#pragma once

#include "../Window/Window.hpp"
#include "../Util/Time/anvTimeStep.hpp"
#include "../Layer/anvLayerStack.hpp"
#include "../Scene/SceneManager.h"
#include "Pointer.hpp"
#include "macros.hpp"

namespace Anvil
{

    class Renderer;

    struct AppProperties
    {
        std::string name;
        std::string wrkdir;

        WindowProps win_props;

        AppProperties(std::string _name = "Anvil App", std::string _wrkdir = "", 
            WindowProps _p = WindowProps())
            : name{ name }, wrkdir{ _wrkdir }, win_props{_p}
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
        void Run();
        virtual void Awake() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;

        void PushLayer(AnvilLayer* _layer);
        void PopLayer(AnvilLayer* _layer);

        Ref<Window> GetWindow();

        static std::string GetLibDir() { return m_DllDir; }
    private:
        void set_dll_dir();
        static std::string m_DllDir;

    protected:
        Ref<Window>    m_Window;
        Ref<Renderer>  m_Renderer;

        SceneManager   m_SceneManager;
        LayerStack     m_LayerStack;
    };
    
    AnvilApplication* CreateApplication();

}
