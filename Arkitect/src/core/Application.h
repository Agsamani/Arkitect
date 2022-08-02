#pragma once
#include "rktpch.h"
#include "window/Window.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "LayerStack.h"
#include "imgui/ImGuiLayer.h"

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *m_Instance; }
	private:
		void run();
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		bool m_Minimized = false;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack layerStack;

		float m_LastFrameTime = 0.0;

		static Application* m_Instance;
		friend int ::main(int argc, char** argv);
	};

	static Application* CreateApplication();
}

