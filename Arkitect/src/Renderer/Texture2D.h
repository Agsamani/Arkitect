#pragma once

#include <string>
#include "Formats.h"

namespace Arkitect {
	class Texture2D
	{
	public:
		Texture2D(uint32_t width, uint32_t height, uint8_t channels = 4, TextureFilterFormat filterFormat = TextureFilterFormat::Nearest);
		Texture2D(const std::string& path, bool pixelized = false);
		~Texture2D();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint8_t GetChannels() const { return m_Channels; }
		uint32_t GetRendererID() const { return m_RendererID; }

		const std::string& GetPath() const { return m_Path; }
		bool IsLoaded() const { return m_IsLoaded; }

		void SetData(void* data, uint32_t size);

		void Bind(uint32_t slot = 0);

		bool operator==(const Texture2D& other) const 
		{
			return m_RendererID == other.GetRendererID();
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint8_t m_Channels;
		uint32_t m_RendererID;
		bool m_IsLoaded = false;
	};
}

