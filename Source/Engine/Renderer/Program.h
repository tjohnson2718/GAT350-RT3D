#pragma once
#include "Framework/Resource/ResourceManager.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glad/include/glad/glad.h>
#include <map>

namespace nc
{
	class Shader;

	// Program class for linking shaders and setting uniforms.
	class Program : public Resource
	{
	public:
		~Program();

		virtual bool Create(std::string name, ...) override;
		void AddShader(const res_t<Shader>& shader);

		bool Link();
		void Use();

		// uniforms
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, unsigned int value);
		void SetUniform(const std::string& name, bool value);

		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetUniform(const std::string& name, const glm::vec4& value);

		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

	private:
		GLint GetUniform(const std::string& name);

	public:
		GLuint m_program = 0;
		std::map<std::string, GLint> m_uniforms;
	};
}


