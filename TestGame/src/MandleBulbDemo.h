#pragma once

#include "Arkitect.h"

class MandleBulbDemo : public Arkitect::Layer
{
public:
	MandleBulbDemo()
		:Layer("MandleBulbDemo")
	{

	}

	~MandleBulbDemo() = default;

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

	float divi = 1.0;

	int maxIt = 100;

	bool firstClick = true;

	glm::vec3 BGColor = glm::vec3(0.0);
	glm::vec3 GlowColor = glm::vec3(0.0, 53.0 / 256.0, 199.0 / 256.0);
	glm::vec3 AColor = glm::vec3(1.0);
	glm::vec3 BColor = glm::vec3(47.0 / 256.0, 16.0 / 256.0, 251.0 / 256.0);

};
