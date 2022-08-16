#pragma once

#include "Arkitect.h"

class TestLayer : public Arkitect::Layer
{
public:
	TestLayer()
		:Layer("TestLayer")
	{

	}

	~TestLayer() = default;

	void OnImGuiUpdate() override;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(Arkitect::Event& e) override;

private:
	std::unique_ptr<Arkitect::Program> program;
	std::shared_ptr<Arkitect::VertexArray> VAO;

	std::shared_ptr<Arkitect::Framebuffer> framebuffer;

	std::unique_ptr<Arkitect::Texture2D> testTexture;
	std::unique_ptr<Arkitect::Mesh> icoMesh;

	glm::vec3 m_Pos = glm::vec3(0.0);
};

