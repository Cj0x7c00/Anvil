#include "Devices.h"
#include "Util/Time/Time.h"
#include <map>

namespace Anvil
{
    Ref<Anvil::Devices> Devices::m_This = nullptr;

    Ref<Devices> Devices::Init(Ref<Window> window)
    {
        ENGINE_INFO("[VK] Setting up vulkan devices");
        m_This = CreateRef<Devices>(window);
        return m_This;
    }

    bool Devices::check_layer_support()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : m_ValidationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    bool Devices::check_devEXT_support(VkPhysicalDevice dev)
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(m_DeviceExt.begin(), m_DeviceExt.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    std::vector<const char*> Devices::get_extensions()
    {
        
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_ValidationEnabled) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
        
    }

    VkInstance& Devices::Instance()
    {
        return m_Instance;
    }

    VkPhysicalDevice& Devices::GPU()
    {
        return m_GPU;
    }

    VkDevice& Devices::Device()
    {
        return m_Device;
    }

    VkSurfaceKHR& Devices::Surface()
    {
        return m_Surface;
    }

    SwapChainSupportDetails Devices::QuerySwapChainSupport()
    {
        SwapChainSupportDetails details;

        // surface capabilities
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_GPU, m_Surface, &details.capabilities);

        // get formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(m_GPU, m_Surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(m_GPU, m_Surface, &formatCount, details.formats.data());
        }

        // get present modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(m_GPU, m_Surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(m_GPU, m_Surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkSurfaceFormatKHR Devices::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR Devices::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D Devices::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        }
        else {
            auto winExtnt = m_Window->GetExtent();
            VkExtent2D actualExtent = {
                static_cast<uint32_t>(winExtnt.width),
                static_cast<uint32_t>(winExtnt.width)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    void Devices::create_instance()
	{
        Time::Profile(" Devices::create_instance");

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = get_extensions();
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (m_ValidationEnabled) {
            ENGINE_DEBUG("[VK] Validation enabled");
            createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
            createInfo.pNext = nullptr;
        }  
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        auto result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
      
        ENGINE_ASSERT((result == VK_SUCCESS) && "Failed to create VK instance");
        ENGINE_INFO("[VK] Created Instance");
	}

    int Devices::rate_device_suitability(VkPhysicalDevice dev)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(dev, &deviceProperties);
        vkGetPhysicalDeviceFeatures(dev, &deviceFeatures);

        int score = 0;

        // Discrete GPUs have a significant performance advantage
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            ENGINE_DEBUG("[VK] GPU canidate: {}", deviceProperties.deviceName);
            score += 1000;
        }

        // Maximum possible size of textures affects graphics quality
        score += deviceProperties.limits.maxImageDimension2D;

        // Application can't function without geometry shaders
        if (!deviceFeatures.geometryShader) {
            return 0;
        }

        // swap chain must be supported
        if (!check_devEXT_support(dev)) {
            bool swapChainAdequate = false;
            SwapChainSupportDetails swapChainSupport = query_sc_support(dev);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

            if (!swapChainAdequate)
                return 0;
        }

        return score;
    }

    QueueFamilyIndices Devices::FindQueueFamilies(VkPhysicalDevice dev)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(m_GPU, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_GPU, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            ENGINE_ASSERT(m_Surface != NULL && "[VK] Window surface cannot be NULL")
            vkGetPhysicalDeviceSurfaceSupportKHR(m_GPU, i, m_Surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    void Devices::select_gpu()
    {
        Time::Profile("Devices::select_gpu");

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

        ENGINE_ASSERT((deviceCount != 0) && "[VK] No GPU found!");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices) {
            int score = rate_device_suitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        // Check if the best candidate is suitable at all
        if (candidates.rbegin()->first > 0) {
            m_GPU = candidates.rbegin()->second;
        }
        else {
            ENGINE_ERROR("[VK] Failed to find a suitable GPU");
        }

        ENGINE_ASSERT((m_GPU != VK_NULL_HANDLE) && "[VK] Failed to select a GPU!");

        VkPhysicalDeviceProperties devF{};
        vkGetPhysicalDeviceProperties(m_GPU, &devF);
        const char* t;
        switch (devF.deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            t = "Discrete GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            t = "Integrated GPU";
            break;
        default:
            t = "no info available";
            break;
        }
        ENGINE_INFO("[VK] Device Selected: {} : {}", devF.deviceName, t);
    }
    void Devices::logical_setup()
    {
        Time::Profile("Devices::logical_setup");
        QueueFamilyIndices indices = FindQueueFamilies(m_GPU);
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        // swap chain extension
        createInfo.enabledExtensionCount = static_cast<uint32_t>(m_DeviceExt.size());
        createInfo.ppEnabledExtensionNames = m_DeviceExt.data();

        if (m_ValidationEnabled) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
            createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_GPU, &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
            ENGINE_ERROR("[VK] Failed to create an Vulkan logic device");
        }

        vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
        vkGetDeviceQueue(m_Device, indices.presentFamily.value(), 0, &m_PresentQueue);
    }
    void Devices::create_surface()
    {
        auto res = glfwCreateWindowSurface(m_Instance, (GLFWwindow*)m_Window->Get(), nullptr, &m_Surface);
        ENGINE_ASSERT((res == VK_SUCCESS) && "[VK] Failed to create window surface");
        ENGINE_INFO("[VK] Created window surface");
    }

    SwapChainSupportDetails Devices::query_sc_support(VkPhysicalDevice dev)
    {
        SwapChainSupportDetails details;

        // surface capabilities
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, m_Surface, &details.capabilities);

        // get formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, m_Surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(dev, m_Surface, &formatCount, details.formats.data());
        }

        // get present modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, m_Surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(dev, m_Surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }
}
  