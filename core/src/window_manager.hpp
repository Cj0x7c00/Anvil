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

            const uint32_t width;
	        const uint32_t height;
            const char* name;

            WindowManager(int w, int h, const char* n);
            
            //creates a basic GLFW window
            void CreateSimpleWindow();

            // creates a vulkan window
            void CreateVulkanWindow();


            VkExtent2D GetExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }



            
    }; //class


} //AnvilEngine

