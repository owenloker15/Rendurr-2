#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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

namespace rnd
{
    ShaderData shader_program_create(const std::filesystem::path& vertexFilePath,
                                     const std::filesystem::path& fragmentFilePath)
    {
        const std::string vertexFilePathStr = vertexFilePath.string();
        const std::string fragmentFilePathStr = fragmentFilePath.string();

        const std::string vertexShaderContent = Utils::read_file(vertexFilePathStr);
        const std::string fragmentShaderContent = Utils::read_file(fragmentFilePathStr);

        // Compile vertex and fragment shaders
        uint32_t vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderContent);
        uint32_t fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderContent);

        // Link the compiled shaders to the shader program
        uint32_t rendererId = glCreateProgram();
        glAttachShader(rendererId, vertexShader);
        glAttachShader(rendererId, fragmentShader);
        glLinkProgram(rendererId);

        // Check for errors
        int success;
        char infoLog[512];
        glGetProgramiv(rendererId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(rendererId, 512, NULL, infoLog);
            RND_CORE_ERROR("Failed to link shader program!", infoLog);
        }

        // Cleanup shaders since they are already linked to the shader program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return {.vertexFilePath = vertexFilePathStr.c_str(),
                .fragmentFilePath = fragmentFilePathStr.c_str(),
                .rendererId = rendererId};
    }

    void shader_program_destroy(const ShaderData& shader)
    {
        glDeleteProgram(shader.rendererId);
    }

    void shader_program_use(const ShaderData& shader)
    {
        glUseProgram(shader.rendererId);
    }

    void shader_uniform_upload_bool(const ShaderData& shader, const char* uniformName, bool value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform1i(location, value ? 1 : 0);
    }

    void shader_uniform_upload_int(const ShaderData& shader, const char* uniformName, int value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform1i(location, value);
    }

    void shader_uniform_upload_float(const ShaderData& shader, const char* uniformName, float value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform1f(location, value);
    }

    void shader_uniform_upload_vec2(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec2& value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform2fv(location, 1, glm::value_ptr(value));
    }

    void shader_uniform_upload_vec3(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec3& value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void shader_uniform_upload_vec4(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::vec4& value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    void shader_uniform_upload_mat3(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::mat3& value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void shader_uniform_upload_mat4(const ShaderData& shader,
                                    const char* uniformName,
                                    const glm::mat4& value)
    {
        shader_program_use(shader);
        GLint location = getUniformLocation(shader.rendererId, uniformName);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
} // namespace rnd
