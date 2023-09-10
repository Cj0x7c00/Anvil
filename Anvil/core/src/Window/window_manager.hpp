#pragma once
#include "../Util/anvLog.hpp"
#include "../anvpch.hpp"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../settings.hpp"
#include "../Vulkan/anvDevice.hpp" // vulkan

#include "../include/stb/stb_image.h" // load image icon


namespace Anvil
{

    // Window Management class
    class WindowManager{

        public:


            std::vector<GLFWwindow*> windows;


            uint32_t width;
	        uint32_t height;
            bool framebufferResized = false;

            const char* name;

            WindowManager(int w, int h, const char* n);

            void CreateWindow();


            // creates a vulkan window
            void CreateVulkanWindow();

            void ResetWindowResizedFlag() { framebufferResized = false; }

            bool WasWindowResized() { return framebufferResized; }

            static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

            VkExtent2D GetExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

         

            
    }; //class


} //Anvil

