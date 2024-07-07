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
#include "../Layer/anvLayerStack.hpp"


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

typedef struct VkRenderPass_T* VkRenderPass;
typedef struct VkCommandBuffer_T* VkCommandBuffer;
typedef struct VkSemaphore_T* VkSemaphore;
typedef struct VkFence_T* VkFence;

typedef struct VkImage_T* VkImage;
typedef struct VkImageView_T* VkImageView;

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
		/// <summary>
		/// Initialization of the renderer, only the Anvil DLL should call this.
		/// </summary>
		/// <param name="window">window ref</param>
		/// <param name="_scene_manager">scene manager  pointer</param>
		static void Init(Ref<Window> window, SceneManager* _scene_manager);

		/// <summary>
		/// TODO: Impliment
		/// Used to load your own custom Rendering System onto the system stack.
		/// </summary>
		static void UseSystem(Ref<RenderSystem> _system);

		/// <summary>
		/// Initializes all the default rendering systems
		/// </summary>
		static void InitCoreSystems();

		/// <summary>
		/// called right before the main loop. called when 
		/// Rendering Systems need to upload to the GPU
		/// </summary>
		static void BeginOneTimeOps();

		/// <summary>
		/// Similar to BeginOneTimeOps(), But can be called at any time
		/// </summary>
		/// <param name="_Fn">A function or lambda with your logic</param>
		static void OnSingleTimeCommand(std::function<void(CommandBuffer cmdBuffer)>  _Fn);

		/// <summary>
		/// Main draw function
		/// </summary>
		static void NewFrame();

		/// <summary>
		/// Renderer tells Vulkan to wait idle
		/// </summary>
		static void WaitIdle();

		/// <summary>
		/// Set Viewpor information
		/// </summary>
		/// <param name="info">Viewport info struct</param>
		/// <param name="cmdBuff">Command Buffer pointer</param>
		static void SetViewport(ViewportInfo& info, CommandBuffer* cmdBuff);

		/// <summary>
		/// Submits the frame info after processing is done
		/// </summary>
		/// <param name="_fi">New frame info</param>
		static void Submit(NewFrameInfo& _fi);

		/// <summary>
		/// Submits the one time commands
		/// </summary>
		/// <param name="cmdBuffer">Command Buffer</param>
		static void SubmitOneTimeCommands(CommandBuffer cmdBuffer);

		/// <summary>
		/// Creates a new swapchain for a window
		/// </summary>
		static void CreateNewSwapChain();

		/// <summary>
		/// Callback used in Window class to tell the renderer thewindow was resized
		/// </summary>
		static void WindowWasResized();

		/// <summary>
		/// Get the active render pass
		/// </summary>
		/// <returns>Ref RenderPass</returns>
		static Ref<RenderPass> GetRenderPass() { return m_FrameInfo.RenderPass; };

		static void BeginRenderPass();

		static void EndRenderPass();

		/// <summary>
		/// Get the active swap chain
		/// </summary>
		/// <returns>Ref SwapChain</returns>
		static Ref<SwapChain>  GetSwapChain();

		/// <summary>
		/// Get the active rendering window
		/// </summary>
		/// <returns>Ref Window</returns>
		static Ref<Window>     GetWindow();


	public:
		static const int MAX_FRAMES_IN_FLIGHT = 3;

	private:
		static void create_render_pass();
		static void create_depth_buffer();
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

		static VkImage m_DepthImage;
		static VkImageView m_DepthImageView;
	};
}

