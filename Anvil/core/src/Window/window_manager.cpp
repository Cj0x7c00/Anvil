#include "window_manager.hpp"
namespace Anvil
{



    void WindowManager::CreateVulkanWindow(){

        ENGINE_INFO("Creating Vulkan Window", " ");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        GLFWwindow* nWin = glfwCreateWindow(width, height, ENGINE_NAME, NULL, NULL);
        windows.push_back(nWin);
        glfwSetWindowUserPointer(nWin, this);
        glfwSetFramebufferSizeCallback(nWin, FramebufferResizeCallback);

    }

    WindowManager::WindowManager(int w, int h, const char* n) : width{static_cast<uint32_t>(w)}, height{static_cast<uint32_t>(h)}, name{n}
    {
        // init glfw
        if(!glfwInit()){
            ENGINE_ERROR("Failed to init glfw", " ");
        }
    }

    void WindowManager::CreateWindow()
    {
        #ifdef PLATFORM_APPLE
        if (glfwVulkanSupported() == GLFW_TRUE){
            CreateVulkanWindow();
        } else{
            ENGINE_ERROR("Vulkan is not supported on this device! make sure you have the SDK installed!", "CreateWindow()");
        }
        #else
        std::cerr << "Unknown Platform!\n";
        #endif
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