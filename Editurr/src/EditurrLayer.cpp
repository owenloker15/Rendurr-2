#include "EditurrLayer.hpp"

#include <Render/Renderer.hpp>
#include <Scene/Mesh.hpp>
#include <Scene/OrthographicProjectionStrategy.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>

#include "Editurr.hpp"
#include "EditurrConfig.h"
#include "EditurrUtils.hpp"
#include "Scene/Components.hpp"

namespace
{
    void dockspaceBegin()
    {
        // READ THIS !!!
        // TL;DR; this demo is more complicated than what most users you would normally use.
        // If we remove all options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
        //     }
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the
        // code below! In this specific demo, we are not using DockSpaceOverViewport() because:
        // - (1) we allow the host window to be floating/moveable instead of filling the viewport
        // (when opt_fullscreen == false)
        // - (2) we allow the host window to have padding (when opt_padding == true)
        // - (3) we expose many flags and need a way to have them visible.
        // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() +
        // DockSpaceOverViewport()
        //      in your code, but we don't here because we allow the window to be floating)

        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable
        // into, because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive
        // docking, otherwise any change of dockspace/settings would lead to windows being stuck in
        // limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }

    void dockspaceEnd()
    {
        ImGui::End();
    }

} // namespace

namespace Editurr
{
    EditurrLayer::EditurrLayer(std::string name)
        : m_cameraController(1280.0 / 720,
                             5.0,
                             std::make_unique<Rendurr::OrthographicProjectionStrategy>()),
          Layer(name)
    {
        Editurr::getInstance().setActiveScene(Editurr::getInstance().createScene());

        const std::filesystem::path assetDir(EDITURR_ASSETS_DIR);
        m_pShader = std::make_shared<Rendurr::Shader>(assetDir / "shaders" / "vertex.glsl",
                                                      assetDir / "shaders" / "frag.glsl");

        std::vector<Rendurr::Vertex> vertices = {
            // Front face
            {{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0}},
            {{0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0}},
            {{0.5f, 0.5f, 0.5f}, {0, 0, 1}, {1, 1}},
            {{-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 1}},

            // Back face
            {{0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 0}},
            {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0}},
            {{-0.5f, 0.5f, -0.5f}, {0, 0, -1}, {1, 1}},
            {{0.5f, 0.5f, -0.5f}, {0, 0, -1}, {0, 1}},

            // Left face
            {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0}},
            {{-0.5f, -0.5f, 0.5f}, {-1, 0, 0}, {1, 0}},
            {{-0.5f, 0.5f, 0.5f}, {-1, 0, 0}, {1, 1}},
            {{-0.5f, 0.5f, -0.5f}, {-1, 0, 0}, {0, 1}},

            // Right face
            {{0.5f, -0.5f, 0.5f}, {1, 0, 0}, {0, 0}},
            {{0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 0}},
            {{0.5f, 0.5f, -0.5f}, {1, 0, 0}, {1, 1}},
            {{0.5f, 0.5f, 0.5f}, {1, 0, 0}, {0, 1}},

            // Top face
            {{-0.5f, 0.5f, 0.5f}, {0, 1, 0}, {0, 0}},
            {{0.5f, 0.5f, 0.5f}, {0, 1, 0}, {1, 0}},
            {{0.5f, 0.5f, -0.5f}, {0, 1, 0}, {1, 1}},
            {{-0.5f, 0.5f, -0.5f}, {0, 1, 0}, {0, 1}},

            // Bottom face
            {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 0}},
            {{0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 0}},
            {{0.5f, -0.5f, 0.5f}, {0, -1, 0}, {1, 1}},
            {{-0.5f, -0.5f, 0.5f}, {0, -1, 0}, {0, 1}},
        };

        std::vector<uint32_t> indices = {
            0,  2,  1,  2,  0,  3,  // Front
            4,  6,  5,  6,  4,  7,  // Back
            8,  10, 9,  10, 8,  11, // Left
            12, 14, 13, 14, 12, 15, // Right
            16, 18, 17, 18, 16, 19, // Top
            20, 22, 21, 22, 20, 23  // Bottom
        };

        std::shared_ptr<Rendurr::Scene> pActiveScene = Editurr::getInstance().getActiveScene();

        Rendurr::Entity entity = pActiveScene->createEntity();

        Rendurr::Material material;
        const std::filesystem::path wallTexturePath = assetDir / "textures" / "wall.jpg";
        material.addTexture(wallTexturePath, Rendurr::TextureType::Ambient);

        Rendurr::Mesh mesh(std::move(vertices), std::move(indices), std::move(material));

        Rendurr::MeshComponent meshComponent(std::move(mesh));
        pActiveScene->addComponent(entity, std::move(meshComponent));

        Rendurr::TransformComponent transformComponent({0.0f, 0.0f, 0.0f},
                                                       {0.0f, 0.0f, 1.0f},
                                                       {1.0f, 1.0f, 1.0f});
        pActiveScene->addComponent(entity, std::move(transformComponent));

        Rendurr::FramebufferSpecification spec;
        spec.width = Rendurr::Application::getInstance().getWindow()->getWidth();
        spec.height = Rendurr::Application::getInstance().getWindow()->getHeight();
        spec.m_colorAttachments = {{"color", Rendurr::ColorAttachmentFormat::RGBA8},
                                   {"red", Rendurr::ColorAttachmentFormat::RGBA8}};
        m_pFramebuffer = std::make_unique<Rendurr::Framebuffer>(spec);
    }

    void EditurrLayer::onAttach() {}

    void EditurrLayer::onUpdate(float dt)
    {
        m_pFramebuffer->bind();

        Rendurr::Renderer::setClearColor({1.0f, 1.0f, 1.0f, 1.0f});
        Rendurr::Renderer::clear();

        glm::mat4 viewMatrix = m_cameraController.getViewMatrix();
        glm::mat4 projectionMatrix = m_cameraController.getProjectionMatrix();
        Rendurr::CameraUniform cameraUniform{viewMatrix, projectionMatrix};
        m_pShader->uploadUniformSet(cameraUniform);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, {0.0f, 0.0f, 0.0f});
        transform = glm::rotate(transform, dt, glm::vec3(0.0f, 0.0f, 1.0f));

        // todo Unsafe
        Rendurr::Renderer::drawScene(Editurr::getInstance().getActiveScene(), m_pShader);
        m_pFramebuffer->unbind();
    }

    void EditurrLayer::onUiRender()
    {
        dockspaceBegin();

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    Rendurr::Application::getInstance().close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        /*
        m_viewportFocused = ImGui::IsWindowFocused();
        Application::Get().GetUILayer()->BlockEvents(!m_viewportFocused);
        */

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_viewportSize = {viewportPanelSize.x, viewportPanelSize.y};

        uint32_t textureID = m_pFramebuffer->getColorAttachmentId("color");
        ImGui::Image(textureID,
                     ImVec2{m_viewportSize.x, m_viewportSize.y},
                     ImVec2(0, 1),
                     ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();

        dockspaceEnd();
    }
} // namespace Editurr
