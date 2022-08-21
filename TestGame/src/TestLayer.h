#pragma once

#include "Arkitect.h"

class TestLayer : public Arkitect::Layer
{
public:
	TestLayer();

	~TestLayer() = default;

	void OnImGuiUpdate() override;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(Arkitect::Event& e) override;

private:
	std::unique_ptr<Arkitect::Program> program;

	std::shared_ptr<Arkitect::Framebuffer> framebuffer;

	std::unique_ptr<Arkitect::Texture2D> testTexture;
	std::unique_ptr<Arkitect::Mesh> icoMesh;

	std::shared_ptr<Arkitect::VertexArray> frameQuad;
	std::unique_ptr<Arkitect::Program> frameProgram;

	Arkitect::ProjectionCameraController cameraController;

	//Debug
	std::shared_ptr<Arkitect::VertexArray> debugVao;
	void debug_MakeVao();
};

