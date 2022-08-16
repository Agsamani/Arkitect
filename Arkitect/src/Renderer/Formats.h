#pragma once

namespace Arkitect {
	enum class TextureFilterFormat {
		None = 0,
		Linear, Nearest
	};

	enum class TextureDataFormat {
		None = 0,
		RGBA8,
		RED_INTEGER,

		DEPTH24STENCIL8
	};
}