#include "Cubemap.h"
#include "Renderer.h"
#include "Core/Logger.h"

#include <cstdarg>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
#include <stb/stb_image.h>

namespace nc
{
	bool Cubemap::Create(std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments
		va_list args;

		// va_start - enables access to variadic function arguments
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments
		std::vector<std::string> filenames = va_arg(args, std::vector<std::string>);

		// va_end - ends traversal of the variadic function arguments
		va_end(args);

		// create textures (returns true/false if successful)
		return Load(filenames);
	}


	bool Cubemap::Load(const std::vector<std::string>& filenames)
	{
		m_target = GL_TEXTURE_CUBE_MAP;

		glGenTextures(1, &m_texture);
		glBindTexture(m_target, m_texture);

		GLuint targets[] =
		{
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		for (size_t i = 0; i < filenames.size(); i++)
		{
			int channels = 0;
			unsigned char* data = stbi_load(filenames[i].c_str(), &m_size.x, &m_size.y, &channels, 0);
			if (!data)
			{
				WARNING_LOG("Could not create surface: " << filenames[i]);
				return false;
			}

			GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
			GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

			glTexImage2D(targets[i], 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return true;
	}
}
