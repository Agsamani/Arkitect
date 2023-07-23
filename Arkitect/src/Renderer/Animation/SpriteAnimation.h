#pragma once

#include <glm/glm.hpp>
#include "renderer/SpriteSheet.h"
#include "core/Deltatime.h"

namespace Arkitect {

	// Can make it more advanced if neccessary like adding state machine and sections for 
	// multiple animations in one sprite sheet

	enum class AnimationStyle /*???? better name*/ { ONCE = 0, LOOP, REVERSER_LOOP }; // Maybe reverse once?

	struct SpriteAnimationSpec { // Maybe better variable types?
		// TODO: add offset (padding/marigin)
		uint32_t FrameWidth;
		uint32_t FrameHeight;

		uint32_t HorizontalFrameCount;
		uint32_t VerticalFrameCount; 

		uint32_t FrameStartIndex = 0;
		uint32_t FrameCount = 1;

		glm::u32vec2 StartPixelCoordinate = { 0, 0};

		float Duration = 1.0;
		bool LoopEnabled = true;
	};

	class SpriteAnimation 
	{
	public:
		SpriteAnimation(std::shared_ptr<Texture2D> spriteTexture, const SpriteAnimationSpec& spec) : m_SpriteSheet(SpriteSheet(spriteTexture)), m_Spec(spec) {};
		SpriteAnimation(const SpriteSheet& spriteSheet, const SpriteAnimationSpec& spec) : m_SpriteSheet(spriteSheet), m_Spec(spec) {};
		~SpriteAnimation() = default;

		void Play() { m_IsPlaying = true; }
		void Pause() { m_IsPlaying = false; CalculateNextFrame(); }
		void Reset() { m_FrameIndex = 0; m_TimeVariable = 0.0; CalculateNextFrame(); }

		void OnUpdate(Deltatime dt);

		SpriteSheet& GetSpriteSheet() { return m_SpriteSheet; }
		SpriteAnimationSpec& GetSpec() { return m_Spec; }
	private:

		SpriteSheet m_SpriteSheet;
		SpriteAnimationSpec m_Spec;

		float m_TimeVariable = 0.0f;
		uint32_t m_FrameIndex = 0;

		bool m_IsPlaying = false;

	private:
		void CalculateNextFrame();
	};
}

