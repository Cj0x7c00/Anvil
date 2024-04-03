#include "SpriteSystem.h"
#include "Util/Time/Time.h"
#include "Renderer/SwapChain.h"
#include "Renderer/GrComp/Pipeline.h"

#include "Scene/Components.h"
#include "Scene/Scene.h"

#include <entt/entt.hpp>

#include <vulkan/vulkan.h>
#include <Util/anvLog.hpp>
#include <algorithm>
#include <execution>

namespace Anvil
{
	SpriteSystem::~SpriteSystem()
	{

	}

	void SpriteSystem::Init()
	{
		load_shaders();
		create_pipeline();
		create_ubos();
		create_descriptor_pool();
		create_descriptor_sets();
	}

	void SpriteSystem::OnCallOnce(CommandBuffer cmdBuffer)
	{

	}

	void SpriteSystem::NewFrame(NewFrameInfo& frameInfo)
	{
		
		m_Pipeline->Bind(frameInfo.CommandBuffer.get());

		Renderer::SetViewport(ViewportInfo::Default(), frameInfo.CommandBuffer.get());
		
		auto& Reg = frameInfo.Scene->GetRegistry();
		auto sprites = Reg.view<SpriteComponent>();
		auto devices = Devices::GetInstance();

		sprites.each([&](SpriteComponent& spriteData)
			{
				(spriteData.buffersCreatedFlag == false) ? spriteData.CreatBuffers() : NULL;

				spriteData.Bind(frameInfo.CommandBuffer.get(), m_Pipeline);
				vkCmdBindDescriptorSets(frameInfo.CommandBuffer->Get(), VK_PIPELINE_BIND_POINT_GRAPHICS, 
					m_Pipeline->GetPipelineLayout(), 0, 1, &m_DescriptorSets[frameInfo.FrameIndex], 
					0, nullptr);
				spriteData.Draw(frameInfo.CommandBuffer.get());
			});
		
	}

	void SpriteSystem::create_ubos()
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
		update_ubos(frameInfo);
	}

	void SpriteSystem::update_ubos(NewFrameInfo& frameInfo)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), m_SwapChain->GetExtent().width / (float)m_SwapChain->GetExtent().height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
		memcpy(m_UniformBuffersMapped[frameInfo.FrameIndex], &ubo, sizeof(ubo));
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
		std::vector<VkDescriptorSetLayout> layouts(Renderer::MAX_FRAMES_IN_FLIGHT, m_Pipeline->GetDescriptorLayout());
		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.descriptorSetCount = static_cast<uint32_t>(Renderer::MAX_FRAMES_IN_FLIGHT);
		allocInfo.pSetLayouts = layouts.data();

		m_DescriptorSets.resize(Renderer::MAX_FRAMES_IN_FLIGHT);
		if (vkAllocateDescriptorSets(Devices::GetInstance()->Device(), &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS) {
			ENGINE_WARN("failed to allocate descriptor sets");
		}

		for (size_t i = 0; i < Renderer::MAX_FRAMES_IN_FLIGHT; i++) {
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_UniformBuffers[i];
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = m_DescriptorSets[i];
			descriptorWrite.dstBinding = 0;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;	
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(Devices::GetInstance()->Device(), 1, &descriptorWrite, 0, nullptr);
		}
	}

	void SpriteSystem::load_shaders()
	{
		ENGINE_INFO("Sprite System: Loading Shaders");
		std::filesystem::current_path("core/src/Renderer/Systems/");
		auto vert = GraphicsFactory::CreateShader("Shaders/SpriteSystemV.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("Shaders/SpriteSystemF.glsl", FRAGMENT);

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);


	}

	void SpriteSystem::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");
		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders);
	}
}