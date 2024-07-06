#include "anvApplication.hpp"
#include "../Util/Time/Time.h"
#include "../Util/TaskRunner/TaskRunner.h"
#include "../Renderer/Renderer.h"

namespace Anvil{

    Ref<Window> AnvilApplication::m_Window = nullptr;

    std::string AnvilApplication::m_DllDir = std::string();
    std::string AnvilApplication::m_WrkDir = std::string();

    AnvilApplication::AnvilApplication(AppProperties& _p) : m_Props{_p}
    {
        set_engine_dirs();
        m_Window = Window::Create(_p.win_props);
        Renderer::Init(m_Window, &m_SceneManager);
        Renderer::BeginOneTimeOps();
    }

    AnvilApplication::~AnvilApplication()
    {

    }

    void AnvilApplication::Run()
    {
        Awake();
        Time::startEngineClock();
        ENGINE_DEBUG("{}", m_Props.wrkdir);
        while (!m_Window->ShouldClose()) {
            Time::update();

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

    void AnvilApplication::set_engine_dirs()
    {
       m_DllDir = ANV_LIB_PATH;
       m_WrkDir = m_Props.wrkdir;
       
       std::filesystem::current_path(m_DllDir);
       ENGINE_DEBUG("\nEngine Install dir {}\nWorking Dir: {}", m_DllDir, m_WrkDir);
    }

}




