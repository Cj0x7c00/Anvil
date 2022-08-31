#pragma once
// Imgui UI
/*
#include "anvLog.hpp"
#include "include/imgui/imgui.h"
#include "include/imgui/backends/imgui_impl_glfw.h"
#include "include/imgui/backends/imgui_impl_vulkan.h"

#include "anvDevice.hpp"
#include "anvSwapChain.hpp"

namespace Anvil{

    class anvImLayer
    {   
        public:
            anvImLayer(AnvDevice &m_device, GLFWwindow* m_window, anvSwapChain &sc);
            ~anvImLayer();
            void ImDraw(VkCommandBuffer cmdBuffer);

        private:
            ImGui_ImplVulkan_InitInfo initInfo{};
            AnvDevice &device;
            anvSwapChain &swapChain;
            GLFWwindow* window;

            void InitImGUI();
            
            void CheckVkResult(VkResult err);
    };

}
*/