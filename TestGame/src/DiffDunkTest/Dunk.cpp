#include "Dunk.h"

Dunk::Dunk(float f, float zeta, float r, glm::vec2 initial)
{
	setParams(f, zeta, r);
	previousPos = initial;
	pos = initial;
	velocity = glm::vec2(0.0);
}

void Dunk::setParams(float f, float zeta, float r)
{
	k1 = zeta / (glm::pi<float>() * f);
	k2 = 1.0 / ((2 * glm::pi<float>() * f) * (2 * glm::pi<float>() * f));
	k3 = (r * zeta) / (2 * glm::pi<float>() * f);
}

void Dunk::OnUpdate(float dt, glm::vec2 input, glm::vec2 inputVel)
{
	pos += dt * velocity;
	velocity += dt * (input + k3 * inputVel - pos - k1 * velocity)/k2;
}

void Dunk::OnUpdate(float dt, glm::vec2 input)
{
	glm::vec2 inputVel = (input - previousPos) / dt;
	previousPos = input;
	OnUpdate(dt, input, inputVel);
}
