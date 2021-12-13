#pragma once

#include "simple_logger.hpp"

#include "../include/Vulkan/vulkan.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>
#include <vector>

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

            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

#ifdef NDEBUG
            const bool enableValidationLayers = false;
#else
            const bool enableValidationLayers = true;
#endif

            void CreateInstance(){

                VkApplicationInfo appInfo{};
                appInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                appInfo.pApplicationName    = "Engine 0.0.0";
                appInfo.applicationVersion  = VK_MAKE_VERSION(1, 0, 0);
                appInfo.pEngineName         = "Engine";
                appInfo.engineVersion       = VK_MAKE_VERSION(1, 0, 0);
                appInfo.apiVersion          = VK_API_VERSION_1_0;

                VkInstanceCreateInfo createInfo{};
                createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                createInfo.pApplicationInfo = &appInfo;

                uint32_t glfwExtensionCount = 0;
                const char** glfwExtensions;

                glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

                createInfo.enabledExtensionCount    = glfwExtensionCount;
                createInfo.ppEnabledExtensionNames  = glfwExtensions;

                createInfo.enabledLayerCount        = 0;

                VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance); 

                if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
                    LOGGER.LOG("Failed to create instance", 2);
                }

                uint32_t extensionCount = 0;
                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

                std::vector<VkExtensionProperties> extensions(extensionCount);

                vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

                std::cout << "available extensions:\n";

                for (const auto& extension : extensions) {
                    std::cout << '\t' << extension.extensionName << '\n';
                }
            }

            bool checkValidationLayerSupport() {
                uint32_t layerCount;
                vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

                std::vector<VkLayerProperties> availableLayers(layerCount);
                vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

                return false;
            }

            


    };



} //SimpleEngine

