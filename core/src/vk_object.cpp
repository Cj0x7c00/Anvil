#include "vk_object.hpp"

namespace AnvilEngine{

    void VK_OBJ::CreateInstance(){
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            ENGINE_ERROR("Failed to enable validation layers");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Anvil Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Anvil Engine 0.0.0";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instCreateInfo{};
        instCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instCreateInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        extensions.push_back("VK_KHR_get_physical_device_properties2");
        instCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size()); //static_cast<uint32_t>(extensions.size())
        instCreateInfo.ppEnabledExtensionNames = extensions.data(); //extensions.data()

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            instCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instCreateInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            instCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            instCreateInfo.enabledLayerCount = 0;

            instCreateInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&instCreateInfo, nullptr, &m_instance) != VK_SUCCESS) {
            ENGINE_ERROR("Failed to create a vulkan instance");
        }
        ENGINE_INFO("Created Vulkan Instance");
    }


    VkResult VK_OBJ::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(m_instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void VK_OBJ::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(m_instance, debugMessenger, pAllocator);
        }
    }

    bool VK_OBJ::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
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

    std::vector<const char*> VK_OBJ::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VK_OBJ::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
        

        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            // Message is important enough to show
            ENGINE_WARN("== VALIDATION LAYER ==");
            ENGINE_ERROR(pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    void VK_OBJ::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debCreateInfo) {
        debCreateInfo = {};
        debCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debCreateInfo.pfnUserCallback = debugCallback;
    }


    
    void VK_OBJ::SetupDebugMessenger(){
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT debCreateInfo;
        populateDebugMessengerCreateInfo(debCreateInfo);

        if (CreateDebugUtilsMessengerEXT(m_instance, &debCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            ENGINE_ERROR("failed to set up debug messenger!");
        }
    }
    

    void VK_OBJ::PickPhysicalDevice(){
        ENGINE_INFO("Picking physical device");

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            ENGINE_ERROR("failed to find a suitable GPU!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (CheckDeviceExtentionSupport(device)) {
                m_physicalDevice = device;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE) {
            ENGINE_ERROR("failed to find a suitable GPU!");
        } 

    }

    bool VK_OBJ::CheckDeviceExtentionSupport(VkPhysicalDevice device){
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }


    VK_OBJ::QueueFamilyIndices VK_OBJ::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

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

    void VK_OBJ::CreateLogicalDevice(){
        
        QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

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
    
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());;
        createInfo.ppEnabledExtensionNames = deviceExtensions.data(); 

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
            ENGINE_ERROR("failed to create logical device!");
        }

        vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
    }


    // create a vulkan rendering surface on the window
    void VK_OBJ::CreateSurface(GLFWwindow* window)
    {
            // FUCK THIS STUPID FUNCTION KEEPT GIVING ME A EXC_BAD_ACCESS MAN FUCK //
            if (glfwCreateWindowSurface(vkobj.m_instance, window, NULL, &vkobj.m_surface) != VK_SUCCESS){
                ENGINE_ERROR("Failed to create a vulkan suface");
            }
            ENGINE_INFO("Created Window Surface");
    }

    void VK_OBJ::InitVulkan(GLFWwindow* window){
        ENGINE_INFO("Initializing Vulkan");
        CreateInstance();
        SetupDebugMessenger();
        CreateSurface(window);
        PickPhysicalDevice();
        CreateLogicalDevice();
    }

    void VK_OBJ::Clean(){
        ENGINE_INFO("Cleaning up vulkan");

        vkDestroyDevice(m_device, nullptr);
        if (enableValidationLayers){
            DestroyDebugUtilsMessengerEXT(m_instance, debugMessenger, nullptr);
        }

        // always destroy the instance last
        vkDestroyInstance(m_instance, nullptr);
    }

    
}