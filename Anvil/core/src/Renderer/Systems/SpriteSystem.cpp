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
		auto devices = Devices::GetInstance();

		sprites.each([&frameInfo, &devices, this, &Reg](auto entity, SpriteComponent& spriteData) {

			VkBuffer& vertexBuffer = spriteData.vertexBuffer;
			VkBuffer& indexBuffer  = spriteData.indexBuffer;

			if (vertexBuffer != NULL || indexBuffer != NULL)
			{
				VkBuffer vertexBuffers[] = { vertexBuffer };
				VkDeviceSize offsets[] = { 0 };

				vkCmdBindVertexBuffers(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, vertexBuffers, offsets);
				vkCmdBindIndexBuffer(m_CommandBuffers[frameInfo.ImageIndex]->Get(), indexBuffer, 0, VK_INDEX_TYPE_UINT16);
				vkCmdDrawIndexed(m_CommandBuffers[frameInfo.ImageIndex]->Get(), static_cast<uint32_t>(spriteData.indexs.size()), 1, 0, 0, 0);
				return;
			}
			else {
				
				VkDeviceMemory vertexBufferMemory;
				VkDeviceMemory indexBufferMemory;

				// vertex
				{

					VkDeviceSize bufferSize = sizeof(spriteData.verts[0]) * spriteData.verts.size();

					VkBuffer stagingBuffer;
					VkDeviceMemory stagingBufferMemory;
					devices->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
						| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

					void* data;
					vkMapMemory(devices->Device(), stagingBufferMemory, 0, bufferSize, 0, &data);
					memcpy(data, spriteData.verts.data(), (size_t)bufferSize);
					vkUnmapMemory(devices->Device(), stagingBufferMemory);

					devices->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
						VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

					devices->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

					vkDestroyBuffer(devices->Device(), stagingBuffer, nullptr);
					vkFreeMemory(devices->Device(), stagingBufferMemory, nullptr);

					
					VkBuffer vertexBuffers[] = { vertexBuffer };
					VkDeviceSize offsets[] = { 0 };

					vkCmdBindVertexBuffers(m_CommandBuffers[frameInfo.ImageIndex]->Get(), 0, 1, vertexBuffers, offsets);
				}

				// index
				{

					VkDeviceSize bufferSize = sizeof(spriteData.indexs[0]) * spriteData.indexs.size();

					VkBuffer stagingBuffer;
					VkDeviceMemory stagingBufferMemory;
					devices->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
						VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

					void* data;
					vkMapMemory(devices->Device(), stagingBufferMemory, 0, bufferSize, 0, &data);
					memcpy(data, spriteData.indexs.data(), (size_t)bufferSize);
					vkUnmapMemory(devices->Device(), stagingBufferMemory);

					devices->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
						VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

					devices->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

					vkDestroyBuffer(devices->Device(), stagingBuffer, nullptr);
					vkFreeMemory(devices->Device(), stagingBufferMemory, nullptr);

					vkCmdBindIndexBuffer(m_CommandBuffers[frameInfo.ImageIndex]->Get(), indexBuffer, 0, VK_INDEX_TYPE_UINT16);

				}

				vkCmdDrawIndexed(m_CommandBuffers[frameInfo.ImageIndex]->Get(), static_cast<uint32_t>(spriteData.indexs.size()), 1, 0, 0, 0);

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
		auto vert = GraphicsFactory::CreateShader("shaders/SpriteSystemV.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("shaders/SpriteSystemF.glsl", FRAGMENT);

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);
	}

	void SpriteSystem::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");
		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders);
	}
}