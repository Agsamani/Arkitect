#pragma once

#include <glm/glm.hpp>
#include "camera/OrthigraphicCamera.h"
#include "Texture.h"

namespace Arkitect {
	class Renderer2D {
	public:
		void Init();
		void Shutdown();

		void BeginScene(const OrthographicCamera& ortho);
		void EndScene();

		void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec4& tintColor);

	};
}
