#include "Framebuffer.hpp"

#include <glad/glad.h>

#include "Core/Log.hpp"

namespace
{
	struct GLFormat
	{
		GLint internal;
		GLenum format;
	};

	GLFormat enumToGLFormat(const Rendurr::ColorAttachmentFormat& format)
	{
		switch (format)
		{
		case(Rendurr::ColorAttachmentFormat::RGBA8):
			return { GL_RGBA8, GL_RGBA };
		default:
			RND_CORE_ERROR("Invalid Color Attachment Format!");
			return {};
		}
	}
}

namespace Rendurr
{
	Framebuffer::Framebuffer(FramebufferSpecification spec) : m_width(spec.width), m_height(spec.height)
	{
		glGenFramebuffers(1, &m_rendererId);
		bind();

		for (const auto& [key, format] : spec.m_colorAttachments)
		{
			addColorAttachment(key, format);
		}

		// Depth buffer
		glGenRenderbuffers(1, &m_depthAttachment);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);

		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			m_depthAttachment
		);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			RND_CORE_ERROR("Framebuffer is incomplete!");
		}

		unbind();
	}

	void Framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
		glViewport(0, 0, m_width, m_height);
	}

	void Framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::release()
	{
		glDeleteFramebuffers(1, &m_rendererId);

		for (auto& [key, texture] : m_colorAttachments)
		{
			glDeleteTextures(1, &texture);
		}

		glDeleteRenderbuffers(1, &m_depthAttachment);
	}

	uint32_t Framebuffer::getColorAttachmentId(const std::string& colorAttachmentKey) const
	{
		return m_colorAttachments.at(colorAttachmentKey);
	}

	void Framebuffer::addColorAttachment(const std::string& colorAttachmentKey, const ColorAttachmentFormat& format)
	{
		const auto glFormats = enumToGLFormat(format);

		// Create texture
		uint32_t texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, glFormats.internal, m_width, m_height, 0, glFormats.format, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorAttachmentIndex, GL_TEXTURE_2D, texture, 0);

		m_colorAttachments[colorAttachmentKey] = texture;
		m_colorAttachmentIndex++;

		// “The fragment shader outputs should go to these attachments.”
		std::vector<GLenum> buffers;
		for (int i = 0; i < m_colorAttachments.size(); i++)
			buffers.push_back(GL_COLOR_ATTACHMENT0 + i);

		glDrawBuffers(buffers.size(), buffers.data());
	}
}
