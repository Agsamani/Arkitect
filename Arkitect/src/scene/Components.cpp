#include <rktpch.h>
#include "Components.h"

namespace Arkitect {

	void SpriteComponent::SetSpriteSheet(SpriteSheet& spriteSheet)
	{
		Texture = spriteSheet.GetSpriteSheet();
		MinCoord = spriteSheet.GetMin();
		MaxCoord = spriteSheet.GetMax();
	}

	void SpriteComponent::SetSpriteSheet(SpriteSheet& spriteSheet, const glm::u32vec2& minPixel, const glm::u32vec2& maxPixel)
	{
		Texture = spriteSheet.GetSpriteSheet();
		spriteSheet.SetMinMaxByPixel(minPixel, maxPixel);
		MinCoord = spriteSheet.GetMin();
		MaxCoord = spriteSheet.GetMax();
	}

}