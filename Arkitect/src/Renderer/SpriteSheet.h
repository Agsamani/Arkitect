#pragma once
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Arkitect {
	class SpriteSheet {
	public:
		SpriteSheet(std::shared_ptr<Texture2D> spriteSheet);
		SpriteSheet(std::shared_ptr<Texture2D> spriteSheet, const glm::vec2& min, const glm::vec2& max);
		~SpriteSheet() = default;

		void SetSpriteSheet(std::shared_ptr<Texture2D> spriteSheet) { m_SpriteSheet = spriteSheet; }
		std::shared_ptr<Texture2D> GetSpriteSheet() const { return m_SpriteSheet; }

		const glm::vec2& GetMin() const { return m_Min; }
		const glm::vec2& GetMax() const { return m_Max; }

		void SetMinMax(const glm::vec2& min, const glm::vec2& max) { m_Min = min; m_Max = max; }
		void SetMinMaxByPixel(const glm::u32vec2& min, const glm::u32vec2& max); // Should reverse Y?
	private:
		std::shared_ptr<Texture2D> m_SpriteSheet;
		glm::vec2 m_Min, m_Max;
	};
}