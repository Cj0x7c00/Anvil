#include "SpriteSystem.h"
#include "Util/Time/Time.h"
#include "Renderer/SwapChain.h"
#include "Renderer/GrComp/Pipeline.h"

#include "Base/anvApplication.hpp"

#include "Scene/Scene.h"

#include <glm/gtx/string_cast.hpp>

#include <entt/entt.hpp>

#include <vulkan/vulkan.h>
#include <Util/anvLog.hpp>

#include <algorithm>
#include <execution>
#include <Renderer/Camera.h>

// TODO: Debug Stats

namespace Anvil
{
	SpriteSystem::~SpriteSystem()
	{

	}

	void SpriteSystem::Init()
	{
		load_shaders();
		create_pipeline();
		create_ubo();
		create_descriptor_pool();
		create_descriptor_sets();
	}

	void SpriteSystem::OnCallOnce(CommandBuffer cmdBuffer)
	{

	}

	void SpriteSystem::NewFrame(NewFrameInfo& frameInfo)
	{
		
		auto& Reg = frameInfo.Scene->GetRegistry();
		auto sprites = Reg.view<SpriteComponent, TransformComponent>();
		auto devices = Devices::GetInstance();
		frameInfo.CommandBuffer->BeginRecording();
		Renderer::BeginRenderPass();
		Renderer::SetViewport(ViewportInfo::Default(), frameInfo.CommandBuffer.get());
		
		m_Pipeline->Bind(frameInfo.CommandBuffer.get());

		for (auto& sprite : sprites)
		{
			auto& [sData, tData] = sprites.get<SpriteComponent, TransformComponent>(sprite);

			if (!sData.buffersCreatedFlag)
			{
				sData.CreateBuffers();
				sData.buffersCreatedFlag = true;
			}

			UniformBufferObject ubo{};

			ubo.view = frameInfo.Scene->GetActiveCamera()->GetComponent<Camera>().GetViewMatrix();
			ubo.proj = frameInfo.Scene->GetActiveCamera()->GetComponent<Camera>().GetProjectionMatrix();
			ubo.proj[1][1] *= -1;
			memcpy(m_UniformBuffersMapped[frameInfo.FrameIndex], &ubo, sizeof(ubo));

			vkCmdBindDescriptorSets(frameInfo.CommandBuffer->Get(), VK_PIPELINE_BIND_POINT_GRAPHICS,
				m_Pipeline->GetPipelineLayout(), 0, 1, &m_DescriptorSets[frameInfo.FrameIndex],
			 	0, nullptr);

			PushConstantData pcd{};
			pcd.model = tData.GetModelMatrix(); //m4x4
			pcd.color = sData.Color; // v3

			vkCmdPushConstants(frameInfo.CommandBuffer->Get(), 
				m_Pipeline->GetPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0,
				sizeof(PushConstantData), &pcd);

			sData.Bind(frameInfo.CommandBuffer.get());
			sData.Draw(frameInfo.CommandBuffer.get());
			
		}
	}

	void SpriteSystem::create_ubo()
	{
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);

		m_UniformBuffers.resize(Renderer::MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMemory.resize(Renderer::MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMapped.resize(Renderer::MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < Renderer::MAX_FRAMES_IN_FLIGHT; i++) {
			Devices::GetInstance()->CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_UniformBuffers[i], m_UniformBuffersMemory[i]);

			vkMapMemory(Devices::GetInstance()->Device(), m_UniformBuffersMemory[i], 0, bufferSize, 0, &m_UniformBuffersMapped[i]);
		}
	}

	void SpriteSystem::Update(NewFrameInfo& frameInfo)
	{

	}

	void SpriteSystem::update_ubos(NewFrameInfo& frameInfo, TransformComponent& trans)
	{
		//UniformBufferObject ubo{};

		//ubo.model = trans.GetModelMatrix();
		//ubo.view = frameInfo.Scene->GetActiveCamera()->GetComponent<Camera>().GetViewMatrix();
		//ubo.proj = frameInfo.Scene->GetActiveCamera()->GetComponent<Camera>().GetProjectionMatrix();
		//ubo.proj[1][1] *= -1;
		//memcpy(m_UniformBuffersMapped[frameInfo.ImageIndex], &ubo, sizeof(ubo));
	}

