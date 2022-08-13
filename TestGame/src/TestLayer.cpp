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
	VAO->SetIndexBuffer(icoMesh->GetIndexBuffer());
	VAO->AddVertexBuffer(icoMesh->GetVertexBuffer());


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

	program->UploadUniformMat4("u_TMat", glm::translate(m_Pos));
	program->UploadUniformMat4("u_Cam", glm::perspective(glm::radians(60.0), 1.6, 0.2, 100.0)); //glm::ortho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0)

	Arkitect::RenderCommand::DrawIndexed(VAO, 0);
}

void TestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Pos");
	ImGui::DragFloat3("Pos", glm::value_ptr(m_Pos), 0.1);
	ImGui::End();
}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	
}
