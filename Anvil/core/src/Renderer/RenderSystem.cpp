#include "RenderSystem.h"
#include "DefaultSystem/defaultRS.h"
#include "SwapChain.h"
#include "Devices.h"

#include <vulkan/vulkan.h>

namespace Anvil
{
	Ref<RenderSystem> RenderSystem::Default(Ref<SwapChain> _sc)
	{
		return CreateRef<defaultRS>(_sc);
	}

	RenderSystem::RenderSystem(Ref<SwapChain> _sc)
		: m_SwapChain{_sc}
	{
		m_CommandBuffer = CommandBuffer::Create();
	}

	void RenderSystem::NewFrame(Ref<RenderPass> renderPass, Ref<Scene> scene)
	{
		
	}

	void RenderSystem::Flush()
	{
		m_CommandBuffer->Reset();
	}

	Ref<CommandBuffer> RenderSystem::GetCommandBuffer()
	{
		return m_CommandBuffer;
	}

}
