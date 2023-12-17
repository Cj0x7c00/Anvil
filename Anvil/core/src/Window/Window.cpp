#include "Window.hpp"
namespace Anvil
{

    void Window::CreateSimpleWindow(){
       
        m_Props.Window = glfwCreateWindow(m_Props.width, m_Props.height, m_Props.name, NULL, NULL);

        glfwMakeContextCurrent(m_Props.Window);

        if (!m_Props.Window){
            glfwTerminate();
            ENGINE_ERROR("Failed to create window");
        }
    }

    void Window::CreateVulkanWindow(){

        ENGINE_INFO("Creating Vulkan Window");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        m_Props.Window = glfwCreateWindow(m_Props.width, m_Props.height, "Anvil", NULL, NULL);
        glfwSetWindowUserPointer(m_Props.Window, this);
        glfwSetFramebufferSizeCallback(m_Props.Window, FramebufferResizeCallback);


#ifdef PLATFORM_APPLE
        /**
         * 
         *  the `glfwSetWindowIcon()` function does nothing on apple devices. 
         *  so we have to make an application bundle for our engine.
         *  very simple stuff. I used an app called "Image2Icon" to make the ICNS file.
         * 
        **/
        ENGINE_INFO("Apple Platform Detected");
#endif

    }

    Window::Window(WindowProps _p) : m_Props{_p}
    {

        // init glfw
        if(!glfwInit()){
            ENGINE_ERROR("Failed to init glfw");
        }

        // Graphics API switch
        if ((glfwVulkanSupported() == GLFW_TRUE)){
            CreateVulkanWindow();
        } else{
            ENGINE_INFO("Creating simple window", " ");

#ifdef PLATFORM_APPLE            
                ENGINE_ERROR("OpenGL is no longer supported on apple devices and Vulkan is not supported.", " ");
                CreateSimpleWindow();
#endif
            }
    }


    void Window::FramebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        auto anvWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        anvWindow->m_Props.framebufferResized = true;
        anvWindow->m_Props.width = width;
        anvWindow->m_Props.height = height;
        anvWindow->ResetWindowResizedFlag();
    }

}