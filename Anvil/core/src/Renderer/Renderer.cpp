#include "Renderer.h"
#include "Util/Time/Time.h"
Anvil::Ref<Anvil::Devices>   Anvil::Renderer::m_Devices	     = nullptr;
Anvil::Ref<Anvil::SwapChain> Anvil::Renderer::m_SwapChain    = nullptr;
Anvil::Ref<Anvil::Window>    Anvil::Renderer::m_Window       = nullptr;

namespace Anvil
{
	void Renderer::Init(Ref<Window> window)
	{
		Time::Profile("Renderer::Init");

		ENGINE_DEBUG("Renderer initializing");

		// initialize Vulkan specific stuff
		m_Devices = Devices::Init(window);
		m_SwapChain = SwapChain::Create();

	}
}

