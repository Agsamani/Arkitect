#pragma once
#include "rktpch.h"
#include "window/Window.h"
#include "events/Event.h"

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

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		friend int ::main(int argc, char** argv);
	};

	static Application* CreateApplication();
}

