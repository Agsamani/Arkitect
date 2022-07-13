#pragma once

int main(int argc, char** argv);

namespace Arkitect {
	class Application
	{
	public:
		Application() = default;
		virtual ~Application();

		virtual void Test() = 0;
	private:
		void run();

		bool m_IsRunning = true;

		friend int ::main(int argc, char** argv);
	};

	static Application* CreateApplication();
}

