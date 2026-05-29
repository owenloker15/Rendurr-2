#include "ShaderUniforms.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Log.hpp"

namespace
{
    GLint getUniformLocation(uint32_t shaderId, const char* uniformName)
    {
        auto uniformLocation = glGetUniformLocation(shaderId, uniformName);
        if (uniformLocation == -1) {
            RND_CORE_ERROR("Failed to find uniform with name {} in shader with id {}!",
                           uniformName,
                           shaderId);
        }
        return uniformLocation;
    }
} // namespace

namespace Rendurr
{
    CameraUniform::CameraUniform(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
        : m_viewMatrix(std::move(viewMatrix)), m_projectionMatrix(std::move(projectionMatrix))
    {}

    void CameraUniform::upload(uint32_t shaderId) const
    {
        auto viewMatrixUniformLocation = getUniformLocation(shaderId, "u_ViewMatrix");
        glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));

        auto projectionMatrixUniformLocation = getUniformLocation(shaderId, "u_ProjectionMatrix");
        glUniformMatrix4fv(projectionMatrixUniformLocation,
                           1,
                           GL_FALSE,
                           glm::value_ptr(m_projectionMatrix));
    }

    MeshTransformUniform::MeshTransformUniform(glm::mat4 transform)
        : m_transform(std::move(transform))
    {}

    void MeshTransformUniform::upload(uint32_t shaderId) const
    {
        auto transformUniformLocation = getUniformLocation(shaderId, "u_Transform");
        glUniformMatrix4fv(transformUniformLocation, 1, GL_FALSE, glm::value_ptr(m_transform));
    }

    TextureUniform::TextureUniform(std::string uniformName, uint32_t textureSlot)
        : m_uniformName(std::move(uniformName)), m_textureSlot(textureSlot)
    {}

    void TextureUniform::upload(uint32_t shaderId) const
    {
        auto textureNameUniformLocation = getUniformLocation(shaderId, m_uniformName.c_str());
        glUniform1i(textureNameUniformLocation, m_textureSlot);
    }

} // namespace Rendurr
