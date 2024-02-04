/*****************************************************
*
* Renderer for the application
* 
* singleton
*
******************************************************/

#pragma once
#include "RenderPass.h"
#include "GrComp/GraphicsFactory.h"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"
#include "../Window/Window.hpp"
#include "../Scene/SceneManager.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkSemaphore_T* VkSemaphore;
typedef struct VkFence_T* VkFence;

enum VkResult;

namespace Anvil
{
	class Devices;
	class SwapChain;
	class RenderSystem;
	class CommandBuffer;

	struct NewFrameInfo
	{
		uint32_t FrameIndex;
		uint32_t ImageIndex;

		Ref<Scene> Scene;

		Ref<CommandBuffer> CommandBuffer;
		Ref<RenderPass>	   RenderPass;
	};

	struct ViewportInfo
	{
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;

		float scissorOffset[2]{0.f, 0.f};
		Extent2D scissorExtent;

		static ViewportInfo Default();
	};

	class ANV_API Renderer
	{
	public:
		static void Init(Ref<Window> window, SceneManager* _scene_manager);
		static void UseSystem(Ref<RenderSystem> _system);
		static void UseDefaultConfiguration();
		static void BeginOneTimeOps();
		static void NewFrame();
		static void WaitIdle();
		static void SetViewport(ViewportInfo& info, CommandBuffer* cmdBuff);
		static void Submit(NewFrameInfo& _fi);
		static void SubmitOneTimeCommands(CommandBuffer cmdBuffer);
		static void CreateNewSwapChain();
		static void WindowWasResized();

		static Ref<RenderPass> GetRenderPass() { return m_FrameInfo.RenderPass; };
		static Ref<SwapChain>  GetSwapChain();
		static Ref<Window>     GetWindow();


	public:
		static const int MAX_FRAMES_IN_FLIGHT = 3;

	private:
		static void create_render_pass();
		static void check_swapchain_suitability(VkResult res);


		static void sync();

	private:
		static NewFrameInfo m_FrameInfo;

		static Ref<Window>		 m_Window;
		static Ref<Devices>      m_Devices;
		static Ref<SwapChain>    m_SwapChain;
		static std::vector<Ref<RenderSystem>> m_RenderSystems;
		static std::vector<Ref<CommandBuffer>> m_CommandBuffers;

		static SceneManager* m_SceneManager;

		static std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		static std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		static std::vector<VkFence>     m_InFlightFences;

	};
}

