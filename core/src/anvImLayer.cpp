// Imgui UI
/*
#include "anvImLayer.hpp"

namespace Anvil
{
    anvImLayer::anvImLayer(AnvDevice &m_device, GLFWwindow* m_window, anvSwapChain &sc) : device{m_device}, window{m_window}, swapChain{sc}
    {
        InitImGUI();
    }

    anvImLayer::~anvImLayer()
    {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void CheckVkResult(VkResult err)
    {

    }

    void anvImLayer::InitImGUI()
    {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForVulkan(window, true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = device.m_instance;
        init_info.PhysicalDevice = device.m_physicalDevice;
        init_info.Device = device.m_device;
        init_info.QueueFamily = device.FindQueueFamilies(device.m_physicalDevice).graphicsFamily; // <- WATCH, VERY IFFY LINE OF CODE
        init_info.Queue = device.m_graphicsQueue;
        init_info.PipelineCache = NULL;
        init_info.DescriptorPool = NULL;
        init_info.Subpass = 0;
        init_info.MinImageCount = 2;
        init_info.ImageCount = swapChain.imageCount();
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = nullptr;
        init_info.CheckVkResultFn = NULL;
        ImGui_ImplVulkan_Init(&init_info, swapChain.getRenderPass());
    }

    void anvImLayer::ImDraw(VkCommandBuffer cmdBuffer)
    {
        ImGui::Render();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBuffer);
    }
}
*/