#pragma once
#include "settings.hpp"
#include "anvpch.hpp"

namespace AnvilEngine{

/**
 * 
 * @brief Basically, all this is is just geting the required vulkan stuf
 * out of the way. later on i will make a class specificaly for vulkan. 
 * right now i just want to get vulkan running on the window and render a
 * basic triangle. "small" things first, ya know? 
 * 
 */

    class VK_OBJ
    {

        public:
            VkInstance m_instance;
            VkDevice m_device;
            VkPhysicalDevice m_physicalDevice;
            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
            VkSurfaceKHR m_surface;

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            
            const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
            const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, "VK_KHR_portability_subset"};

            VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
            VkDebugUtilsMessengerCreateInfoEXT debCreateInfo{};

            struct QueueFamilyIndices {
                std::optional<uint32_t> graphicsFamily;
                std::optional<uint32_t> presentFamily;

                bool isComplete() {
                    return graphicsFamily.has_value() && presentFamily.has_value();
                }
            };

            struct SwapChainSupportDetails {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentModes;
            };

#ifdef NDEBUG
            const bool enableValidationLayers = false;
#else
            const bool enableValidationLayers = true;
#endif

            

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

            void CreateInstance();

            void PickPhysicalDevice();

            //bool isDeviceSuitable(VkPhysicalDevice device);

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            bool CheckDeviceExtentionSupport(VkPhysicalDevice device);

            void CreateLogicalDevice();

            void InitVulkan(GLFWwindow* window);

            void CreateSurface(GLFWwindow* window);

            // VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

            // VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

            // VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

            // SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

            // void CreateSwapChain(GLFWwindow* window);

            void Clean();
    };

    VK_OBJ vkobj;



} //AnvilEngine