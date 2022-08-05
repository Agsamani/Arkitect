#include "rktpch.h"
#include "Application.h"

#include "Utils.h"
#include "Base.h"


//TEMP
#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

// TODO : debug callback


namespace Arkitect {

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		if (m_Instance) {
			RKT_CORE_ERROR("Application already exists");
		}
		m_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(RKT_BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//TEMP
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		glClearColor(0.15, 0.15, 0.15, 1.0);

		float vertices[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VAO = std::make_unique<VertexArray>();

		std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float2, "position"}
		};
		VBO->SetLayout(layout);

		std::shared_ptr<IndexBuffer> IBO = std::make_shared<IndexBuffer>(indices, 6);

		VAO->SetIndexBuffer(IBO);
		VAO->AddVertexBuffer(VBO);

		program = glCreateProgram();

		unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vShaderString = R"(#version 460 core

layout (location = 0) in vec2 aPos; 

void main()
{
    gl_Position = vec4(aPos , 0.0, 1.0);
})";

		const char* vShaderSource = vShaderString.c_str();
		glShaderSource(vShader, 1, &vShaderSource, NULL);
		glCompileShader(vShader);
		glAttachShader(program, vShader);

		unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fShaderString = R"(#version 460 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(227.0/256.0,0.0/256.0,79.0/256.0,1.0f);
} )";

		const char* fShaderSource = fShaderString.c_str();
		glShaderSource(fShader, 1, &fShaderSource, NULL);
		glCompileShader(fShader);
		glAttachShader(program, fShader);

		glDeleteShader(vShader);
		glDeleteShader(fShader);

		glLinkProgram(program);

		glUseProgram(program);
	}

	void Application::run()
	{
		while (m_Running)
		{
			float currentTime = Time::GetTime();
			Deltatime dt = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;

			for (Layer* layer : layerStack) {
				layer->OnUpdate(dt);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : layerStack) {
				layer->OnImGuiUpdate();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();


			//TEMP
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(program);
			VAO->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RKT_BIND_EVENT_FN(OnWindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(RKT_BIND_EVENT_FN(OnWindowResizeEvent));

		for (auto it = layerStack.rbegin(); it != layerStack.rend(); it++) {
			if (e.Handled) {
				break;
			}
			(*it)->OnEvent(e);
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