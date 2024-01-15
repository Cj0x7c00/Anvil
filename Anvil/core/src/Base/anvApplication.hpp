#pragma once

#include "../Window/Window.hpp"
#include "../Util/Time/anvTimeStep.hpp"

#include "Pointer.hpp"
#include "macros.hpp"

namespace Anvil
{

    class Renderer;

    class ANV_API AnvilApplication
    {

    public:

        AnvilApplication();   
        //void PushLayer(AnvilLayer* layer);
        //void PopLayer(AnvilLayer* layer);

        virtual void Run() = 0;

        Ref<Window> GetWindow();

    private:
        Ref<Window>    m_Window;
        Ref<Renderer>  m_Renderer;
    };
    
    AnvilApplication* CreateApplication();

}
