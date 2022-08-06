#include <rktpch.h>
#include "Shader.h"

#include <glad/glad.h>

namespace Arkitect {


	GLenum ShaderTypeToOpenGlType(ShaderType type) {
		switch (type)
		{
		case Arkitect::ShaderType::Vertex:			return GL_VERTEX_SHADER;
		case Arkitect::ShaderType::TessControl:		return GL_TESS_CONTROL_SHADER;
		case Arkitect::ShaderType::TessEvaluate:	return GL_TESS_EVALUATION_SHADER;
		case Arkitect::ShaderType::Geometry:		return GL_GEOMETRY_SHADER;
		case Arkitect::ShaderType::Fragment:		return GL_FRAGMENT_SHADER;
		case Arkitect::ShaderType::Compute:			return GL_COMPUTE_SHADER;
		}

		RKT_CORE_ERROR("Unknown ShaderType!");
		return 0;
	}

	Shader::Shader(std::string path, ShaderType type)
		:m_Type(type)
	{
		m_RendererID = glCreateShader(ShaderTypeToOpenGlType(m_Type));

		// TODO : optimize this
		std::ifstream file(path);
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string str = buffer.str();
		const char* shaderData = str.c_str();
		glShaderSource(m_RendererID, 1, &shaderData, NULL);
		glCompileShader(m_RendererID);
	}

	Shader::~Shader()
	{
		glDeleteShader(m_RendererID);
	}

}