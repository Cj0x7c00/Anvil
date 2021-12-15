#include "vk_object.hpp"

namespace SimpleEngine{

    void VK_OBJ::CreateInstance(){
                 if (enableValidationLayers && !checkValidationLayerSupport()) {
                    throw std::runtime_error("validation layers requested, but not available!");
                }

                VkApplicationInfo appInfo{};
                appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName = "Hello Triangle";
                appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
                appInfo.pEngineName = "No Engine";
                appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
                appInfo.apiVersion = VK_API_VERSION_1_0;

                VkInstanceCreateInfo instCreateInfo{};
                instCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                instCreateInfo.pApplicationInfo = &appInfo;

                const char* instExtension = "VK_KHR_get_physical_device_properties2";

                auto extensions = getRequiredExtensions();
                instCreateInfo.enabledExtensionCount = 1; //static_cast<uint32_t>(extensions.size())
                instCreateInfo.ppEnabledExtensionNames = &instExtension; //extensions.data()

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
                    throw std::runtime_error("failed to create instance!");
                }
                LOGGER.LOG("Created vulkan instance", 1);
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
                    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
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

 
            /*
            void VK_OBJ::SetupDebugMessenger(){
                if (!enableValidationLayers) return;

                VkDebugUtilsMessengerCreateInfoEXT debCreateInfo;
                populateDebugMessengerCreateInfo(debCreateInfo);

                if (CreateDebugUtilsMessengerEXT(m_instance, &debCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                    throw std::runtime_error("failed to set up debug messenger!");
                }
            }
            */

            void VK_OBJ::PickPhysicalDevice(){
                LOGGER.LOG("Picking physical device", 0);

                uint32_t deviceCount = 0;
                vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

                if (deviceCount == 0) {
                    throw std::runtime_error("failed to find GPUs with Vulkan support!");
                }

                std::vector<VkPhysicalDevice> devices(deviceCount);
                vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

                for (const auto& device : devices) {
                    if (isDeviceSuitable(device)) {
                        physicalDevice = device;
                        break;
                    }
                }

                if (physicalDevice == VK_NULL_HANDLE) {
                    throw std::runtime_error("failed to find a suitable GPU!");
                }

            }

            bool VK_OBJ::isDeviceSuitable(VkPhysicalDevice device) {
                QueueFamilyIndices indices = findQueueFamilies(device);

                return indices.isComplete();
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

                    if (indices.isComplete()) {
                        break;
                    }

                    i++;
                }

                return indices;
            }

            void VK_OBJ::CreateLogicalDevice(){
                LOGGER.LOG("Creating Logical Device", 0);

                QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
                queueCreateInfo.queueCount = 1;

                float queuePriority = 1.0f;
                queueCreateInfo.pQueuePriorities = &queuePriority;

                VkPhysicalDeviceFeatures deviceFeatures{};

                VkDeviceCreateInfo devCreateInfo{};
                devCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

                const char* deviceExtension = "VK_KHR_portability_subset";

                devCreateInfo.pQueueCreateInfos = &queueCreateInfo;
                devCreateInfo.queueCreateInfoCount = 1;

                devCreateInfo.pEnabledFeatures = &deviceFeatures;

                devCreateInfo.enabledExtensionCount = 1;
                devCreateInfo.ppEnabledExtensionNames = &deviceExtension;

                if (enableValidationLayers) {
                    devCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                    devCreateInfo.ppEnabledLayerNames = validationLayers.data();
                } else {
                    devCreateInfo.enabledLayerCount = 0;
                }

                if (vkCreateDevice(physicalDevice, &devCreateInfo, nullptr, &device) != VK_SUCCESS) {
                    LOGGER.LOG("Failed to create logical device", 2);
                }

                vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            }

            void VK_OBJ::InitVulkan(){
                LOGGER.LOG("Initializing Vulkan", 1);
                CreateInstance();
                //SetupDebugMessenger();
                PickPhysicalDevice();
                CreateLogicalDevice();
            }

            void VK_OBJ::Clean(){
                if (enableValidationLayers){
                    DestroyDebugUtilsMessengerEXT(m_instance, debugMessenger, nullptr);
                }
                vkDestroyInstance(m_instance, nullptr);
                vkDestroyDevice(device, nullptr);
            }
}