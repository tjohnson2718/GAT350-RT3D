#pragma once
#include "Framework/Resource/Resource.h"
#include <glm/glm/glm.hpp>
#include <glad/include/glad/glad.h>

namespace nc
{
	class Texture;

	class Framebuffer : public Resource
	{
	public:
		Framebuffer() = default;
		~Framebuffer();

		bool Create(std::string filename, ...) override;
		bool CreateFramebuffer(res_t<Texture> texture);
		bool CreateDepthbuffer(int width, int height);

		void Bind();
		void Unbind();

		glm::ivec2 GetSize() const { return m_size; }

	protected:
		GLuint m_fbo = 0;
		res_t<Texture> m_texture;
		glm::ivec2 m_size{ 0 };
	};
}
