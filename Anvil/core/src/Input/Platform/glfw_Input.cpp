
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

	std::pair<float, float> glfw_Input::Impl_GetMousePos()
	{
		auto window = static_cast<GLFWwindow*>(AnvilApplication::GetWindow()->Get());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float) xpos, (float) ypos };
	}


	void glfw_Input::Impl_SetMouseMode(Anvil::MouseMode _m)
	{
		auto window = static_cast<GLFWwindow*>(AnvilApplication::GetWindow()->Get());
		glfwSetInputMode(window, GLFW_CURSOR, (_m == MOUSE_MODE_FREE) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
}
