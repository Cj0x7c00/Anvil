#include "window_manager.hpp"
namespace AnvilEngine
{

    void WindowManager::CreateSimpleWindow(){
       
        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);

        glfwMakeContextCurrent(Window);

        if (!Window){
            glfwTerminate();
            ENGINE_ERROR("Failed to init glfw");
        }
    }

    void WindowManager::CreateVulkanWindow(){

        ENGINE_DEBUG("Creating Vulkan Window");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
        vkobj.InitVulkan();
        vkobj.CreateSurface(Window);
    }

    void WindowManager::Init(){

        // init glfw
        if(!glfwInit()){
            ENGINE_ERROR("couldn't init glfw");
        }

        // check if we can do better than OpenGL
        if (CheckForVulkanSupport()){
            CreateVulkanWindow();
        } else{
            ENGINE_INFO("Creating simple window");
            ENGINE_WARN("OpenGL is depricated on Apple devices");
            CreateSimpleWindow();
        }
    }

    bool WindowManager::CheckForVulkanSupport(){
        if (GLFW_TRUE == glfwVulkanSupported())
        {
            ENGINE_INFO("VulkanAPI supported");
            return true;
        } else {

            return false;
        }
    }
    
}