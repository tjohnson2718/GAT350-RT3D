#pragma once
#include <glad/include/glad/glad.h>
#include "Framework/Resource/Resource.h"
#include <vector>

namespace nc
{
	class VertexBuffer : public Resource
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		bool Create(std::string name, ...) override;
		void Draw(GLenum primitiveType = GL_TRIANGLES);
		void Bind() { glBindVertexArray(m_vao); }

		void CreateVertexBuffer(GLsizei size, GLsizei vertexCount, GLvoid* data);
		void CreateIndexBuffer(GLenum indexType, GLsizei count, GLvoid* data);

		void SetAttribute(int index, GLint size, GLsizei stride, GLuint offset);

	protected:
		GLuint m_vao = 0;			// vertex array object

		GLuint m_vbo = 0;			// vertex buffer object
		GLuint m_vertexCount = 0;	// number of vertices in vertex buffer

		GLuint m_ibo = 0;			// index buffer object
		GLuint m_indexCount = 0;	// number of indices index buffer
		GLenum m_indexType = 0;		// data type of index
	};
}