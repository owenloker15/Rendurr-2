#include "Texture.hpp"

#include <glad/glad.h>

#include <stb_image.h>

#include "Core/Log.hpp"

namespace Rendurr
{
	Texture::Texture(const std::filesystem::path& filepath, TextureType type) : m_type(type)
	{
		stbi_set_flip_vertically_on_load(true);

		// Begin creating opengl texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);

		glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Read texture data from file
		int width, height, numChannels;
		unsigned char* data = stbi_load(filepath.string().c_str(), &width, &height, &numChannels, 0);

		if (data)
		{
			//glTexStorage2D(m_rendererId)

			// Check channels and determine format

			GLenum internalFormat = 0;
			GLenum dataFormat = 0;

			if (numChannels == 1)
			{
				internalFormat = GL_R8;
				dataFormat = GL_RED;
			}
			else if (numChannels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}
			else if (numChannels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else
			{
				RND_CORE_ERROR("Unsupported number of channels: {} for {}", numChannels, filepath.string());
			}

			glTextureStorage2D(m_rendererId, 1, internalFormat, width, height);
			glTextureSubImage2D(m_rendererId, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

			// TODO error checking
		}
		else
		{
			std::string errorReason = stbi_failure_reason();
			RND_CORE_ERROR("Failed to load texture image data: {} - {}", filepath.string(), errorReason);
		}

		stbi_image_free(data);

	}

	TextureType Texture::getType() const
	{
		return m_type;
	}

	void Texture::bind(uint32_t textureSlot) const
	{
		glBindTextureUnit(textureSlot, m_rendererId);
	}

	std::pair<std::string, uint32_t> Texture::TextureTypeToString(TextureType type)
	{
	    switch (type) {
	    case TextureType::Ambient: return std::make_pair<std::string, uint32_t>("u_Material_albedo", 0);
	    default: return std::make_pair<std::string, uint32_t>("", -1);
	    }
	}
}
