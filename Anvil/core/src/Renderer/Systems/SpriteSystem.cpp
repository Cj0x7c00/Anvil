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
	void SpriteSystem::Init()
	{
		load_shaders();
		create_pipeline();
	}

	void SpriteSystem::render_sprites(NewFrameInfo& frameInfo, Ref<Scene> scene)
	{
		auto& Reg = scene->GetRegistry();
		auto sprites = Reg.view<SpriteComponent>();
		ENGINE_DEBUG("Sprites: {}", sprites.size());
		auto devices = Devices::GetInstance();

		sprites.each([&frameInfo, &devices, this, &Reg](auto entity, SpriteComponent& spriteData) {

			VkBuffer& vertexBuffer = spriteData.vertexBuffer;
			if (vertexBuffer != NULL)
			{
				ENGINE_DEBUG("Handling: {}", Reg.get<TagComponent>(entity).Get());
				VkBuffer vertexBuffers[] = { vertexBuffer };
				VkDeviceSize offsets[] = { 0 };

				vkCmdBindVertexBuffers(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, vertexBuffers, offsets);
				vkCmdDraw(m_CommandBuffers[frameInfo.ImageIndex]->Get(), static_cast<uint32_t>(spriteData.verts.size()), 1, 0, 0);
				return;
			}
			else {

				VkBufferCreateInfo bufferInfo{};
				bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				bufferInfo.size = sizeof(spriteData.verts[0]) * spriteData.verts.size();
				bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

				if (vkCreateBuffer(devices->Device(), &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
					ENGINE_ERROR("Failed to create vertex buffer!");;
				}

				VkDeviceMemory vertexBufferMemory;

				VkMemoryRequirements memRequirements;
				vkGetBufferMemoryRequirements(devices->Device(), vertexBuffer, &memRequirements);

				VkMemoryAllocateInfo allocInfo{};
				allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				allocInfo.allocationSize = memRequirements.size;
				allocInfo.memoryTypeIndex = devices->FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

				if (vkAllocateMemory(devices->Device(), &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
					ENGINE_ERROR("Failed to allocate vertex buffer memory!");
				}

				vkBindBufferMemory(devices->Device(), vertexBuffer, vertexBufferMemory, 0);
				void* data;
				vkMapMemory(devices->Device(), vertexBufferMemory, 0, bufferInfo.size, 0, &data);
				memcpy(data, spriteData.verts.data(), (size_t)bufferInfo.size);
				vkUnmapMemory(devices->Device(), vertexBufferMemory);

				VkBuffer vertexBuffers[] = { vertexBuffer };
				VkDeviceSize offsets[] = { 0 };

				vkCmdBindVertexBuffers(this->m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, vertexBuffers, offsets);
				vkCmdDraw(m_CommandBuffers[frameInfo.ImageIndex]->Get(), static_cast<uint32_t>(spriteData.verts.size()), 1, 0, 0);
			}

		});
	}



	void SpriteSystem::NewFrame(NewFrameInfo& frameInfo, Ref<Scene> scene)
	{
		m_CommandBuffers[frameInfo.ImageIndex]->BeginRecording();
		frameInfo.RenderPass->Begin(m_CommandBuffers[frameInfo.ImageIndex], frameInfo.ImageIndex);
		m_Pipeline->Bind(m_CommandBuffers[frameInfo.ImageIndex]);

		// these need abstraction
		{
			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = 0.0f;
			viewport.width = static_cast<float>(m_SwapChain->GetExtent().width);
			viewport.height = static_cast<float>(m_SwapChain->GetExtent().height);
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			vkCmdSetViewport(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, &viewport);

			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = m_SwapChain->GetExtent();
			vkCmdSetScissor(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, &scissor);
		}

		render_sprites(frameInfo, scene);

		frameInfo.RenderPass->End(m_CommandBuffers[frameInfo.ImageIndex]);
		m_CommandBuffers[frameInfo.ImageIndex]->EndRecording();
	}

	void SpriteSystem::load_shaders()
	{
		ENGINE_INFO("Default System: Loading Shaders");
		auto vert = GraphicsFactory::CreateShader("shaders/DefaultRSVert.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("shaders/DefaultRSFrag.glsl", FRAGMENT);

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);
	}

	void SpriteSystem::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");
		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders);
	}
}