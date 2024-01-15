#pragma once

#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace Anvil
{
    class WinWindow :
        public Window
    {
    public:
        WinWindow(WindowProps _p);
        ~WinWindow();

        void PollEvents()        override;
        bool ShouldClose()       override;

        virtual void ResetWindowResizedFlag() override {};

        virtual void SetRezizeCallback(ResizeCallbackFn fn) override {};

        virtual void* Get() override { return m_WinHandle; };

        virtual bool WasWindowResized() override { return false; };


        virtual Extent2D GetExtent() override { return Extent2D(); };

        virtual void* GetSurface() override;

    private:
        void Init(const WindowProps& _p);

    private:
        GLFWwindow*  m_WinHandle;
        VkSurfaceKHR m_Surface;
    };
}
