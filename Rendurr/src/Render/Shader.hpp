#pragma once

#include <filesystem>

#include "ShaderUniforms.hpp"

namespace Rendurr
{
    struct ShaderData
    {
        const char* vertexFilePath;
        const char* fragmentFilePath;
        uint32_t rendererId;
    };

    ShaderData shader_program_create(const std::filesystem::path& vertexFilePath,
                                     const std::filesystem::path& fragmentFilePath);
    void shader_program_destroy(const ShaderData& shader);
    void shader_program_use(const ShaderData& shader);

    // Uniform uploads
    void shader_uniform_upload_bool(const ShaderData& shader, const char* uniformName, bool value);
    void shader_uniform_upload_int(const ShaderData& shader, const char* uniformName, int value);
    void shader_uniform_upload_float(const ShaderData& shader,
                                     const char* uniformName,
                                     float value);
    void shader_uniform_upload_vec2(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec2& value);
    void shader_uniform_upload_vec3(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec3& value);
    void shader_uniform_upload_vec4(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec4& value);
    void shader_uniform_upload_mat3(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::mat3& value);
    void shader_uniform_upload_mat4(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::mat4& value);

} // namespace Rendurr
