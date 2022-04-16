#pragma once
#include "anvLog.hpp"
#include "anvpch.hpp"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "settings.hpp"
#include "anvDevice.hpp" // vulkan
#include "include/stb/stb_image.h" // load image icon

namespace AnvilEngine
{

    // Window Management class
    class WindowManager{

        public:

            GLFWwindow* Window;

            uint32_t width;
	        uint32_t height;
            bool framebufferResized = false;

            const char* name;

            WindowManager(int w, int h, const char* n);
            
            //creates a basic GLFW window
            void CreateSimpleWindow();

            // creates a vulkan window
            void CreateVulkanWindow();

            void ResetWindowResizedFlag() { framebufferResized = false; }

            bool WasWindowResized() { return framebufferResized; }

            static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);


            VkExtent2D GetExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }



            
    }; //class


} //AnvilEngine

