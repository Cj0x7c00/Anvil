#include "anvApplication.hpp"
#include "../Util/Time/Time.h"
#include "../Renderer/Renderer.h"

namespace Anvil{

    AnvilApplication::AnvilApplication()
    {
        WindowProps p;
        m_Window = Window::Create(p);

       Renderer::Init(m_Window);
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
        ENGINE_INFO("Popping Layer {}", _layer->GetName());
        m_LayerStack.PopLayer(_layer);
    }

}



