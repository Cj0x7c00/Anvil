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

}



