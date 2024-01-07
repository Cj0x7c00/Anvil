#pragma once

#include "Window.hpp"

#include <GLFW/glfw3.h>

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

        virtual void* Get() override { return nullptr; };

        virtual bool WasWindowResized() override { return false; };


        virtual Extent2D GetExtent() override { return Extent2D(); };

    private:
        void Init(const WindowProps& _p);

    private:
        GLFWwindow* m_WinHandle;
    };
}
