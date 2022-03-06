#pragma once
#include "window_manager.cpp"
#include <GLFW/glfw3.h>


namespace AnvilEngine{

    class AnvilEngineApplication{
        public:
            WindowManager WindowManager;

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
