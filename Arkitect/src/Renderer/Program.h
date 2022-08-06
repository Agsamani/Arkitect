#pragma once
#include "Shader.h"

// TODO : this will change later
namespace Arkitect {
	class Program {
	public:
		Program();
		~Program();

		void AttachShader(const Shader& shader) const;
		void LinkProgram() const;
		void UseProgram() const;
	private:
		uint32_t m_RendererID;
	};
}
