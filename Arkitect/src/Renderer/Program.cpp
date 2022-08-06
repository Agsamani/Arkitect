#include "rktpch.h"
#include "Program.h"

#include <glad/glad.h>


namespace Arkitect {

	Program::Program()
	{
		m_RendererID = glCreateProgram();
	}

	Program::~Program()
	{
		glDeleteProgram(m_RendererID);
		// TODO : Maybe detach shaders?
	}

	void Program::AttachShader(const Shader& shader) const
	{
		glAttachShader(m_RendererID, shader.GetShaderID());
	}

	void Program::LinkProgram() const
	{
		glLinkProgram(m_RendererID);
	}

	void Program::UseProgram() const
	{
		glUseProgram(m_RendererID);
	}

}