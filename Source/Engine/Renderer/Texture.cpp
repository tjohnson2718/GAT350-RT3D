#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL2-2.28.4/include/SDL_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace nc
{
	Texture::~Texture()
	{
		if (m_texture) glDeleteTextures(1, &m_texture);
	}

	bool Texture::Create(std::string filename, ...)
	{
		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}

	bool Texture::CreateTexture(int width, int height)
	{
		m_target = GL_TEXTURE_2D;
		m_size = glm::vec2{ width, height };

		glGenTextures(1, &m_texture);
		glBindTexture(m_target, m_texture);

		// create texture (width, height)
		glTexImage2D(m_target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		// set texture parameters
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return true;
	}

	bool Texture::CreateDepthTexture(int width, int height)
	{
		m_target = GL_TEXTURE_2D;
		m_size = glm::vec2{ width, height };

		glGenTextures(1, &m_texture);
		glBindTexture(m_target, m_texture);

		// create texture (width, height)
		glTexImage2D(m_target, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		// set texture parameters
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		return true;
	}

	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		int channels = 0;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename.c_str(), &m_size.x, &m_size.y, &channels, 0);
		if (!data)
		{
			WARNING_LOG("Could not create surface: " << filename);
			return false;
		}
		
		glGenTextures(1, &m_texture);
		glBindTexture(m_target, m_texture);

		GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
		GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

		glTexStorage2D(m_target, 1, internalFormat, m_size.x, m_size.y);
		glTexSubImage2D(m_target, 0, 0, 0, m_size.x, m_size.y, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

		stbi_image_free(data);

		return true;
	}

	void Texture::ProcessGui()
	{
		ImGui::TextColored(ImVec4{ 0, 1, 0, 1 }, "Name: %s", name.c_str());
		ImGui::Text("Size: %d x %d", m_size.x, m_size.y);
		ImGui::Separator();
		ImVec2 size = ImVec2(256, 256);
		ImGui::Image((void*)(intptr_t)m_texture, size);
	}
}