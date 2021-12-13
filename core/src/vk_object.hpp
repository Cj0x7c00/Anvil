#pragma once

#include "simple_logger.hpp"

#include "../include/Vulkan/vulkan.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <optional>

/**
 * 
 * @brief Basically, all this is is just geting the required vulkan stuf
 * out of the way. later on i will make a class specificaly for vulkan. 
 * right now i just want to get vulkan running on the window and render a
 * basic triangle. "small" things first, ya know? 
 * 
 */

namespace SimpleEngine{

    class VK_OBJ
    {

        public:

            VkInstance m_instance;
            VkDevice device;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkQueue graphicsQueue;
            
            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            VkDebugUtilsMessengerEXT debugMessenger;
            VkDebugUtilsMessengerCreateInfoEXT debCreateInfo{};

            struct QueueFamilyIndices {
                std::optional<uint32_t> graphicsFamily;

                bool isComplete() {
                    return graphicsFamily.has_value();
                }
            };

#ifdef NDEBUG
            const bool enableValidationLayers = false;
#else
            const bool enableValidationLayers = true;
#endif

           void CreateInstance(){
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

                VkInstanceCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                createInfo.pApplicationInfo = &appInfo;

                auto extensions = getRequiredExtensions();
                createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
                createInfo.ppEnabledExtensionNames = extensions.data();

                VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
                if (enableValidationLayers) {
                    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                    createInfo.ppEnabledLayerNames = validationLayers.data();

                    populateDebugMessengerCreateInfo(debugCreateInfo);
                    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
                } else {
                    createInfo.enabledLayerCount = 0;

                    createInfo.pNext = nullptr;
                }

                if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create instance!");
                }
                LOGGER.LOG("Created vulkan instance", 1);
            }


            VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
                auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
                if (func != nullptr) {
                    return func(m_instance, pCreateInfo, pAllocator, pDebugMessenger);
                } else {
                    return VK_ERROR_EXTENSION_NOT_PRESENT;
                }
            }

            void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
                auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
                if (func != nullptr) {
                    func(m_instance, debugMessenger, pAllocator);
                }
            }

            bool checkValidationLayerSupport() {
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

            std::vector<const char*> getRequiredExtensions() {
                uint32_t glfwExtensionCount = 0;
                const char** glfwExtensions;
                glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

                std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

                if (enableValidationLayers) {
                    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                }

                return extensions;
            }

            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
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

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
                createInfo = {};
                createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                createInfo.pfnUserCallback = debugCallback;
            }

 

            void SetupDebugMessenger(){
                if (!enableValidationLayers) return;

                VkDebugUtilsMessengerCreateInfoEXT createInfo;
                populateDebugMessengerCreateInfo(createInfo);

                if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
                    throw std::runtime_error("failed to set up debug messenger!");
                }
            }

            void PickPhysicalDevice(){
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

            bool isDeviceSuitable(VkPhysicalDevice device) {
                QueueFamilyIndices indices = findQueueFamilies(device);

                return indices.isComplete();
            }

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
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

            void CreateLogicalDevice(){
                LOGGER.LOG("Creating Logical Device", 0);

                QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
                queueCreateInfo.queueCount = 1;

                float queuePriority = 1.0f;
                queueCreateInfo.pQueuePriorities = &queuePriority;

                VkPhysicalDeviceFeatures deviceFeatures{};

                VkDeviceCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

                createInfo.pQueueCreateInfos = &queueCreateInfo;
                createInfo.queueCreateInfoCount = 1;

                createInfo.pEnabledFeatures = &deviceFeatures;

                createInfo.enabledExtensionCount = 0;

                if (enableValidationLayers) {
                    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                    createInfo.ppEnabledLayerNames = validationLayers.data();
                } else {
                    createInfo.enabledLayerCount = 0;
                }

                if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
                    LOGGER.LOG("Failed to create logical device", 2);
                }

                vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            }

            void InitVulkan(){
                LOGGER.LOG("Initializing Vulkan", 1);
                CreateInstance();
                SetupDebugMessenger();
                PickPhysicalDevice();
                CreateLogicalDevice();
            }

            void Clean(){
                if (enableValidationLayers){
                    DestroyDebugUtilsMessengerEXT(m_instance, debugMessenger, nullptr);
                }
                vkDestroyInstance(m_instance, nullptr);
                vkDestroyDevice(device, nullptr);
            }

    };

    VK_OBJ vkobj;



} //SimpleEngine
