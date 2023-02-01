#include "ComputeTestLayer.h"
#include "imgui.h"

#include <glm/gtc/type_ptr.hpp>

ComputeTestLayer::ComputeTestLayer()
	:Layer("ComputeTestLayer"), orthoCameraController(1.6, true), textureDim(1024 , 1024 )
{
}

void ComputeTestLayer::OnAttach()
{
	agentCount = 2048 * 2;
	Arkitect::RenderCommand::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });

	mainQuad = std::make_shared<Arkitect::VertexArray>();
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
	mainQuad->AddVertexBuffer(vertexBuffer);
	mainQuad->SetIndexBuffer(indexBuffer);
	mainQuadProgram = std::make_unique<Arkitect::Program>();
	mainQuadProgram->AttachShader(Arkitect::Shader("assets/shaders/slimeMould/main.vert", Arkitect::ShaderType::Vertex));
	mainQuadProgram->AttachShader(Arkitect::Shader("assets/shaders/slimeMould/main.frag", Arkitect::ShaderType::Fragment));
	mainQuadProgram->LinkProgram();

	Arkitect::TextureSpec agentTextureSpec = { Arkitect::TextureFilterFormat::Nearest, Arkitect::DataType::FLOAT };
	agentTexture = std::make_unique<Arkitect::Texture2D>(agentCount, 1, 4, agentTextureSpec);
	InitAgents();
	agentTexture->BindImage(0);
	fieldTexture = std::make_unique<Arkitect::Texture2D>(textureDim.x, textureDim.y);
	fieldTexture->BindImage(1);
	mainTexture = std::make_unique<Arkitect::Texture2D>(textureDim.x, textureDim.y);	
	mainQuadProgram->UseProgram();
	mainQuadProgram->UploadUniformInt("u_Texture", 0);
	mainTexture->BindImage(2);


	agentCompute = std::make_unique<Arkitect::ComputeShader>("assets/shaders/slimeMould/agent.comp");
	fieldCompute = std::make_unique<Arkitect::ComputeShader>("assets/shaders/slimeMould/field.comp");
	drawCompute = std::make_unique<Arkitect::ComputeShader>("assets/shaders/slimeMould/draw.comp");

	uint8_t* textureData = new uint8_t[textureDim.x * textureDim.y * 4];
	memset(textureData, 0, textureDim.x * textureDim.y * 4);
	fieldTexture->SetData(textureData, textureDim.x * textureDim.y * 4);
	delete[] textureData;

	frameProgram = std::make_unique<Arkitect::Program>();
	frameProgram->AttachShader(Arkitect::Shader("assets/shaders/slimeMould/frame.vert", Arkitect::ShaderType::Vertex));
	frameProgram->AttachShader(Arkitect::Shader("assets/shaders/slimeMould/frame.frag", Arkitect::ShaderType::Fragment));
	frameProgram->LinkProgram();

	Arkitect::RenderCommand::SetLineWidth(2.0);
	Arkitect::RenderCommand::SetLineSmooth(false);
}

void ComputeTestLayer::InitAgents() {
	float* data = new float[agentCount * 4];
	for (int i = 0; i < agentCount; i++) {
		data[4 * i + 0] = 0.0;//Arkitect::Random::Float() * 2.0 - 1.0;
		data[4 * i + 1] = 0.0;//Arkitect::Random::Float() * 2.0 - 1.0;
		float theta = (Arkitect::Random::Float()) * 2 * 3.14156;
		data[4 * i + 2] = glm::cos(theta);
		data[4 * i + 3] = glm::sin(theta);
	}
	agentTexture->SetData(data, agentCount * 4 * sizeof(float));
	delete[] data;
}

void ComputeTestLayer::OnDetach()
{
	
}

void ComputeTestLayer::OnUpdate(float dt)
{
	if (m_State == STATE::PLAY) {
		OnIteration(dt);
	}
	Arkitect::RenderCommand::Clear();
	orthoCameraController.OnUpdate(dt);

	mainQuadProgram->UseProgram();
	mainQuadProgram->UploadUniformMat4("u_Cam", orthoCameraController.GetCamera().GetViewProjection());

	mainTexture->Bind();

	Arkitect::RenderCommand::DrawIndexed(mainQuad, 0);

	frameProgram->UseProgram();
	frameProgram->UploadUniformMat4("u_Cam", orthoCameraController.GetCamera().GetViewProjection());
	Arkitect::RenderCommand::DrawLine(mainQuad, 0);
}

void ComputeTestLayer::OnImGuiUpdate()
{
	ImGui::Begin("Compute");
	if (ImGui::Button("Do")) {
		OnIteration(0.0);
	}
	ImGui::SameLine();
	if (ImGui::Button("PLAY")) {
		m_State = STATE::PLAY;
	}
	ImGui::SameLine();
	if (ImGui::Button("PAUSE")) {
		m_State = STATE::PAUSE;
	}

	ImGui::DragFloat("Speed", &m_AgentSpeed, 0.05, 0.0, 200.0);
	ImGui::DragFloat("Sensor Arm Length", &m_SensorArmLength, 0.5, 0.0, 500.0);
	ImGui::SliderAngle("Sensor Angle", &m_SensorAngle, 0.0, 180.0);
	ImGui::SliderAngle("Rotation Angle", &m_RotationAngle, 0.0, 180.0);
	ImGui::DragFloat("Decay", &m_DecayRate, 0.1, 0.0, 100.0);

	ImGui::ColorEdit4("Color A", glm::value_ptr(m_ColorA));
	ImGui::ColorEdit4("Color B", glm::value_ptr(m_ColorB));

	ImGui::End();

}

void ComputeTestLayer::OnEvent(Arkitect::Event& e)
{
	orthoCameraController.OnEvent(e);
	
	Arkitect::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Arkitect::MouseButtonPressedEvent>(RKT_BIND_EVENT_FN(ComputeTestLayer::OnMouseClickEvent));
}

bool ComputeTestLayer::OnMouseClickEvent(Arkitect::MouseButtonPressedEvent& e)
{
	
	return false;
}

void ComputeTestLayer::OnIteration(Arkitect::Deltatime dt)
{
	const Arkitect::Program& fieldProgram = fieldCompute->GetProgram();
	fieldProgram.UseProgram();
	fieldProgram.UploadUniformFloat("u_DecayRate", m_DecayRate / 10000.0);
	fieldCompute->Dispatch(textureDim.x / 8, textureDim.y / 4, 1);

	const Arkitect::Program& agentProgram = agentCompute->GetProgram();
	agentProgram.UseProgram();
	agentProgram.UploadUniformFloat2("u_Dim", { float(textureDim.x), float(textureDim.y) });
	agentProgram.UploadUniformFloat("u_Speed", m_AgentSpeed / 1000.0);
	agentProgram.UploadUniformFloat("u_SensorArmLength", m_SensorArmLength);
	agentProgram.UploadUniformFloat("u_SensorAngle", m_SensorAngle);
	agentProgram.UploadUniformFloat("u_RotationAngle", m_RotationAngle);
	agentProgram.UploadUniformFloat("u_Random", Arkitect::Random::Float());
	agentCompute->Dispatch(agentCount / 32, 1, 1);

	const Arkitect::Program& drawProgram = drawCompute->GetProgram();
	drawProgram.UseProgram();
	drawProgram.UploadUniformFloat4("u_ColorA", m_ColorA);
	drawProgram.UploadUniformFloat4("u_ColorB", m_ColorB);
	drawCompute->Dispatch(textureDim.x / 8, textureDim.y / 4, 1);
}

