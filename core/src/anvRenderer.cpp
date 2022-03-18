#include "anvRenderer.hpp"

namespace AnvilEngine
{
    void anvRenderer::Init(GLFWwindow* window)
    {
        ENGINE_INFO("Initializing Renderer");
        CreateSwapChain(window);
    }
    
    
    void anvRenderer::Clean()
    {
        ENGINE_INFO("Cleaning up renderer");
        vkDestroySwapchainKHR(vkobj.m_device, vkobj.swapChain, nullptr);
        vkDestroySurfaceKHR(vkobj.m_instance, vkobj.m_surface, nullptr);
    }


    auto anvRenderer::IsDeviceSuitable(VkPhysicalDevice device) {
        VK_OBJ::QueueFamilyIndices indices = vkobj.findQueueFamilies(device);

        //bool extensionsSupported = vkobj.CheckDeviceExtentionSupport(device);

        bool swapChainAdequate = false;
        
        VK_OBJ::SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        

        return indices.isComplete() && swapChainAdequate;
    }


    VkSurfaceFormatKHR anvRenderer::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }


    VkPresentModeKHR anvRenderer::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) 
    {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }


    VkExtent2D anvRenderer::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
        } else {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            VkExtent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }


    VK_OBJ::SwapChainSupportDetails anvRenderer::QuerySwapChainSupport(VkPhysicalDevice device)
    {
        VK_OBJ::SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, vkobj.m_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkobj.m_surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, vkobj.m_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkobj.m_surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, vkobj.m_surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }


    void anvRenderer::CreateSwapChain(GLFWwindow* window)
    {
        VK_OBJ::SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(vkobj.m_physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, window);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = vkobj.m_surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VK_OBJ::QueueFamilyIndices indices = vkobj.findQueueFamilies(vkobj.m_physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(vkobj.m_device, &createInfo, nullptr, &vkobj.swapChain) != VK_SUCCESS) {
            ENGINE_ERROR("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(vkobj.m_device, vkobj.swapChain, &imageCount, nullptr);
        vkobj.swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(vkobj.m_device, vkobj.swapChain, &imageCount, vkobj.swapChainImages.data());

        vkobj.swapChainImageFormat = surfaceFormat.format;
        vkobj.swapChainExtent = extent;

        ENGINE_INFO("Created Swapchain");
    }

} // namespace AnvilEngine
