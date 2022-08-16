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

	VAO = std::make_shared<Arkitect::VertexArray>();

	icoMesh = std::make_unique<Arkitect::Mesh>("assets/meshes/basic.gltf");

	program = std::make_unique<Arkitect::Program>();
	program->AttachShader(Arkitect::Shader("assets/shaders/default.vert", Arkitect::ShaderType::Vertex));
	program->AttachShader(Arkitect::Shader("assets/shaders/default.frag", Arkitect::ShaderType::Fragment));

	program->LinkProgram();
	program->UseProgram();

	Arkitect::FramebufferSpec fbSpec;
	fbSpec.Attachments = { 
		{Arkitect::TextureDataFormat::RGBA8, Arkitect::TextureFilterFormat::Nearest},
		{Arkitect::TextureDataFormat::DEPTH24STENCIL8, Arkitect::TextureFilterFormat::Nearest}
	};
	fbSpec.Width = 128;
	fbSpec.Height = 128;

	framebuffer = std::make_shared<Arkitect::Framebuffer>(fbSpec);
}

void TestLayer::OnDetach()
{
	
}

void TestLayer::OnUpdate(float dt)
{
	Arkitect::RenderCommand::Clear();
	framebuffer->Bind();
	Arkitect::RenderCommand::Clear();
	program->UseProgram();

	program->UploadUniformMat4("u_TMat", glm::translate(m_Pos));
	program->UploadUniformMat4("u_Cam", glm::perspective(glm::radians(60.0), 1.0, 0.2, 100.0)); //glm::ortho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0)

	Arkitect::RenderCommand::DrawIndexed(icoMesh->GetVertexArray(), 0);
	framebuffer->Unbind();
}

void TestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Pos");

	uint64_t textureID = framebuffer->GetColorAttachmentRendererID(0);
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ 1024, 1024 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::DragFloat3("Pos", glm::value_ptr(m_Pos), 0.1);
	ImGui::End();
}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	
}
