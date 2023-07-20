#include <rktpch.h>
#include "SpriteSheet.h"

namespace Arkitect {

	SpriteSheet::SpriteSheet(std::shared_ptr<Texture2D> spriteSheet)
		: SpriteSheet(spriteSheet, { 0.0, 0.0 }, { 1.0, 1.0 })
	{
	}

	SpriteSheet::SpriteSheet(std::shared_ptr<Texture2D> spriteSheet, const glm::vec2& min, const glm::vec2& max)
		: m_SpriteSheet(spriteSheet), m_Min(min), m_Max(max)
	{

	}

	void SpriteSheet::SetMinMaxByPixel(const glm::u32vec2& minPixel, const glm::u32vec2& maxPixel)
	{ // Reverses Y so it is easy to use pixel coordinates of images like in photoshop
		m_Min = { (float)(minPixel.x) / m_SpriteSheet->GetWidth() , (float)(maxPixel.y) / m_SpriteSheet->GetHeight() };
		m_Max = { (float)(maxPixel.x + 1) / m_SpriteSheet->GetWidth() , (float)(minPixel.y + 1) / m_SpriteSheet->GetHeight() };
	}

}