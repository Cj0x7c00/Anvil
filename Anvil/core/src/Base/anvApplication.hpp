#pragma once

#include "../Window/Window.hpp"
#include "../Util/Time/anvTimeStep.hpp"
#include "../Layer/anvLayerStack.hpp"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "Pointer.hpp"
#include "macros.hpp"

namespace Anvil
{

    class Renderer;

    /// <summary>
    /// Struct used to configure the application,
    /// </summary>
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

    /// <summary>
    /// Main class for anvil
    /// </summary>
    class ANV_API AnvilApplication
    {

    public:

        AnvilApplication(AppProperties& _p);
        ~AnvilApplication();

        void Run();

        /// <summary>
        /// Called after construction
        /// </summary>
        virtual void Awake() = 0;

        /// <summary>
        /// Called once per frame
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Called after rendering
        /// </summary>
        virtual void LateUpdate() = 0;

        /// <summary>
        /// Push a Layer on the LayerStack
        /// </summary>
        /// <param name="_layer">A pointer to a layer</param>
        void PushLayer(AnvilLayer* _layer);

        /// <summary>
        /// Pop a layer off of the Layer Stack
        /// </summary>
        /// <param name="_layer"></param>
        void PopLayer(AnvilLayer* _layer);

        /// <summary>
        /// Get the main window in use
        /// </summary>
        /// <returns>Ref<Window></returns>
        static Ref<Window> GetWindow()
        {
            return m_Window;
        }

        /// <summary>
        /// Get the main DLL work directory
        /// </summary>
        /// <returns></returns>
        static std::string GetLibDir() { return m_DllDir; }

    private:
        void set_dll_dir();
        static std::string m_DllDir;

    protected:
        static Ref<Window>    m_Window;
        Ref<Renderer>  m_Renderer;

        SceneManager   m_SceneManager;
        LayerStack     m_LayerStack;

        AppProperties m_Props;
    };
    
    /// <summary>
    /// Engine entry point
    /// </summary>
    /// <returns>AnvilApplication*</returns>
    AnvilApplication* CreateApplication();

}