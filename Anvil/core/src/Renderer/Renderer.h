/*****************************************************
*
* Renderer for the application
* 
* singleton
*
******************************************************/

#pragma once
#include "RenderPass.h"
#include "RenderSystem.h"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "../Window/Window.hpp"
#include "../Scene/SceneManager.h"
#include "GrComp/GraphicsFactory.h"

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkSemaphore_T* VkSemaphore;
typedef struct VkFence_T* VkFence;
enum VkResult;

namespace Anvil
{
	class Devices;
	class SwapChain;

	struct NewFrameInfo
	{
		uint32_t FrameIndex;
		uint32_t ImageIndex;
		Ref<RenderPass>	 RenderPass;
	};

	class ANV_API Renderer
	{
	public:
		static void Init(Ref<Window> window, SceneManager* _scene_manager);
		static void UseSystem(Ref<RenderSystem> _system);
		static void UseDefaultConfiguration();
		static void NewFrame();
		static void WaitIdle();
		static void CreateNewSwapChain();
		static void WindowWasResized();

		static Ref<RenderPass> GetRenderPass() { return m_FrameInfo.RenderPass; };

	public:
		static const int MAX_FRAMES_IN_FLIGHT = 3;

	private:
		static void create_render_pass();
		static void check_swapchain_suitability(VkResult res);
		static void sync();
		static void submit(uint32_t imgIndex);

	private:
		static NewFrameInfo m_FrameInfo;

		static Ref<Devices>      m_Devices;
		static Ref<SwapChain>    m_SwapChain;
		static Ref<Window>		 m_Window;
		static Ref<RenderSystem> m_RenderSystem;

		static SceneManager* m_SceneManager;

		static std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		static std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		static std::vector<VkFence>     m_InFlightFences;

	};
}

