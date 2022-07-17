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

		}
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		RKT_CORE_TRACE(e);
	}

	void Application::Close()
	{
		m_Running = false;
	}

}