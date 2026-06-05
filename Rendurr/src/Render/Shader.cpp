#include "Shader.hpp"

#include <glad/glad.h>

#include "Utils/FileUtils.hpp"

namespace
{
    constexpr uint32_t compileShader(GLenum shaderType, std::string_view shaderSource)
    {
        // Create shader object
        uint32_t shader = glCreateShader(shaderType);

        // Attach the shader source to the shader object and compile the shader
        const char* src = shaderSource.data();
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        // Check for errors
        int logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 1) {
            std::string infoLog(logLength, '\0');
            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
            RND_CORE_ERROR("Shader compilation failed!\n{}", infoLog);
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }
} // namespace

namespace Rendurr
{
    ShaderHandle shader_program_create(const std::filesystem::path& vertexFilePath,
                                       const std::filesystem::path& fragmentFilePath)
    {
        const std::string vertexShaderContent = Utils::read_file(vertexFilePath.string());
        const std::string fragmentShaderContent = Utils::read_file(fragmentFilePath.string());

        // Compile vertex and fragment shaders
        uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderContent);
        uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderContent);

        // Link the compiled shaders to the shader program
        ShaderHandle handle = glCreateProgram();
        glAttachShader(handle, vertexShader);
        glAttachShader(handle, fragmentShader);
        glLinkProgram(handle);

        // Check for errors
        int success;
        char infoLog[512];
        glGetProgramiv(handle, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(handle, 512, NULL, infoLog);
            RND_CORE_ERROR("Failed to link shader program!", infoLog);
        }

        // Cleanup shaders since they are already linked to the shader program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return handle;
    }

    void shader_program_destroy(ShaderHandle handle)
    {
        glDeleteProgram(handle);
    }

    void shader_program_use(ShaderHandle handle)
    {
        glUseProgram(handle);
    }

} // namespace Rendurr
