#pragma once

#include "../include/GLFW/glfw3.h"
#include "window_manager.cpp"
#include "vk_object.cpp"

namespace SimpleEngine{

    class App{
        public:
            WindowManager WindowManager;
            VK_OBJ vkobj;

            void Start(){
                
                WindowManager.Init();
        
                while (!glfwWindowShouldClose(WindowManager.Window)){

                    glfwPollEvents();
                }
            }

            void ShutDown(){
                vkobj.Clean();
                glfwDestroyWindow(WindowManager.Window);
                glfwTerminate();
            }
    };

}
