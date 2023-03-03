#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

class Dunk
{
public:
	Dunk(float f, float zeta, float r, glm::vec2 initial);

	void setParams(float f, float zeta, float r);

	void OnUpdate(float dt, glm::vec2 input, glm::vec2 inputVel);
	void OnUpdate(float dt, glm::vec2 input);

	glm::vec2 previousPos;
	glm::vec2 pos;
	glm::vec2 velocity;
private:
	float k1, k2, k3;
};

