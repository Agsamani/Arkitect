#include "rktpch.h"
#include "Application.h"

#include "Base.h"


namespace Arkitect {

	// TODO : singleton maybe

	Application::Application()
	{
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(RKT_BIND_EVENT_FN(OnEvent));
	}

	void Arkitect::Application::run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RKT_BIND_EVENT_FN(OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(RKT_BIND_EVENT_FN(OnWindowResizeEvent));
	}

	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return false;
	}

	Application::~Application()
	{
		
	}
}