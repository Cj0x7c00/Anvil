#pragma once
#include "window_manager.cpp"
#include "anvRenderer.cpp"
#include <GLFW/glfw3.h>


namespace AnvilEngine{

    class AnvilEngineApplication{
        public:
            WindowManager WindowManager;
            anvRenderer Renderer;
        

            AnvilEngineApplication()
            {
                ENGINE_INFO("Starting Engine");
                ENGINE_INFO(glfwGetVersionString());

                // Engine Initiations
                WindowManager.Init();
                Renderer.Init(WindowManager.Window);

            }

            void Run(){
                ENGINE_INFO("Running. . .");
                while (!glfwWindowShouldClose(WindowManager.Window)){

                    glfwPollEvents();
                }
            }

            ~AnvilEngineApplication(){
                ENGINE_INFO("Stopping Engine");
                Renderer.Clean();
                vkobj.Clean();
                glfwDestroyWindow(WindowManager.Window);
                glfwTerminate();
            }

    };

}
