#pragma once

#include <glm/glm.hpp>
#include "camera/OrthigraphicCamera.h"
#include "Texture.h"
#include "scene/Components.h"
#include "renderer/Font.h"

namespace Arkitect {
	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& ortho);
		static void EndScene();

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, const glm::vec2* tecCoords, const glm::vec4& tintColor);

		static void DrawSprite(const glm::mat4& transform, const SpriteComponent& sprite);

		struct TextParams
		{
			glm::vec4 Color{ 1.0f };
			float Kerning = 0.0f;
			float LineSpacing = 0.0f;
		};
		static void DrawText(std::shared_ptr<Font> font, const std::string& text, const TextParams& textParams, const glm::mat4& transform);
		static void DrawText(const std::string& text, const TextComponent& tc, const glm::mat4& transform);
	};
}
