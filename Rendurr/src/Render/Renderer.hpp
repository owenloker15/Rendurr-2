#pragma once

#include <glm/vec4.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

namespace rnd
{

    void clear();
    void setClearColor(const glm::vec4& rgba);
    void setViewport(float width, float height);
    void enableDepthTesting();
    void enableDebug();

    void upload_texture_to_shader(const TextureData& texture, const ShaderData& shader);
    void drawIndexed(uint32_t vertexArrayRendererId, uint32_t indexCount);
} // namespace rnd
