#pragma once
#include "../Window/Window.hpp"
//#include "../Layer/anvLayerStack.hpp"
#include "../Util/Time/anvTimeStep.hpp"
#include "Pointer.hpp"
#include "settings.hpp"

namespace Anvil
{

    class ANV_API AnvilApplication
    {

    public:

        AnvilApplication();   
        //void PushLayer(AnvilLayer* layer);
        //void PopLayer(AnvilLayer* layer);

        virtual void Run() = 0;

        Ref<Window> GetWindow();

        void print();

    private:
        Ref<Window>    m_Window;
    };
    
    AnvilApplication* CreateApplication();

}
