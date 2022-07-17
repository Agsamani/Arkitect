#include "rktpch.h"
#include "Window.h"

#include "GLFW/glfw3.h"

namespace Arkitect {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		RKT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(int width , int height , std::string title)
	{
		Init(width, height, title);
	}

	void Window::Init(int width, int height, std::string title)
	{
		m_Data.width = width;
		m_Data.height = height;
		m_Data.title = title;

		if (s_GLFWWindowCount == 0) {
			if (!glfwInit()) {
				RKT_CORE_ERROR("GLFW error initializing");
			}
		}

		#if defined(RKT_DEBUG)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

		m_GLFWwindow = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), NULL, NULL);
		if (!m_GLFWwindow)
		{
			glfwTerminate();
			RKT_CORE_ERROR("GLFW error creating window");
		}
		++s_GLFWWindowCount;
		glfwMakeContextCurrent((GLFWwindow*)m_GLFWwindow);
		glfwSetWindowUserPointer((GLFWwindow*)m_GLFWwindow, &m_Data);
		SetVSync(true);

	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers((GLFWwindow*)m_GLFWwindow);
		glfwPollEvents();
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.vsync = enabled;
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow((GLFWwindow*)m_GLFWwindow);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

}