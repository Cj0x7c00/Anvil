/*****************************************************
*
* Renderer for the application
* 
* singleton
*
******************************************************/

#pragma once
#include "Devices.h"
#include "SwapChain.h"

#include "Window/Window.hpp"
#include "Base/Pointer.hpp"
#include "Base/macros.hpp"

namespace Anvil
{
	class ANV_API Renderer
	{
	public:
		static void Init(Ref<Window> window);

	private:
		static Ref<Devices> m_Devices;
		static Ref<SwapChain> m_SwapChain;
		static Ref<Window>  m_Window;
	};
}

