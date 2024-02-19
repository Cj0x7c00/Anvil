#include "Entity.h"
#include "Components.h"
#include "Renderer/Devices.h"
#include "Renderer/CommandBuffer.h"
#include "Renderer/GrComp/Pipeline.h"
#include <vulkan/vulkan.h>

namespace Anvil
{
	UserPointerComponent::UserPointerComponent(Entity* _ent) 
		: entity{ _ent }
	{

	}

	Entity* UserPointerComponent::Get()
	{
		return entity;
	}

	VkVertexInputBindingDescription vertex::GetBindingDescription() 
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 2> vertex::GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(vertex, color);
		return attributeDescriptions;
	}


	void SpriteComponent::CreatBuffers()
	{
		VkDeviceMemory vertexBufferMemory;
		VkDeviceMemory indexBufferMemory;

		// vertex
		{
			VkDeviceSize bufferSize = sizeof(verts[0]) * verts.size();

			VkBuffer stagingBuffer;
			VkDeviceMemory stagingBufferMemory;
			Devices::GetInstance()->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
				| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

			void* data;
			vkMapMemory(Devices::GetInstance()->Device(), stagingBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, verts.data(), (size_t)bufferSize);
			vkUnmapMemory(Devices::GetInstance()->Device(), stagingBufferMemory);

			Devices::GetInstance()->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

			Devices::GetInstance()->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

			vkDestroyBuffer(Devices::GetInstance()->Device(), stagingBuffer, nullptr);
			vkFreeMemory(Devices::GetInstance()->Device(), stagingBufferMemory, nullptr);

		}

		// index
		{
			if (indexs.empty())
				return;

			VkDeviceSize bufferSize = sizeof(indexs[0]) * indexs.size();
			VkBuffer stagingBuffer;
			VkDeviceMemory stagingBufferMemory;
			Devices::GetInstance()->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
				VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

			void* data;
			vkMapMemory(Devices::GetInstance()->Device(), stagingBufferMemory, 0, bufferSize, 0, &data);
			memcpy(data, indexs.data(), (size_t)bufferSize);
			vkUnmapMemory(Devices::GetInstance()->Device(), stagingBufferMemory);

			Devices::GetInstance()->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

			Devices::GetInstance()->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

			vkDestroyBuffer(Devices::GetInstance()->Device(), stagingBuffer, nullptr);
			vkFreeMemory(Devices::GetInstance()->Device(), stagingBufferMemory, nullptr);
		}

		buffersCreatedFlag = true;
	}

	void SpriteComponent::Bind(CommandBuffer* cmdBuffer, Ref<Pipeline> pipeline)
	{
		VkBuffer vertexBuffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(cmdBuffer->Get(), 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(cmdBuffer->Get(), indexBuffer, 0, VK_INDEX_TYPE_UINT16);
	}

	void SpriteComponent::Draw(CommandBuffer* cmdBuffer)
	{
		if (indexs.empty())
		{
			vkCmdDraw(cmdBuffer->Get(), verts.size(), 1, 0, 0);
		}
		else
		{
			vkCmdDrawIndexed(cmdBuffer->Get(), 
			static_cast<uint32_t>(indexs.size()), 1, 0, 0, 0);
		}
	}

}