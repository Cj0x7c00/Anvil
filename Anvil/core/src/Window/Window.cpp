#include "Window.hpp"
#include "WinWindow.h"
#include <vulkan/vulkan.h>

namespace Anvil
{
	Ref<Window> Window::Create(WindowProps _p)
	{
		return CreateRef<WinWindow>(_p);
	}
	Extent2D Extent2D::operator=(VkExtent2D& ext)
	{

		Extent2D ex;
		ex.width = ext.width;
		ex.height = ext.height;
		return ex;
		
	}
}