#pragma once
#include "settings.hpp"
#include "anvpch.hpp"

/**
 * 
 * @brief Basically, all this is is just geting the required vulkan stuf
 * out of the way. later on i will make a class specificaly for vulkan. 
 * right now i just want to get vulkan running on the window and render a
 * basic triangle. "small" things first, ya know? 
 * 
 */

namespace AnvilEngine{

    class VK_OBJ
    {

        public:

            VkInstance m_instance = VK_NULL_HANDLE;
            VkDevice m_device = VK_NULL_HANDLE;
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkQueue m_graphicsQueue = VK_NULL_HANDLE;
            VkSurfaceKHR m_surface = VK_NULL_HANDLE;
            
            const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

            VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
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

            void CreateInstance();

            VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, 
                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
                const VkAllocationCallbacks* pAllocator, 
                VkDebugUtilsMessengerEXT* pDebugMessenger);

            void DestroyDebugUtilsMessengerEXT(VkInstance instance, 
                VkDebugUtilsMessengerEXT debugMessenger, 
                const VkAllocationCallbacks* pAllocator);

            bool checkValidationLayerSupport();

            std::vector<const char*> getRequiredExtensions();
            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debCreateInfo);

            void SetupDebugMessenger();
            
            void PickPhysicalDevice();

            bool isDeviceSuitable(VkPhysicalDevice device);

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            void CreateLogicalDevice();

            void InitVulkan();

            void CreateSurface(GLFWwindow* window);

            void Clean();
    };

    VK_OBJ vkobj;



} //AnvilEngine
