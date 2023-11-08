#include "FrameBuffer.h"
#include "Renderer.h"
#include "Core/Logger.h"

namespace nc
{
	Framebuffer::~Framebuffer()
	{
		if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
	}

	bool Framebuffer::Create(std::string filename, ...)
	{
		va_list args;

		// get texture name
		va_start(args, filename);
		const char* textureName = va_arg(args, const char*);
		va_end(args);

		// get texture resource
		auto texture = GET_RESOURCE(Texture, textureName);

		return CreateFramebuffer(texture);
	}

	bool Framebuffer::CreateFramebuffer(res_t<Texture> texture)
	{
		m_texture = texture;
		m_size = m_texture->GetSize();

		m_texture->Bind();

		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		// create the depth buffer (bind)
		CreateDepthbuffer(m_size.x, m_size.y);

		// bind the texture to the FBO
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->m_texture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR_LOG("Error creating frame buffer.");
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	bool Framebuffer::CreateDepthbuffer(int width, int height)
	{
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR_LOG("Error creating depth buffer.");
			return false;
		}

		return true;
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void Framebuffer::Unbind()
	{
		glFlush();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
