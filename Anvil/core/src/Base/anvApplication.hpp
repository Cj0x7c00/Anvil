#pragma once

#include "../Window/Window.hpp"
#include "../Util/Time/anvTimeStep.hpp"
#include "../Layer/anvLayerStack.hpp"
#include "Pointer.hpp"
#include "macros.hpp"

namespace Anvil
{

    class Renderer;

    class ANV_API AnvilApplication
    {

    public:

        AnvilApplication();   

        virtual void Run() = 0;

        Ref<Window> GetWindow();

        void PushLayer(AnvilLayer* _layer);
        void PopLayer(AnvilLayer* _layer);

    protected:
        Ref<Window>    m_Window;
        Ref<Renderer>  m_Renderer;

        LayerStack     m_LayerStack;
    };
    
    AnvilApplication* CreateApplication();

}
