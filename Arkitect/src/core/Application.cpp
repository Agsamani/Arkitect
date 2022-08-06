#include "rktpch.h"
#include "Application.h"

#include "Utils.h"
#include "Base.h"

#include "Renderer/RenderCommand.h"

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

		RenderCommand::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		//TEMP
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });


		float vertices[] = {
			-0.5f, -0.5f, 0.2, 0.5, 0.6, 1.0,
			 0.5f, -0.5f, 0.9, 0.5, 0.2, 1.0,
			 0.5f,  0.5f, 0.2, 0.0, 0.6, 1.0,
			-0.5f,  0.5f, 0.4, 0.5, 0.9, 1.0
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VAO = std::make_shared<VertexArray>();

		std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ShaderDataType::Float2, "position"},
			{ShaderDataType::Float4, "color"}
		};
		VBO->SetLayout(layout);

		std::shared_ptr<IndexBuffer> IBO = std::make_shared<IndexBuffer>(indices, 6);

		VAO->SetIndexBuffer(IBO);
		VAO->AddVertexBuffer(VBO);

		program = std::make_unique<Program>();
		program->AttachShader(Shader("../Arkitect/assets/shaders/default.vert", ShaderType::Vertex));
		program->AttachShader(Shader("../Arkitect/assets/shaders/default.frag", ShaderType::Fragment));

		program->LinkProgram();
		program->UseProgram();
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
			RenderCommand::Clear();
			program->UseProgram();
			RenderCommand::DrawIndexed(VAO, 6);
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