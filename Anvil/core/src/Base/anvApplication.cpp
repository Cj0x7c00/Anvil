#include "anvApplication.hpp"
#include "../Util/Time/Time.h"
#include "../Util/TaskRunner/TaskRunner.h"
#include "../Renderer/Renderer.h"

namespace Anvil{

    std::string AnvilApplication::m_DllDir = std::string();

    AnvilApplication::AnvilApplication(AppProperties& _p)
    {
        set_dll_dir();
        m_Window = Window::Create(_p.win_props);
        Renderer::Init(m_Window, &m_SceneManager);
    }

    AnvilApplication::~AnvilApplication()
    {
        m_LayerStack.~LayerStack();
    }

    void AnvilApplication::Run()
    {
        Awake();
        Renderer::BeginOneTimeOps();
        while (!m_Window->ShouldClose()) {

            m_Window->PollEvents();
			Update();
			Renderer::NewFrame();
			LateUpdate();
        }
		Renderer::WaitIdle();
    }

    Ref<Window> AnvilApplication::GetWindow()
    {
        return m_Window;
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



