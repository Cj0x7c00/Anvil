/*****************************************************
*
* Renderer for the application
* 
* singleton
*
******************************************************/

#pragma once
#include "../Window/Window.hpp"
#include "../Base/Pointer.hpp"
#include "../Base/macros.hpp"
#include "GrComp/GraphicsFactory.h"
#include "RenderSystem.h"

typedef struct VkRenderPass_T* VkRenderPass;

namespace Anvil
{
	class Devices;
	class SwapChain;

	class ANV_API Renderer
	{
	public:
		static void Init(Ref<Window> window);

		static void UseSystem(Ref<RenderSystem> _system);

		static void UseDefaultConfiguration();
		
		static VkRenderPass& GetRenderPass() { return m_RenderPass; };

	private:
		static void create_render_pass();
	private:
		static Ref<Devices>   m_Devices;
		static Ref<SwapChain> m_SwapChain;
		static Ref<Window>    m_Window;

		static Ref<RenderSystem> m_RenderSystem;

		static VkRenderPass   m_RenderPass;
	};
}

