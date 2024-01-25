#include "RenderSystem.h"
#include "Systems/defaultRS.h"
#include "SwapChain.h"
#include "Devices.h"
#include "Renderer.h"
#include "Util/anvLog.hpp"
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
		m_CommandBuffers.clear();
		for (int i = 0; i < Renderer::MAX_FRAMES_IN_FLIGHT; i++)
		{
			m_CommandBuffers.push_back(CommandBuffer::Create());
			ENGINE_DEBUG("Command buffer {} pushed back", i);
		}
	}

	void RenderSystem::NewFrame(Ref<RenderPass> renderPass, Ref<Scene> scene)
	{
		
	}

	void RenderSystem::Flush(uint32_t imageIndex)
	{
		m_CommandBuffers[imageIndex]->Reset();
	}

	Ref<CommandBuffer> RenderSystem::GetCommandBuffer(uint32_t imageIndex)
	{
		return m_CommandBuffers[imageIndex];
	}

}
