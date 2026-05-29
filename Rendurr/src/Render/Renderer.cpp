#include "Renderer.hpp"

#include <glad/glad.h>
#include <iostream>

#include "Scene/Components.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace
{
    void drawIndexed(const Rendurr::VertexArray& vertexArray)
    {
        vertexArray.bind();
        glDrawElements(GL_TRIANGLES,
                       vertexArray.getIndexBuffer().getIndexCount(),
                       GL_UNSIGNED_INT,
                       nullptr);
        vertexArray.unbind();
    }

    void drawMesh(const Rendurr::Mesh& mesh, const std::shared_ptr<Rendurr::Shader>& pShader)
    {
        pShader->use();

        for (const auto& texture : mesh.getMaterial().getTextures()) {
            const auto nameToSlot = Rendurr::Texture::TextureTypeToString(texture.getType());
            Rendurr::TextureUniform textureUniform{nameToSlot.first, nameToSlot.second};
            texture.bind(nameToSlot.second);
            pShader->uploadUniformSet(textureUniform);
        }

        drawIndexed(mesh.getVertexArray());
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
                             const std::shared_ptr<Shader>& pShader)
    {
        pShader->use();

        pScene->forEachEntity([&pScene, &pShader](Entity entity) {
            const auto transformComponent = pScene->getTransformComponent(entity);
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
            pShader->uploadUniformSet(transformUniform);

            const auto& meshComponent = pScene->getMeshComponent(entity);
            drawMesh(meshComponent.mesh, pShader);
        });
    }
} // namespace Rendurr
