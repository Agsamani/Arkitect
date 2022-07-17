#pragma once

#include "core/Base.h"
#include "events/Event.h"

namespace Arkitect {
	class Window {
	public:
		Window(int width = 1280, int height = 720, std::string title = "Arkitect");
		~Window() = default;
		
		void OnUpdate();

		unsigned int GetWidth() { return m_Data.Width; }
		unsigned int GetHeight() { return m_Data.Height; }

		void SetEventCallback(std::function<void(Event&)> eventCallback) { m_Data.EventCallback = eventCallback; }
		bool IsVsync() { return m_Data.VSync; }
		void SetVSync(bool enabled);

		void* GetNativeWindow() { return m_Window; }
	private:
		void Init(int width, int height, std::string title);
		void Shutdown();

		// TODO : clean this
		void* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync = true;

			std::function<void(Event&)> EventCallback;
		};

		WindowData m_Data;
	};
}
