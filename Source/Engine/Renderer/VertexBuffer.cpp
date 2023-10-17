#include "VertexBuffer.h"

namespace nc
{
	VertexBuffer::VertexBuffer()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_ibo) glDeleteBuffers(1, &m_ibo);
		if (m_vbo) glDeleteBuffers(1, &m_vbo);
		if (m_vao) glDeleteVertexArrays(1, &m_vao);
	}

	bool VertexBuffer::Create(std::string name, ...)
	{
		return true;
	}

	void VertexBuffer::CreateVertexBuffer(GLsizei size, GLsizei vertexCount, GLvoid* data)
	{
		// size is number of bytes of data

		// store vertex count for draw call
		m_vertexCount = vertexCount;

		// create vertex buffer
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// copy data into vertex buffer
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::CreateIndexBuffer(GLenum indexType, GLsizei count, GLvoid* data)
	{
		// store index type (GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT)
		m_indexType = indexType;
		// store index count for draw call
		m_indexCount = count;

		// create index buffer
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		GLsizei size = 0; // index count * number of bytes of type (sizeof() returns the number of bytes in the data type)
		switch (m_indexType)
		{
		case GL_UNSIGNED_BYTE:
			size = m_indexCount * sizeof(GLubyte);
			break;
		case GL_UNSIGNED_SHORT:
			size = m_indexCount * sizeof(GLushort);
			break;
		case GL_UNSIGNED_INT:
			size = m_indexCount * sizeof(GLuint);
			break;
		}

		// copy data into index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
		
	void VertexBuffer::SetAttribute(int attribindex, GLint size, GLsizei stride, GLuint offset)
	{
		// size is number of elements (position = 3 (xyz), color = 3 (rgb), texcoord = 2 (uv))

		// bind vertex buffer
		glBindVertexBuffer(0, m_vbo, 0, stride);
		// enable vertex attribute (position, color, ...)
		glEnableVertexAttribArray(attribindex);
		// set vertex attribute format
		glVertexAttribFormat(attribindex, size, GL_FLOAT, GL_FALSE, offset);
		// bind vertex attribute index to vertex buffer
		glVertexAttribBinding(attribindex, 0);
	}

	void VertexBuffer::Draw(GLenum primitiveType)
	{
		// bind vertex array object
		glBindVertexArray(m_vao);

		// if index buffer object was set (!= 0) then draw using index array data, else render primitives from vertex array data
		if (m_ibo)
		{
			glDrawElements(primitiveType, m_indexCount, m_indexType, 0);
		}
		else if (m_vbo)
		{
			glDrawArrays(primitiveType, 0, m_vertexCount);
		}
	}
}
