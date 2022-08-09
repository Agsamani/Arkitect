#include "rktpch.h"
#include "Texture2D.h"

#include <glad/glad.h>
#include "core/Base.h"

#include "stb_image.h"

namespace Arkitect {

	GLenum GetGLDataFormat(uint8_t channels) {
		switch (channels) {
		case 1: return GL_RED;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
		}

		RKT_CORE_ERROR("Uknown channel count : {0}", channels);
		return -1;
	}

	GLenum GetGLInternalFormat(uint8_t channels) {
		switch (channels) {
		case 1: return GL_R8;
		case 2: return GL_RG8;
		case 3: return GL_RGB8;
		case 4: return GL_RGBA8;
		}

		RKT_CORE_ERROR("Uknown channel count : {0}", channels);
		return -1;
	}
	
	Texture2D::Texture2D(uint32_t width, uint32_t height, uint8_t channels /*= 4*/, bool pixelized /*= false*/)
		:m_Width(width), m_Height(height), m_Channels(channels)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GetGLInternalFormat(m_Channels), m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, pixelized ? GL_NEAREST : GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, pixelized ? GL_NEAREST : GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture2D::Texture2D(const std::string& path, bool pixelized /*= false*/)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		if (data) {
			m_IsLoaded = true;

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, GetGLInternalFormat(channels), width, height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, pixelized ? GL_NEAREST : GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, pixelized ? GL_NEAREST : GL_LINEAR);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GetGLDataFormat(channels), GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else {
			RKT_CORE_ERROR("Failed to load texture : {0}", m_Path);
		}
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture2D::SetData(void* data, uint32_t size)
	{
		if (size != m_Width * m_Height * m_Channels) {
			RKT_CORE_ERROR("Data is not the entire texture!");
		}
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GetGLDataFormat(m_Channels), GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(uint32_t slot /*= 0*/)
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}
