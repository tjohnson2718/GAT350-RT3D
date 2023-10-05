#pragma once
#include "Framework/Resource/ResourceManager.h"
#include <glad/include/glad/glad.h>

namespace nc
{
	// Shader class for loading and compiling shaders.
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string filename, ...) override;

	public:
		GLuint m_shader = 0;
	};
}