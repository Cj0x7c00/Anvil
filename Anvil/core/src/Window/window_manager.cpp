#include "window_manager.hpp"
namespace Anvil
{

    void WindowManager::CreateSimpleWindow(){
       
        Window = glfwCreateWindow(width, height, name, NULL, NULL);

        glfwMakeContextCurrent(Window);

        if (!Window){
            glfwTerminate();
            ENGINE_ERROR("Failed to create window", " ");
        }
    }

    void WindowManager::CreateVulkanWindow(){

        ENGINE_INFO("Creating Vulkan Window", " ");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        Window = glfwCreateWindow(width, height, ENGINE_NAME, NULL, NULL);
        glfwSetWindowUserPointer(Window, this);
        glfwSetFramebufferSizeCallback(Window, FramebufferResizeCallback);


#ifdef PLATFORM_APPLE
        /**
         * 
         *  the `glfwSetWindowIcon()` function does nothing on apple devices. 
         *  so we have to make an application bundle for our engine.
         *  very simple stuff. I used an app called "Image2Icon" to make the ICNS file.
         * 
        **/
        ENGINE_INFO("Apple Platform Detected", " ");
        ENGINE_INFO("Using Apple application bundles", " ");
#endif

    }

    WindowManager::WindowManager(int w, int h, const char* n) : width{static_cast<uint32_t>(w)}, height{static_cast<uint32_t>(h)}, name{n}
    {

        // init glfw
        if(!glfwInit()){
            ENGINE_ERROR("Failed to init glfw", " ");
        }

        // Graphics API switch
        if ((glfwVulkanSupported() == GLFW_TRUE) || PLATFORM_APPLE){
            CreateVulkanWindow();
        } else{
            ENGINE_INFO("Creating simple window", " ");
            ENGINE_WARN("OpenGL is depricated on Apple devices", " ");

            if (PLATFORM_APPLE){
                ENGINE_ERROR("OpenGL is no longer supported on apple devices and Vulkan is not supported.", " ");
            } else{
                CreateSimpleWindow();
            }
        }

    }

    void WindowManager::FramebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        auto anvWindow = reinterpret_cast<WindowManager *>(glfwGetWindowUserPointer(window));
        anvWindow->framebufferResized = true;
        anvWindow->width = width;
        anvWindow->height = height;
        anvWindow->ResetWindowResizedFlag();
    }

}