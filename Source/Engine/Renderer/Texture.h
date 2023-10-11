#pragma once
#include "Framework/Resource/Resource.h"
#include <glm/glm/glm.hpp>
#include <glad/include/glad/glad.h>


struct SDL_Texture;

namespace nc
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		virtual bool Create(std::string filename, ...) override;

		bool Load(const std::string& filename, class Renderer& renderer);
		const glm::ivec2& GetSize() const { return m_size; }

		void SetActive(GLuint unit) { glActiveTexture(unit); }
		void Bind() { glBindTexture(m_target, m_texture); }

		friend class Renderer;

	private:
		GLuint m_texture = 0;
		GLenum m_target = GL_TEXTURE_2D;
		glm::ivec2 m_size{ 0 };
	};
}
