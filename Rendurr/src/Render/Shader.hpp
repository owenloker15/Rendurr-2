#pragma once

#include <filesystem>

#include "ShaderUniforms.hpp"

namespace Rendurr
{
    typedef uint32_t ShaderHandle;

    ShaderHandle shader_program_create(const std::filesystem::path& vertexFilePath,
                                       const std::filesystem::path& fragmentFilePath);
    void shader_program_destroy(ShaderHandle handle);
    void shader_program_use(ShaderHandle handle);

    template <typename T>
    void shader_program_upload_uniform(ShaderHandle handle, T uniform)
    {
        shader_program_use(handle);
        uniform.upload(handle);
    }

} // namespace Rendurr
