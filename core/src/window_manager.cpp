#include "window_manager.hpp"

namespace SimpleEngine{

    void WindowManager::CreateSimpleWindow(){

        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
        glfwMakeContextCurrent(Window);

        if (!Window){
            glfwTerminate();
            LOGGER.LOG("failed to create window", 2);
            glfwTerminate();
        }
    }

    void WindowManager::CreateVulkanWindow(){

        LOGGER.LOG("creating vulkan window", 1);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
        vkobj.InitVulkan();
    }

    void WindowManager::Init(){

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

    bool WindowManager::CheckForVulkanSupport(){
        if (GLFW_TRUE == glfwVulkanSupported())
        {
            LOGGER.LOG("Vulkan is Supported!", 0);
            return true;
        } else {
            LOGGER.LOG("Vulkan not supported!", 0);
            return false;
        }
    }
        
    

}