#include "Renderer.hpp"

#include <glad/glad.h>
#include <iostream>

#include "glm/ext/matrix_transform.hpp"
#include "Scene/AssetManager.h"
#include "Scene/Components.hpp"

namespace
{
    void drawIndexed(uint32_t vertexArrayRendererId, uint32_t indexCount)
    {
        Rendurr::vertex_array_bind(vertexArrayRendererId);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        Rendurr::vertex_array_unbind();
    }

    void upload_material_to_shader(const Rendurr::AssetManager& assetManager,
                                   Rendurr::MaterialHandle materialHandle,
                                   Rendurr::ShaderHandle shaderHandle)
    {
        Rendurr::shader_program_use(shaderHandle);

        const auto& materialData = asset_manager_get_material(assetManager, materialHandle);
        for (const auto& textureHandle : materialData.textureHandles) {
            const auto& textureData = asset_manager_get_texture(assetManager, textureHandle);
            const auto uniformData = Rendurr::texture_uniform_data(textureData.type);
            const auto& textureSlot = uniformData.textureSlot;
            Rendurr::TextureUniform textureUniform{uniformData.uniformName, textureSlot};
            Rendurr::texture_bind(textureData.rendererId, textureSlot);
            Rendurr::shader_program_upload_uniform(shaderHandle, std::move(textureUniform));
        }
    }

    void glDebugOutput(GLenum source,
                       GLenum type,
                       unsigned int id,
                       GLenum severity,
                       GLsizei length,
                       const char* message,
                       const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " << message << std::endl;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                std::cout << "Source: API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cout << "Source: Window System";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cout << "Source: Shader Compiler";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cout << "Source: Third Party";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                std::cout << "Source: Application";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                std::cout << "Source: Other";
                break;
        }
        std::cout << std::endl;

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                std::cout << "Type: Error";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cout << "Type: Deprecated Behaviour";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cout << "Type: Undefined Behaviour";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                std::cout << "Type: Portability";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cout << "Type: Performance";
                break;
            case GL_DEBUG_TYPE_MARKER:
                std::cout << "Type: Marker";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                std::cout << "Type: Push Group";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                std::cout << "Type: Pop Group";
                break;
            case GL_DEBUG_TYPE_OTHER:
                std::cout << "Type: Other";
                break;
        }
        std::cout << std::endl;

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cout << "Severity: high";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cout << "Severity: medium";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cout << "Severity: low";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cout << "Severity: notification";
                break;
        }
        std::cout << std::endl;
    }
} // namespace

namespace Rendurr
{
    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::setClearColor(const glm::vec4& rgba)
    {
        glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
    }

    void Renderer::setViewport(float width, float height)
    {
        glViewport(0, 0, width, height);
    }

    void Renderer::enableDepthTesting()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::enableDebug()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    void Renderer::drawScene(const std::shared_ptr<Scene>& pScene,
                             const AssetManager& assetManager,
                             const ShaderHandle& shaderHandle)
    {
        Rendurr::shader_program_use(shaderHandle);

        pScene->forEachEntity([&pScene, &assetManager, &shaderHandle](Entity entity) {
            const TransformComponent& transformComponent = pScene->getTransformComponent(entity);
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, transformComponent.translation);
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.x),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.y),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform,
                                    glm::radians(transformComponent.rotation.z),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, transformComponent.scale);

            MeshTransformUniform transformUniform{transform};
            Rendurr::shader_program_upload_uniform(shaderHandle, std::move(transformUniform));

            const MeshComponent& meshComponent = pScene->getMeshComponent(entity);
            const auto& meshData = asset_manager_get_mesh(assetManager, meshComponent.handle);
            upload_material_to_shader(assetManager, meshData.mHandle, shaderHandle);
            drawIndexed(meshData.vaRendererId, meshData.indexCount);
        });
    }
} // namespace Rendurr
