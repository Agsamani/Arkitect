#include "rktpch.h"
#include "SpriteAnimation.h"

namespace Arkitect {

	void SpriteAnimation::OnUpdate(Deltatime dt)
	{
		if (m_IsPlaying) {
			m_TimeVariable += dt;
			if (m_TimeVariable >= m_Spec.Duration / m_Spec.FrameCount) {

				m_FrameIndex++;

				if (m_FrameIndex >= m_Spec.FrameCount) {
					if (m_Spec.LoopEnabled) {
						m_FrameIndex = 0;
					}
					else {
						m_FrameIndex--;
						m_IsPlaying = false;
					}
				}

				CalculateNextFrame();

				m_TimeVariable = 0.0;
			}
		}
	}

	void SpriteAnimation::CalculateNextFrame()
	{
		int frameX = (m_Spec.FrameStartIndex + m_FrameIndex) % m_Spec.HorizontalFrameCount;
		int frameY = (m_Spec.FrameStartIndex + m_FrameIndex) / m_Spec.HorizontalFrameCount;

		glm::u32vec2 min = glm::u32vec2(
			m_Spec.StartPixelCoordinate.x + frameX * m_Spec.FrameWidth,
			m_Spec.StartPixelCoordinate.y - (frameY + 1) * m_Spec.FrameHeight + 1
		);

		glm::u32vec2 max = glm::u32vec2(m_Spec.FrameWidth, m_Spec.FrameHeight) + min - glm::u32vec2(1, 1);
		
		m_SpriteSheet.SetMinMaxByPixel(min, max);
	}

}