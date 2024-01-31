#include "Window.hpp"

#include "WinWindow.h"

namespace Anvil
{
	Ref<Window> Window::Create(WindowProps _p)
	{
		return CreateRef<WinWindow>(_p);
	}
}