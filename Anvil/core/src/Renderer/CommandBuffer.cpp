#include "CommandBuffer.h"

#include "Devices.h"

#include <vulkan/vulkan.h>

namespace Anvil
{
	Ref<CommandBuffer> CommandBuffer::Create()
	{
		return CreateRef<CommandBuffer>();
	}

	void CommandBuffer::BeginRecording()
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr; 

		if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
			ENGINE_WARN("Failed to record the command buffer");
		}
		ENGINE_DEBUG("Recording Command Buffer");
	}

	void CommandBuffer::EndRecording()
	{
		vkEndCommandBuffer(m_CommandBuffer);
		ENGINE_DEBUG("Recording done");
	}

	void CommandBuffer::Reset()
	{
		vkResetCommandBuffer(m_CommandBuffer, 0);
	}

	VkCommandBuffer& CommandBuffer::Get()
	{
		return m_CommandBuffer;
	}

	void CommandBuffer::create_cmd_buffer()
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = Devices::GetInstance()->CommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(Devices::GetInstance()->Device(), &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
			ENGINE_WARN("[Render System]: Failed to create command buffer");
		}

		ENGINE_INFO("Created command buffer");
	}
}