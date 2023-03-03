#pragma once

#include "Arkitect.h"

class Renderer2DTestLayer : public Arkitect::Layer {
public:
	Renderer2DTestLayer();
	~Renderer2DTestLayer() = default;

	void OnImGuiUpdate() override;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(Arkitect::Event& e) override;
private:

	std::unique_ptr<Arkitect::Renderer2D> m_Renderer2D;
	Arkitect::OrthographicCameraController m_Camera;

	std::shared_ptr<Arkitect::Texture2D> m_TestTexture;

	glm::vec4 m_QuadColorA = glm::vec4(1.0);
	glm::vec4 m_QuadColorB = glm::vec4(1.0);
};