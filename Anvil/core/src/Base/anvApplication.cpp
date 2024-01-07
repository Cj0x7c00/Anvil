#include "anvApplication.hpp"

namespace Anvil{

    AnvilApplication::AnvilApplication()
    {
        WindowProps p;
        m_Window = Window::Create(p);
    }

    void AnvilApplication::print()
    {
        ENGINE_INFO("print");
    }

    Ref<Window> AnvilApplication::GetWindow()
    {
        return m_Window;
    }

}



