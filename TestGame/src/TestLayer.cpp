#include "TestLayer.h"
#include "imgui.h"

#include <fstream>
#include <sstream>

#define GLM_ENABLE_EXPERIMENTAL // TODO : move to premake maybe

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

TestLayer::TestLayer()
	:Layer("TestLayer"), cameraController(1.6, 60.0), orthoCameraController(1.6)
{
}



void TestLayer::OnAttach()
{
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });

	frameQuad = std::make_shared<Arkitect::VertexArray>();
	float quadVertices[] = {
		-1.0, -1.0, 0.0, 0.0,
		 1.0, -1.0, 1.0, 0.0,
		 1.0,  1.0, 1.0, 1.0,
		-1.0,  1.0, 0.0, 1.0
	};
	uint32_t quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};
	std::shared_ptr<Arkitect::VertexBuffer> vertexBuffer = std::make_shared<Arkitect::VertexBuffer>(quadVertices, sizeof(quadVertices));
	Arkitect::BufferLayout layout = {
		{Arkitect::ShaderDataType::Float2, "position"},
		{Arkitect::ShaderDataType::Float2, "texcoord"},
	};
	vertexBuffer->SetLayout(layout);
	std::shared_ptr<Arkitect::IndexBuffer> indexBuffer = std::make_shared<Arkitect::IndexBuffer>(quadIndices, 6);
	frameQuad->AddVertexBuffer(vertexBuffer);
	frameQuad->SetIndexBuffer(indexBuffer);
	frameProgram = std::make_unique<Arkitect::Program>();
	frameProgram->AttachShader(Arkitect::Shader("assets/shaders/frame.vert", Arkitect::ShaderType::Vertex));
	frameProgram->AttachShader(Arkitect::Shader("assets/shaders/frame.frag", Arkitect::ShaderType::Fragment));
	frameProgram->LinkProgram();



	icoMesh = std::make_unique<Arkitect::Mesh>("assets/meshes/donut.gltf");

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
	fbSpec.Width = (uint32_t)(128 * 4 * 1.6);
	fbSpec.Height = 128 * 4;

	framebuffer = std::make_shared<Arkitect::Framebuffer>(fbSpec);
	debug_MakeVao();

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

	
	cameraController.OnUpdate(dt);
	orthoCameraController.OnUpdate(dt);

	program->UploadUniformMat4("u_Cam", cameraController.GetCamera().GetViewProjection());

	Arkitect::RenderCommand::DrawIndexed(icoMesh->GetVertexArray(), 0);
	//Arkitect::RenderCommand::DrawLine(debugVao, 0);
	framebuffer->Unbind();

	Arkitect::RenderCommand::SetViewport(0, 0, Arkitect::Application::Get().GetWindow().GetWidth(), Arkitect::Application::Get().GetWindow().GetHeight());
	Arkitect::RenderCommand::Clear();
	framebuffer->BindAttachmentTexture(0, 0);
	frameProgram->UseProgram();
	Arkitect::RenderCommand::DrawIndexed(frameQuad, 0);
}

void TestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Pos");

// 	uint64_t textureID = framebuffer->GetColorAttachmentRendererID(0);
// 	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ 1024, 1024 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	if (ImGui::Button("Smooth lines"))
	{
		Arkitect::RenderCommand::SetLineSmooth(true);
	}
	if (ImGui::Button("No Smooth lines"))
	{
		Arkitect::RenderCommand::SetLineSmooth(false);
	}
	ImGui::End();
}

void TestLayer::OnEvent(Arkitect::Event& e)
{
	cameraController.OnEvent(e);
	orthoCameraController.OnEvent(e);
}

void TestLayer::debug_MakeVao()
{
	debugVao = std::make_shared<Arkitect::VertexArray>();
	float vs[] = {
		1.0, 0.0, 0.0,
		0.0, 0.75, 0.0,
		0.0, 0.0, 0.5
	};

	uint32_t is[] = {
		0, 1, 2
	};

	Arkitect::BufferLayout l = {
		{Arkitect::ShaderDataType::Float3, "pos"}
	};

	std::shared_ptr<Arkitect::VertexBuffer> vb = std::make_shared<Arkitect::VertexBuffer>(vs, sizeof(vs));
	vb->SetLayout(l);
	std::shared_ptr<Arkitect::IndexBuffer> ib = std::make_shared<Arkitect::IndexBuffer>(is, 3);
	debugVao->AddVertexBuffer(vb);
	debugVao->SetIndexBuffer(ib);
}
