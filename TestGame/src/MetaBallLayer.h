#pragma once

#include "Arkitect.h"
#include "SlimeMouldLayer.h"

class MetaBallLayer : public Arkitect::Layer
{
public:
	MetaBallLayer();

	~MetaBallLayer() = default;

	void OnImGuiUpdate() override;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(Arkitect::Event & e) override;

private:
	bool OnMouseClickEvent(Arkitect::MouseButtonPressedEvent& e);
	void OnIteration(Arkitect::Deltatime dt);

	void InitAgents();

private:
	std::shared_ptr<Arkitect::VertexArray> mainQuad;
	std::unique_ptr<Arkitect::Program> mainQuadProgram;

	std::unique_ptr<Arkitect::Program> frameProgram;

	Arkitect::OrthographicCameraController orthoCameraController;


	const glm::ivec2 textureDim;
	unsigned int agentCount;

	std::unique_ptr<Arkitect::Texture2D> agentTexture;
	std::unique_ptr<Arkitect::Texture2D> fieldTexture;
	std::unique_ptr<Arkitect::Texture2D> mainTexture;

	std::unique_ptr<Arkitect::ComputeShader> agentCompute;
	std::unique_ptr<Arkitect::ComputeShader> fieldCompute;
	std::unique_ptr<Arkitect::ComputeShader> drawCompute;

	//
	STATE m_State = STATE::PAUSE;

	float m_AgentSpeed = 5.0;
	float m_SensorArmLength = 9.0;
	float m_SensorAngle = (2 * 3.14156) * (1.0 / 8.0);
	float m_RotationAngle = m_SensorAngle;
	float m_DecayRate = 1.0;

	glm::vec4 m_ColorA = glm::vec4(1.0);
	glm::vec4 m_ColorB = glm::vec4(0.0);
};

