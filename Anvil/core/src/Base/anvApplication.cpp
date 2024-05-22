#include "anvApplication.hpp"
#include "../Util/Time/Time.h"
#include "../Util/TaskRunner/TaskRunner.h"
#include "../Renderer/Renderer.h"

namespace Anvil{

    Ref<Window> AnvilApplication::m_Window = nullptr;


    std::string AnvilApplication::m_DllDir = std::string();

    AnvilApplication::AnvilApplication(AppProperties& _p) : m_Props{_p}
    {
        set_dll_dir();
        m_Window = Window::Create(_p.win_props);
        Renderer::Init(m_Window, &m_SceneManager);
    }

    AnvilApplication::~AnvilApplication()
    {

    }

    void AnvilApplication::Run()
    {
        Awake();
        Renderer::BeginOneTimeOps();
        ENGINE_DEBUG("{}", m_Props.wrkdir);
        std::filesystem::current_path(m_Props.wrkdir.c_str());
        while (!m_Window->ShouldClose()) {

            m_Window->PollEvents();

			Update();
            
			Renderer::NewFrame();

            for (auto& Layer : m_LayerStack.GetLayers())
            {
                Layer->Update();
            }

			LateUpdate();

        }
		Renderer::WaitIdle();
    }

    void AnvilApplication::PushLayer(AnvilLayer* _layer)
    {

        ENGINE_INFO("Pushing Layer \"{}\"", _layer->GetName());
        m_LayerStack.PushLayer(_layer);
    }

    void AnvilApplication::PopLayer(AnvilLayer* _layer)
    {

        ENGINE_INFO("Popping Layer \"{}\"", _layer->GetName());
        m_LayerStack.PopLayer(_layer);
    }

    void AnvilApplication::set_dll_dir()
    {
       std::filesystem::current_path("..\\Anvil\\");
       m_DllDir = std::filesystem::current_path().string();
    }

}



