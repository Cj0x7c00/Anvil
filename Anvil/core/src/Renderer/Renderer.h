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
#include "RenderPass.h"
#include "GrComp/GraphicsFactory.h"
#include "RenderSystem.h"

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkSemaphore_T* VkSemaphore;
typedef struct VkFence_T* VkFence;

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
		
		static Ref<RenderPass> GetRenderPass() { return m_RenderPass; };

		static void NewFrame();

		static void WaitIdle();

	private:
		static void create_render_pass();
		static void sync();
		static void submit();
		static void present(uint32_t imgIndex);

	private:
		static Ref<Devices>      m_Devices;
		static Ref<SwapChain>    m_SwapChain;
		static Ref<Window>		 m_Window;
		static Ref<RenderSystem> m_RenderSystem;
		static Ref<RenderPass>	 m_RenderPass;

		static VkCommandBuffer   m_CommandBuffer;

		static VkSemaphore m_ImageAvailableSemaphore;
		static VkSemaphore m_RenderFinishedSemaphore;
		static VkFence     m_InFlightFence;
	};
}

