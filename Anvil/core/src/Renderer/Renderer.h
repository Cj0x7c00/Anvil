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
enum VkResult;

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
		static void NewFrame();
		static void WaitIdle();
		static void CreateNewSwapChain();
		static void WindowWasResized();

		static Ref<RenderPass> GetRenderPass() { return m_RenderPass; };

	public:
		static const int MAX_FRAMES_IN_FLIGHT = 3;

	private:
		static void create_render_pass();
		static void check_swapchain_suitability(VkResult res);
		static void sync();
		static void submit(uint32_t imgIndex);

	private:
		static uint32_t m_FrameIndex;
		static uint32_t m_ImageIndex;

		static Ref<Devices>      m_Devices;
		static Ref<SwapChain>    m_SwapChain;
		static Ref<Window>		 m_Window;
		static Ref<RenderSystem> m_RenderSystem;
		static Ref<RenderPass>	 m_RenderPass;

		static std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		static std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		static std::vector<VkFence>     m_InFlightFences;

	};
}

