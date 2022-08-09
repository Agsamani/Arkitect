#pragma once
// temp
namespace Arkitect {
	class FileIO {
	public:
		static void WriteImage(const void* data, const char* path, uint32_t width, uint32_t height, int comp = 4);

		// Temp :
		static void ScreenShot(const char* path);
	};
	
}