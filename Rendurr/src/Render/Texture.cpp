#include "Texture.hpp"

#include <cstdint>
#include <glad/glad.h>
#include <stb_image.h>

#include "Core/Log.hpp"
#include "Scene/AssetManager.h"

namespace Rendurr
{
    TextureHandle texture_create(AssetManager& assetManager,
                                 const std::filesystem::path& path,
                                 TextureType type)
    {
        TextureHandle handle = assetManager.m_textures.size();

        std::string keepStringAlive = path.string();

        TextureData data = {.name = keepStringAlive.c_str(), .rendererId = 0, .type = type};

        stbi_set_flip_vertically_on_load(true);

        // Begin creating opengl texture
        glCreateTextures(GL_TEXTURE_2D, 1, &data.rendererId);

        glTextureParameteri(data.rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(data.rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(data.rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(data.rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Read texture data from file
        int width, height, numChannels;
        unsigned char* imgData = stbi_load(path.string().c_str(), &width, &height, &numChannels, 0);

        if (imgData) {
            // glTexStorage2D(m_rendererId)

            // Check channels and determine format

            GLenum internalFormat = 0;
            GLenum dataFormat = 0;

            if (numChannels == 1) {
                internalFormat = GL_R8;
                dataFormat = GL_RED;
            }
            else if (numChannels == 3) {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }
            else if (numChannels == 4) {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            }
            else {
                RND_CORE_ERROR("Unsupported number of channels: {} for {}",
                               numChannels,
                               path.string());
            }

            glTextureStorage2D(data.rendererId, 1, internalFormat, width, height);
            glTextureSubImage2D(
                data.rendererId, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, imgData);

            // TODO error checking
        }
        else {
            std::string errorReason = stbi_failure_reason();
            RND_CORE_ERROR("Failed to load texture image data: {} - {}",
                           path.string(),
                           errorReason);
        }

        assetManager.m_textures.insert(assetManager.m_textures.begin() + handle, data);

        stbi_image_free(imgData);
        return handle;
    }

    void texture_destroy(TextureHandle handle) {}

    void texture_bind(TextureHandle handle, uint16_t textureSlot)
    {
        glBindTextureUnit(textureSlot, handle);
    }

} // namespace Rendurr
