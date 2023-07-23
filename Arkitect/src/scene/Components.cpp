#include <rktpch.h>
#include "Components.h"

namespace Arkitect {

	void SpriteComponent::SetSpriteSheet(SpriteSheet& spriteSheet)
	{
		Texture = spriteSheet.GetTexture();
		MinCoord = spriteSheet.GetMin();
		MaxCoord = spriteSheet.GetMax();
	}

	void SpriteComponent::SetSpriteSheet(SpriteSheet& spriteSheet, const glm::u32vec2& minPixel, const glm::u32vec2& maxPixel)
	{
		Texture = spriteSheet.GetTexture();
		spriteSheet.SetMinMaxByPixel(minPixel, maxPixel);
		MinCoord = spriteSheet.GetMin();
		MaxCoord = spriteSheet.GetMax();
	}

}