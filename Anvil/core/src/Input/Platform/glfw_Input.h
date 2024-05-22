#pragma once
#include "../Input.h"
#include <GLFW/glfw3.h>

namespace Anvil
{


    class glfw_Input :
        public Input
    {
    protected:
        virtual bool Impl_IsKeyPressed(int keycode) override;
    };

    Input* Input::sInstance = new glfw_Input();
}
