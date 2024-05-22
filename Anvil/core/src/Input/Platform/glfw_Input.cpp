
#include "glfw_Input.h"
#include <GLFW/glfw3.h>

#include <Base/anvApplication.hpp>

namespace Anvil
{
	bool glfw_Input::Impl_IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(AnvilApplication::GetWindow()->Get());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

}