	void SpriteSystem::create_descriptor_pool()
	{
		VkDescriptorPoolSize poolSize{};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = static_cast<uint32_t>(Renderer::MAX_FRAMES_IN_FLIGHT) ;

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = static_cast<uint32_t>(Renderer::MAX_FRAMES_IN_FLIGHT);

		if (vkCreateDescriptorPool(Devices::GetInstance()->Device(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS) {
			ENGINE_ERROR("failed to create descriptor pool!");
		}
	}

	void SpriteSystem::create_descriptor_sets()
	{
		ENGINE_INFO("Sprite System: Creating DST sets");

		std::vector<VkDescriptorSetLayout> layouts(Renderer::MAX_FRAMES_IN_FLIGHT, m_Pipeline->GetDescriptorLayout());

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
		allocInfo.pSetLayouts = layouts.data();

		m_DescriptorSets.resize(Renderer::MAX_FRAMES_IN_FLIGHT);

		if (vkAllocateDescriptorSets(Devices::GetInstance()->Device(), &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS) {
			ENGINE_WARN("failed to allocate descriptor sets");
		}

		for (size_t i = 0; i < m_DescriptorSets.size(); i++) {

			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_UniformBuffers[i];
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;	
			descriptorWrite.dstSet = m_DescriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(Devices::GetInstance()->Device(), 1, &descriptorWrite, 0, nullptr);
		}
	}

	void SpriteSystem::load_shaders()
	{
		ENGINE_INFO("Sprite System: Loading Shaders");
		
		std::filesystem::current_path(AnvilApplication::GetLibDir().c_str());
		std::filesystem::current_path("core/src/Renderer/Systems/Shaders/");

		auto vert = GraphicsFactory::CreateShader("SpriteSystemV.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("SpriteSystemF.glsl", FRAGMENT);

		std::filesystem::current_path(AnvilApplication::GetWorkingDir().c_str());

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);
	}

	void SpriteSystem::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");

		PipelineInfo pi{};
		pi.vertexBindingDesc = vertex::GetBindingDescription();
		pi.vertexAttrDesc    = vertex::GetAttributeDescriptions();
		
		pi.vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		pi.vertexInputInfo.vertexBindingDescriptionCount = 1;
		pi.vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(pi.vertexAttrDesc.size());
		pi.vertexInputInfo.pVertexBindingDescriptions = &pi.vertexBindingDesc;
		pi.vertexInputInfo.pVertexAttributeDescriptions = pi.vertexAttrDesc.data();

		pi.asmInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		pi.asmInputInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		pi.asmInputInfo.primitiveRestartEnable = VK_FALSE;

		pi.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		pi.viewportInfo.viewportCount = 1;
		pi.viewportInfo.scissorCount = 1;

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		pi.depthInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		pi.depthInfo.depthTestEnable = VK_TRUE;
		pi.depthInfo.depthWriteEnable = VK_TRUE;
		pi.depthInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		pi.depthInfo.depthBoundsTestEnable = VK_FALSE;
		pi.depthInfo.minDepthBounds = 0.0f; // Optional
		pi.depthInfo.maxDepthBounds = 1.0f; // Optional
		pi.depthInfo.stencilTestEnable = VK_FALSE;
		pi.depthInfo.front = {}; // Optional
		pi.depthInfo.back = {};  // Optional


		pi.rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		pi.rasterizerInfo.depthClampEnable = VK_FALSE;
		pi.rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
		pi.rasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
		pi.rasterizerInfo.lineWidth = 1.0f;
		pi.rasterizerInfo.cullMode = VK_CULL_MODE_NONE;
		pi.rasterizerInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		pi.rasterizerInfo.depthBiasEnable = VK_FALSE;

		pi.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		pi.multisampleInfo.sampleShadingEnable = VK_FALSE;
		pi.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		pi.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		pi.colorBlendInfo.logicOpEnable = VK_FALSE;
		pi.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
		pi.colorBlendInfo.attachmentCount = 1;
		pi.colorBlendInfo.pAttachments = &colorBlendAttachment;
		pi.colorBlendInfo.blendConstants[0] = 0.f;
		pi.colorBlendInfo.blendConstants[1] = 0.f;
		pi.colorBlendInfo.blendConstants[2] = 0.f;
		pi.colorBlendInfo.blendConstants[3] = 0.f;

		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		pi.dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		pi.dynamicInfo.dynamicStateCount = 2;
		pi.dynamicInfo.pDynamicStates = dynamicStates.data();

		// -- Push Constant Data -- //
		VkPushConstantRange SpriteData{};
		SpriteData.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		SpriteData.size = sizeof(PushConstantData);
		SpriteData.offset = 0;

		pi.PushConstantRanges.push_back(SpriteData);

		// -- UBO Data -- //
		VkDescriptorSetLayoutBinding uboBinding{};
		uboBinding.binding = 0;
		uboBinding.descriptorCount = 1;
		uboBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboBinding.pImmutableSamplers = VK_NULL_HANDLE;
		uboBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

		pi.DstSetLayoutBindings.push_back(uboBinding);

		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders, pi);
	}
}