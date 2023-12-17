#pragma once
#include "../Util/anvLog.hpp"
#include "../anvpch.hpp"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../settings.hpp"
#include "../Vulkan/anvDevice.hpp" // vulkan


namespace Anvil
{
    struct WindowProps
    {
        GLFWwindow* Window;

        uint32_t width;
        uint32_t height;
        bool framebufferResized = false;

        const char* name;

        WindowProps(uint32_t w=900, uint32_t h = 700, const char* n="Window")
            : width{w}, height{h}, name{n}
        {

        }
    };

    // Window Management class
    class Window{

        public:

            static Ref<Window> Create(WindowProps _p)
            {
                return CreateRef<Window>(_p);
            }

            Window(WindowProps _p);
            
            //creates a basic GLFW window
            void CreateSimpleWindow();

            // creates a vulkan window
            void CreateVulkanWindow();

            void ResetWindowResizedFlag() { m_Props.framebufferResized = false; }

            bool WasWindowResized() { return m_Props.framebufferResized; }

            static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

            VkExtent2D GetExtent() { return { m_Props.width, m_Props.height }; }

            GLFWwindow* Get() { return m_Props.Window; }

            bool ShouldClose() { return glfwWindowShouldClose(m_Props.Window); }
         
    private:
        WindowProps m_Props;
            
    }; //class


} //Anvil

