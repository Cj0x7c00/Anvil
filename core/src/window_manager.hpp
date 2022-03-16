#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "anvpch.cpp"
#include <GLFW/glfw3.h>
#include "settings.hpp"
#include "vk_object.cpp" // vulkan
#include "../include/stb/stb_image.h" // load image icon
#include "../include/stb/stb_image_write.h"



namespace AnvilEngine
{

    // Window Management class
    class WindowManager{

        public:

            GLFWwindow* Window;

            const uint32_t width		= 800;
	        const uint32_t height		= 600;

            //creates a basic GLFW window
            void CreateSimpleWindow();

            // creates a vulkan window
            void CreateVulkanWindow();

            // Init glfw and see if vulkan is supported
            void Init();

            // Check for vk support. If not, we will use a basic window
            bool CheckForVulkanSupport();



            
    }; //class


} //AnvilEngine

