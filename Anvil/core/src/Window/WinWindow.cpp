#include "WinWindow.h"
#include "../Renderer/Renderer.h"

namespace Anvil
{
	WindowProps WinWindow::m_Props = WindowProps();

	void WinWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<WinWindow*>(glfwGetWindowUserPointer(window));
		m_Props.width = width;
		m_Props.height = height;

		Renderer::WindowWasResized();
	}

	WinWindow::WinWindow(WindowProps _p) 
	{
		Init(_p);
	}

	void WinWindow::Init(WindowProps _p)
	{
		m_Props = _p;
		if (!glfwInit())
			ENGINE_ERROR("Failed to init glfw");
		if (m_Props.maximized == true)
		{

			// API selection made by renderer, not GLFW
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			//maximized
			glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

			//// no decoration
			//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);


			m_WinHandle = glfwCreateWindow(_p.width, _p.height, _p.name, NULL, NULL);
			glfwSetWindowUserPointer(m_WinHandle, this);

			glfwSetFramebufferSizeCallback(m_WinHandle, framebufferResizeCallback);

		} else {
			// API selection made by renderer, not GLFW
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			m_WinHandle = glfwCreateWindow(_p.width, _p.height, _p.name, NULL, NULL);
			glfwSetWindowUserPointer(m_WinHandle, this);

			glfwSetFramebufferSizeCallback(m_WinHandle, framebufferResizeCallback);
		}

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

	bool WinWindow::WasWindowResized()
	{
		return false;
	}

	void* WinWindow::GetSurface()
	{
		return m_Surface;
	}
}