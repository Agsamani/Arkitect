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
	{ 
		m_Min = { (float)(minPixel.x) / GetTexture()->GetWidth() , (float)(minPixel.y) / GetTexture()->GetHeight() };
		m_Max = { (float)(maxPixel.x + 1) / GetTexture()->GetWidth() , (float)(maxPixel.y + 1) / GetTexture()->GetHeight() };
	}

}