#include "RenderSystem.h"
#include "Systems/SpriteSystem.h"
#include "Systems/UISystem.h"
#include "SwapChain.h"
#include "Devices.h"
#include "Renderer.h"
#include "Util/anvLog.hpp"
#include "UBO.h"
#include <vulkan/vulkan.h>

std::vector<Anvil::RenderSystem*> Anvil::RenderSystem::m_SystemsInPlace = {};
Anvil::Ref<Anvil::SwapChain> Anvil::RenderSystem::m_SwapChain = nullptr;

namespace Anvil
{
	std::vector<Ref<RenderSystem>> RenderSystem::Default(Ref<SwapChain> _sc)
	{
		return { CreateRef<SpriteSystem>(_sc), CreateRef<UISystem>(_sc) };
	}

	RenderSystem::RenderSystem(Ref<SwapChain> _sc)
	{
		m_SwapChain = _sc;


		m_SystemsInPlace.push_back(this);
		ENGINE_INFO("Render system count: {}", m_SystemsInPlace.size());
	}

	void RenderSystem::OnCallOnce(CommandBuffer cmdBuffer)
	{
	}

	void RenderSystem::Update(NewFrameInfo& frameInfo)
	{

	}

	void RenderSystem::WindowWasResized(Ref<SwapChain> _sc)
	{
		m_SwapChain = _sc;
	}

}
