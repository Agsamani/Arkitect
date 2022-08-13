#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "renderer/Buffer.h"
#include "renderer/VertexArray.h"

// Basic single mesh for now

namespace Arkitect {
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh();

		const std::shared_ptr<VertexArray>& GetVertexArray() { return m_VertexArray; }

		glm::mat4 GetTransform();

		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec4 GetRotation() const { return m_Rotation; }
		glm::vec3 GetScale() const { return m_Scale; }

		void SetPosition(glm::vec3 val) { m_Position = val; }
		void SetRotation(glm::vec4 val) { m_Rotation = val; }
		void SetScale(glm::vec3 val) { m_Scale = val; }
	private:

		std::shared_ptr<VertexArray> m_VertexArray;

		glm::vec3 m_Position = glm::vec3(0.0);
		glm::vec4 m_Rotation = glm::vec4(0.0);
		glm::vec3 m_Scale = glm::vec3(1.0);
	};
}
