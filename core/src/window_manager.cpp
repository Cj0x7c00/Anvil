#include "window_manager.hpp"
namespace AnvilEngine
{

    void WindowManager::CreateSimpleWindow(){
       
        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);

        glfwMakeContextCurrent(Window);

        if (!Window){
            glfwTerminate();
            ENGINE_ERROR("Failed to create window");
        }
    }

    void WindowManager::CreateVulkanWindow(){

        ENGINE_INFO("Creating Vulkan Window");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        Window = glfwCreateWindow(width, height, "Engine 0.0.0", NULL, NULL);
        vkobj.InitVulkan(Window);

#ifndef PLATFORM_APPLE
        // load image 
        int width, height, channels;
        unsigned char* pixles  = stbi_load("../extras/Icon3.png", &width, &height, &channels, 4);

        // change icon
        GLFWimage image[1];
        image[0].width = width;
        image[0].height = height;
        image[0].pixels = pixles;

        glfwSetWindowIcon(Window, 1, image);
#endif

        // if on apple devices, the app icon will be handled by the app bundle system on apple devices

    }

    void WindowManager::Init(){

        // init glfw
        if(!glfwInit()){
            ENGINE_ERROR("Failed to init glfw");
        }

        // Graphics API switch
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