#pragma once
#include "rktpch.h"
#include "window/Window.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace Arkitect {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		Window& GetWindow() { return *m_Window; }

		void OnEvent(Event& e);
		void Close();

	private:
		void run();
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		bool m_Minimized = false;

		friend int ::main(int argc, char** argv);
	};

	static Application* CreateApplication();
}

