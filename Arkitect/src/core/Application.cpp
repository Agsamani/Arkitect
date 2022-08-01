#include "rktpch.h"
#include "Application.h"

#include "Utils.h"
#include "Base.h"


namespace Arkitect {

	// TODO : singleton maybe

	Application::Application()
	{
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(RKT_BIND_EVENT_FN(OnEvent));
	}

	void Application::run()
	{
		while (m_Running)
		{
			float currentTime = Time::GetTime();
			Deltatime dt = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;

			m_Window->OnUpdate();

			for (Layer* layer : layerStack) {
				layer->OnUpdate(dt);
			}
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RKT_BIND_EVENT_FN(OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(RKT_BIND_EVENT_FN(OnWindowResizeEvent));

		for (Layer* layer : layerStack) {
			if (e.Handled) {
				break;
			}
			layer->OnEvent(e);
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
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