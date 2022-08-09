#include <rktpch.h>
#include "FileIO.h"
#include "core/Base.h"
#include "core/Application.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <glad/glad.h>

namespace Arkitect {

	void FileIO::WriteImage(const void* data ,const char* path, uint32_t width, uint32_t height, int comp /*= 4*/)
	{
		int res = stbi_write_png(path, width, height, comp, data, comp * width);
		if (!res) {
			RKT_CORE_ERROR("Failed to write image: {0}", path);
		}
	}

	void FileIO::ScreenShot(const char* path)
	{
		int width = Application::Get().GetWindow().GetWidth();
		int height = Application::Get().GetWindow().GetHeight();
		unsigned char* data = new unsigned char[width * height * 4];
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		WriteImage(data, path, width, height, 4);
		delete[] data;
	}

}