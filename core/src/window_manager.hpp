#pragma once



#include <iostream>
#include <vector>

#include "simple_logger.hpp"
#include "vk_object.hpp"

#include "../include/Vulkan/vulkan.h"
#include "../include/GLFW/glfw3.h"



namespace SimpleEngine
{

    // Window Management class
    class SEWindow{

        public:

            GLFWwindow* seWindow;

            const uint32_t width		= 800;
	        const uint32_t height		= 600;

            void CreateSimpleWindow(){

                seWindow = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
                glfwMakeContextCurrent(seWindow);

                if (!seWindow){
                    glfwTerminate();
                    LOGGER.LOG("failed to create window", 2);
                    glfwTerminate();
                }
            }

            void CreateVulkanWindow(){

                LOGGER.LOG("creating vulkan window", 1);
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

                seWindow = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
                vkobj.InitVulkan();



            }

            // Check for vk support. If not, we will use a basic window
            bool CheckForVulkanSupport(){
                if (GLFW_TRUE == glfwVulkanSupported())
                {
                    LOGGER.LOG("Vulkan is Supported!", 0);
                    return true;
                } else {
                    LOGGER.LOG("Vulkan not supported!", 0);
                    return false;
                }
            }

            // Init glfw and see if vulkan is supported
            void Init(){

                // init glfw
                if(!glfwInit()){
                    LOGGER.LOG("Couldnt init glfw library", 2);
                }

                // check if we cam do better than OpeGL
                if (CheckForVulkanSupport()){
                    CreateVulkanWindow();
                } else{
                    CreateSimpleWindow();
                }
            }

            
    }; //class

} //SimpleEngine

