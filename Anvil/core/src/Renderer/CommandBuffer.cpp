#include "CommandBuffer.h"
#include "Devices.h"
#include "GrComp/Pipeline.h"
#include "RenderPass.h"
#include "SwapChain.h"
#include <vulkan/vulkan.h>

namespace Anvil
{
	Ref<CommandBuffer> CommandBuffer::Create()
	{
		return CreateRef<CommandBuffer>();
	}

	void CommandBuffer::BeginRecording(NewFrameInfo& _fi, Ref<Pipeline> _pipeline = nullptr)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr; 

		if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
			ENGINE_WARN("Failed to record the command buffer");
		}

		if (_pipeline != nullptr)
		{
			_pipeline->Bind(_fi.CommandBuffer.get());
		}

		_fi.RenderPass->Begin(this, _fi.ImageIndex);
	}

	void CommandBuffer::BeginRecording()
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		//beginInfo.pInheritanceInfo = nullptr;
		if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
			ENGINE_WARN("Failed to record the command buffer");
		}
	}

	void CommandBuffer::EndRecording()
	{
		vkEndCommandBuffer(m_CommandBuffer);
	}

	// Also ends a render pass
	void CommandBuffer::EndRecording(NewFrameInfo& _fi)
	{
		_fi.RenderPass->End(this);
		vkEndCommandBuffer(m_CommandBuffer);
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
			ENGINE_WARN("Failed to create command buffer");
		}

	}
}