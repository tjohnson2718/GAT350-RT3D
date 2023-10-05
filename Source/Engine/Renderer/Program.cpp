#include "Program.h"
#include "Shader.h"
#include "Core/Core.h"

namespace nc
{
	Program::~Program()
	{
		if (m_program)
		{
			glDeleteProgram(m_program);
		}
	}

	bool Program::Create(std::string filename, ...)
	{
		// load program json document
		rapidjson::Document document;
		if (!Json::Load(filename, document))
		{
			ERROR_LOG("Could not load program file: " << filename);
			return false;
		}

		// create program
		m_program = glCreateProgram();

		// get/add vertex shader
		std::string vertexShader;
		READ_DATA(document, vertexShader);
		if (!vertexShader.empty())
		{
			auto shader = GET_RESOURCE(nc::Shader, vertexShader, GL_VERTEX_SHADER);
			if (!shader)
			{
				ERROR_LOG("Could not get shader: " << vertexShader);
				return false;
			}
			AddShader(shader);
		}

		// get/add fragment shader
		std::string fragmentShader;
		READ_DATA(document, fragmentShader);
		if (!fragmentShader.empty())
		{
			auto shader = GET_RESOURCE(nc::Shader, fragmentShader, GL_FRAGMENT_SHADER);
			if (!shader)
			{
				ERROR_LOG("Could not get shader: " << fragmentShader);
				return false;
			}

			AddShader(shader);
		}

		return Link();
	}

	void Program::AddShader(const res_t<Shader>& shader)
	{
		glAttachShader(m_program, shader->m_shader);
	}

	bool Program::Link()
	{
		// link shader programs
		glLinkProgram(m_program);

		// check program link status
		GLint status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetProgramInfoLog(m_program, length, &length, &infoLog[0]);

				ERROR_LOG("Failed to link program: " << infoLog.c_str());
			}

			glDeleteProgram(m_program);
			m_program = 0;

			return false;
		}

		return true;
	}

	void Program::Use()
	{
		if (m_program) glUseProgram(m_program);
	}

	void Program::SetUniform(const std::string& name, float value)
	{
		GLint uniform = GetUniform(name);
		glUniform1f(uniform, value);
	}

	void Program::SetUniform(const std::string& name, int value)
	{
		GLint uniform = GetUniform(name);
		glUniform1i(uniform, value);
	}

	void Program::SetUniform(const std::string& name, bool value)
	{
		GLint uniform = GetUniform(name);
		glUniform1i(uniform, value);
	}

	void Program::SetUniform(const std::string& name, unsigned int value)
	{
		GLint uniform = GetUniform(name);
		glUniform1ui(uniform, value);
	}

	void Program::SetUniform(const std::string& name, const glm::vec2& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniform2fv(uniform, 1, &value[0]);
	}

	void Program::SetUniform(const std::string& name, const glm::vec3& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniform3fv(uniform, 1, &value[0]);
	}

	void Program::SetUniform(const std::string& name, const glm::vec4& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniform4fv(uniform, 1, &value[0]);
	}

	void Program::SetUniform(const std::string& name, const glm::mat3& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Program::SetUniform(const std::string& name, const glm::mat4& value)
	{
		GLint uniform = GetUniform(name);
		if (uniform != -1) glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint Program::GetUniform(const std::string& name)
	{
		// find uniform in map
		auto uniform = m_uniforms.find(name);
		// if not found, get uniform in program
		if (uniform == m_uniforms.end()) 
		{
			// get uniform in program
			GLint location = glGetUniformLocation(m_program, name.c_str());
			if (location == -1)
			{
				WARNING_LOG("Could not find uniform location: " << name.c_str());
			}
			m_uniforms[name] = location;
		}

		return m_uniforms[name];
	}
}
