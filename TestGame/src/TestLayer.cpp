#include "TestLayer.h"
#include "imgui.h"

#include <fstream>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL // TODO : move to premake maybe
#include "glm/gtx/vector_angle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


void TestLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });


	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VAO = std::make_shared<Arkitect::VertexArray>();

	std::shared_ptr<Arkitect::VertexBuffer> VBO = std::make_shared<Arkitect::VertexBuffer>(vertices, sizeof(vertices));

	Arkitect::BufferLayout layout = {
		{Arkitect::ShaderDataType::Float2, "position"},
		{Arkitect::ShaderDataType::Float2, "texCoord"}
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

	testTexture = std::make_unique<Arkitect::Texture2D>("assets/textures/testTex2.png");
	testTexture->Bind();
	program->UploadUniformInt("u_Texture", 0);
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

}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	
}
