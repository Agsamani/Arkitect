#include "rktpch.h"
#include "ProjectionCamera.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Arkitect {

	ProjectionCamera::ProjectionCamera(float fov, float aspectRatio, float near, float far)
		:m_Fov(glm::radians(fov)), m_AspectRation(aspectRatio), m_Near(near), m_Far(far)
	{
		m_ProjectionMatrix = glm::perspective(m_Fov, m_AspectRation, m_Near, m_Far);
		Recalculate();
	}

	void ProjectionCamera::SetAspectRatio(float aspectRatio)
	{
		m_AspectRation = aspectRatio;
		m_ProjectionMatrix = glm::perspective(m_Fov, m_AspectRation, m_Near, m_Far);
	}

	void ProjectionCamera::Recalculate()
	{
		glm::mat4 horizontalRotation = glm::rotate(glm::mat4(1.0), m_HorizontalAngle, glm::vec3(0.0, 1.0, 0.0));
		glm::vec3 tempDir = glm::vec3(horizontalRotation * glm::vec4(0.0, 0.0, -1.0, 1.0));
		glm::mat4 verticalRotation = glm::rotate(glm::mat4(1.0), m_VerticalAngle, (glm::cross(tempDir, glm::vec3(0.0, 1.0, 0.0))));
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0), m_Position) * verticalRotation * horizontalRotation);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void ProjectionCamera::CalculateFront()
	{
		glm::mat4 horizontalRotation = glm::rotate(glm::mat4(1.0), m_HorizontalAngle, glm::vec3(0.0, 1.0, 0.0));
		glm::vec3 tempDir = glm::vec3(horizontalRotation * glm::vec4(0.0, 0.0, -1.0, 1.0));
		glm::mat4 verticalRotation = glm::rotate(glm::mat4(1.0), m_VerticalAngle, (glm::cross(tempDir, glm::vec3(0.0, 1.0, 0.0))));
		m_FrontDirection = glm::vec3(verticalRotation * horizontalRotation * glm::vec4(0.0, 0.0, -1.0, 1.0));
	}

}
