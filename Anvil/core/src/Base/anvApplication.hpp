#pragma once

#include "../Window/Window.hpp"
#include "../Util/Time/anvTimeStep.hpp"
#include "../Layer/anvLayerStack.hpp"
#include "Pointer.hpp"
#include "macros.hpp"

namespace Anvil
{

    class Renderer;

    struct AppProperties
    {
        std::string name;
        std::string wrkdir;

        bool maximized = false;

        WindowProps win_props;

        AppProperties(std::string _name = "Anvil App", std::string _wrkdir = "", 
            bool _maximized = false, WindowProps _p = WindowProps())
            : name{ name }, wrkdir{ _wrkdir }, maximized{ _maximized }, win_props{_p}
        {
            if (wrkdir == "")
            {
                wrkdir = std::filesystem::current_path().string();
            }
        }
    };

    class ANV_API AnvilApplication
    {

    public:

        AnvilApplication(AppProperties& _p);
        ~AnvilApplication();
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
