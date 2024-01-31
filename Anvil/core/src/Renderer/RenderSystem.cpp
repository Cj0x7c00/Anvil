#include "RenderSystem.h"
#include "Systems/SpriteSystem.h"
#include "SwapChain.h"
#include "Devices.h"
#include "Renderer.h"
#include "Util/anvLog.hpp"
#include <vulkan/vulkan.h>

std::vector<Anvil::RenderSystem*> Anvil::RenderSystem::m_SystemsInPlace = {};

namespace Anvil
{
	Ref<RenderSystem> RenderSystem::Default(Ref<SwapChain> _sc)
	{
		return CreateRef<SpriteSystem>(_sc);
	}

	RenderSystem::RenderSystem(Ref<SwapChain> _sc)
		: m_SwapChain{_sc}
	{
		m_CommandBuffers.clear();
		for (int i = 0; i < Renderer::MAX_FRAMES_IN_FLIGHT; i++)
		{
			m_CommandBuffers.push_back(CommandBuffer::Create());
		}

		m_SystemsInPlace.push_back(this);
		ENGINE_INFO("Render system count: {}", m_SystemsInPlace.size());
	}

	void RenderSystem::Flush(uint32_t imageIndex)
	{
		m_CommandBuffers[imageIndex]->Reset();
	}

	Ref<CommandBuffer> RenderSystem::GetCommandBuffer(uint32_t imageIndex)
	{
		return m_CommandBuffers[imageIndex];
	}

	void RenderSystem::WindowWasResized(Ref<SwapChain> _sc)
	{
		m_SwapChain = _sc;
	}

}
