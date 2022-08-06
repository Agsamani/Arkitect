#include "TestLayer.h"
#include "imgui.h"

#include <fstream>
#include <sstream>

#include <glm/glm.hpp>


void TestLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });


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

	VAO = std::make_shared<Arkitect::VertexArray>();

	std::shared_ptr<Arkitect::VertexBuffer> VBO = std::make_shared<Arkitect::VertexBuffer>(vertices, sizeof(vertices));

	Arkitect::BufferLayout layout = {
		{Arkitect::ShaderDataType::Float2, "position"},
		{Arkitect::ShaderDataType::Float4, "color"}
	};
	VBO->SetLayout(layout);

	std::shared_ptr<Arkitect::IndexBuffer> IBO = std::make_shared<Arkitect::IndexBuffer>(indices, 6);

	VAO->SetIndexBuffer(IBO);
	VAO->AddVertexBuffer(VBO);

	program = std::make_unique<Arkitect::Program>();
	program->AttachShader(Arkitect::Shader("assets/shaders/default.vert", Arkitect::ShaderType::Vertex));
	program->AttachShader(Arkitect::Shader("assets/shaders/default.frag", Arkitect::ShaderType::Fragment));

	program->LinkProgram();
	program->UseProgram();
}

void TestLayer::OnDetach()
{
	
}

void TestLayer::OnUpdate(float dt)
{
	Arkitect::RenderCommand::Clear();
	program->UseProgram();
	Arkitect::RenderCommand::DrawIndexed(VAO, 6);
}

void TestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Test");
	ImGui::Text("LOOOLE");
	if (ImGui::Button("TOUCH ME!")) {
		RKT_INFO("lol");
	}
	ImGui::End();
}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	
}
