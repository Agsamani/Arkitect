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

	glm::vec3 cPosition;
	glm::vec4 cameraDir;

	glm::vec2 prevCurserPos;
	glm::mat4 cOrientation;
	glm::mat4 newOrientation;

	float var = 1.0;
	float theta = 0.55;
	int powerVar = 8.0;

	bool firstClick = true;
};

