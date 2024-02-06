#include "UISystem.h"
#include "Util/Time/Time.h"
#include "Renderer/SwapChain.h"
#include "Renderer/GrComp/Pipeline.h"

#include "Scene/Components.h"
#include "Scene/Scene.h"

#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"

#include <entt/entt.hpp>

#include <vulkan/vulkan.h>
#include <Util/anvLog.hpp>
#include <Util/TaskRunner/TaskRunner.h>


namespace Anvil
{
	UISystem::~UISystem()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplVulkan_Shutdown();
		ImGui::DestroyContext();
	}

	void UISystem::Init()
	{
		create_descriptor_pool();

		ImGui::CreateContext();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)Renderer::GetWindow()->Get(), true);

		auto devices = Devices::GetInstance();

		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = devices->Instance();
		init_info.PhysicalDevice = devices->GPU();
		init_info.Device = devices->Device();
		init_info.Queue = devices->GraphicsQueue();
		init_info.DescriptorPool = m_DescriptorPool;
		init_info.MinImageCount = Renderer::MAX_FRAMES_IN_FLIGHT;
		init_info.ImageCount = Renderer::MAX_FRAMES_IN_FLIGHT;
		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

		ImGui_ImplVulkan_Init(&init_info, Renderer::GetRenderPass()->Get());
	}

	void UISystem::OnCallOnce(CommandBuffer cmdBuffer)
	{
		ImGui_ImplVulkan_CreateFontsTexture(cmdBuffer.Get());
		ImGui::SetNextWindowPos(ImVec2(50, 50));
	}

	void UISystem::NewFrame(NewFrameInfo& frameInfo)
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplVulkan_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode);
		
		auto& Reg = frameInfo.Scene->GetRegistry();
		auto view = Reg.view<CanvasComponent>();
		view.each([](CanvasComponent& canComp) {

			auto& canvas = canComp.Get();
			canvas->Update();
			
		});

		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), frameInfo.CommandBuffer->Get(), NULL);
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	void UISystem::create_descriptor_pool()
	{
		VkDescriptorPoolSize pool_sizes[] =
		{
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		};

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		poolInfo.maxSets = Renderer::MAX_FRAMES_IN_FLIGHT;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = pool_sizes;

		if (vkCreateDescriptorPool(Devices::GetInstance()->Device(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS) {
			ENGINE_ERROR("failed to create descriptor pool!");
		}
	}

}