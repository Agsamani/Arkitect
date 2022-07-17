#pragma once

#include "core/Base.h"
#include "events/Event.h"

namespace Arkitect {
	class Window {
	public:
		Window(int width = 1280, int height = 720, std::string title = "Arkitect");
		~Window() = default;
		
		void OnUpdate();

		unsigned int GetWidth() { return m_Data.width; }
		unsigned int GetHeight() { return m_Data.height; }

		void SetEventCallback(std::function<void(Event&)> eventCallback) { m_Data.eventCallbackFn = eventCallback; }
		bool IsVsync() { return m_Data.vsync; }
		void SetVSync(bool enabled);

		void* GetNativeWindow() { return m_GLFWwindow; }
	private:
		void Init(int width, int height, std::string title);
		void Shutdown();

		// TODO : clean this
		void* m_GLFWwindow;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vsync = true;

			std::function<void(Event&)> eventCallbackFn;
		};

		WindowData m_Data;
	};
}
