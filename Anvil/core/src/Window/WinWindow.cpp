#include "WinWindow.h"

namespace Anvil
{
	WinWindow::WinWindow(WindowProps _p)
	{
		Init(_p);
	}

	void WinWindow::Init(const WindowProps& _p)
	{
		if (!glfwInit())
			ENGINE_ERROR("Failed to init glfw");

		// API selection made by renderer, not GLFW
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// TODO: Window resizing
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_WinHandle = glfwCreateWindow(_p.width, _p.height, _p.name, NULL, NULL);

		ENGINE_ASSERT((m_WinHandle != NULL) && "Failed to create window: {}", _p.name);
		ENGINE_INFO("Window Created: {}", _p.name);
	}

	WinWindow::~WinWindow()
	{
		glfwTerminate();
	}

	void WinWindow::PollEvents()
	{
		glfwPollEvents();
	}

	bool WinWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_WinHandle);
	}
}