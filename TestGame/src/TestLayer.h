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

	std::unique_ptr<Arkitect::Texture2D> testTexture;

};

