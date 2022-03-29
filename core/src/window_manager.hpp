#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "anvpch.cpp"
#include <GLFW/glfw3.h>
#include "settings.hpp"
#include "anvDevice.cpp" // vulkan
#include "../include/stb/stb_image.h" // load image ico

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
            ~WindowManager();

            //creates a basic GLFW window
            void CreateSimpleWindow();

            // creates a vulkan window
            void CreateVulkanWindow();


            VkExtent2D GetExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }



            
    }; //class


} //AnvilEngine

