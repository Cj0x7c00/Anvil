#pragma once
#include "anvpch.hpp"
#include "vk_object.hpp"

namespace AnvilEngine
{
    class anvRenderer
    {
    private:
        /* data */
    public:
        void Init(GLFWwindow* window);
        void Clean();

        auto IsDeviceSuitable(VkPhysicalDevice device);

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

        VK_OBJ::SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

        void CreateSurface(GLFWwindow* window);

        void CreateSwapChain(GLFWwindow* window);
    };
    
    
} // AnvilEngine
