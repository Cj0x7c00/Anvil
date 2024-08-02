#pragma once
#include "../Input.h"
#include "../Keys.h"
#include <GLFW/glfw3.h>

namespace Anvil
{


    class glfw_Input :
        public Input
    {
    protected:
        virtual bool Impl_IsKeyPressed(int keycode) override;
        virtual std::pair<float, float> Impl_GetMousePos() override;
        virtual void Impl_SetMouseMode(Anvil::MouseMode _m) override;
    };

    Input* Input::sInstance = new glfw_Input();
}
