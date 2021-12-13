#pragma once

#include "../include/GLFW/glfw3.h"
#include "window_manager.hpp"
#include "vk_object.hpp"

namespace SimpleEngine{

    class App{
        public:
            SimpleEngine::SEWindow SEWindow;
            SimpleEngine::VK_OBJ vkobj;

            void Start(){
                
                SEWindow.Init();
        
                while (!glfwWindowShouldClose(SEWindow.seWindow)){

                    glfwPollEvents();
                }
            }

            void ShutDown(){
                //vkDestroyDevice( SEWindow.device, nullptr );
	            vkDestroyInstance( vkobj.m_instance, nullptr );
                glfwDestroyWindow(SEWindow.seWindow);
                glfwTerminate();
            }
    };

}
