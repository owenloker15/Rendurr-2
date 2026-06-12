#include <EditurrConfig.h>
#include <Rendurr.h>

#include "Core/Window.h"
#include "Editurr.h"
#include "glm/ext/matrix_transform.hpp"
#include "Render/EditurrRender.h"
#include "Render/Framebuffer.hpp"
#include "Render/Renderer.hpp"
#include "Render/VertexBuffer.hpp"
#include "Scene/AssetManager.h"
#include "Scene/CameraController.hpp"
#include "Scene/Material.h"
#include "Scene/Model.h"
#include "Scene/Texture.h"
#include "UI/EditurrUI.h"
#include "UI/UI.h"
#include "Utils/Timer.hpp"

int main()
{
    // Initialize Rendurr library
    Rendurr::init();

    // Initialize objects

    // Window
    Rendurr::WindowSpec windowSpec = {.title = "Editurr", .width = 1280, .height = 720};
    Rendurr::Window window = Rendurr::window_create(windowSpec);

    // UI
    Editurr::ui_init(window);

    // Framebuffer
    Rendurr::FramebufferSpecification spec = {
        .width = window.specification.width,
        .height = window.specification.height,
        .m_colorAttachments = {{"color", Rendurr::ColorAttachmentFormat::RGBA8},
                               {"red", Rendurr::ColorAttachmentFormat::RGBA8}}};

    // Log

    // Camera
    Rendurr::CameraController cameraController = {1280.0 / 720,
                                                  5.0,
                                                  Rendurr::ProjectionType::Ortho};

    // Shader
    const std::filesystem::path assetDir(EDITURR_ASSETS_DIR);
    const Rendurr::ShaderData shader =
        Rendurr::shader_program_create(assetDir / "shaders" / "vertex.glsl",
                                       assetDir / "shaders" / "frag.glsl");

    // Editurr global state
    Editurr::EditurrState state = {.input = {},
                                   .renderContext = {.framebuffer = {spec}},
                                   .assetManager = {},
                                   .uiContext = {.viewportWidth = 0.0f, .viewportHeight = 0.0f},
                                   .activeScene = {}};

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

    Editurr::Entity& entity = Editurr::scene_create_entity(state.activeScene);
    const auto modelHandle =
        Editurr::model_import_from_file(state.assetManager,
                                        assetDir / "models" / "backpack" / "backpack.obj");
    entity.name = "Backpack";
    entity.model = modelHandle;
    entity.transform = {.translation = {0.0f, 0.0f, 0.0f},
                        .rotation = {0.0f, 0.0f, 1.0f},
                        .scale = {1.0f, 1.0f, 1.0f}};

    Rendurr::enableDepthTesting();

    const auto lastFrameTime = Rendurr::time_current();

    while (!state.input.windowCloseRequested) {
        // Frame time delta
        const auto currentFrameTime = Rendurr::time_current();
        const auto dt = Rendurr::time_delta(currentFrameTime, lastFrameTime);

        // Event polling
        Rendurr::poll_events();
        Rendurr::window_retrieve_events(window, state.input);

        // Process inputs

        // Update
        cameraController.update(state.input);
        const glm::mat4 viewMatrix = cameraController.getViewMatrix();
        const glm::mat4 projectionMatrix = cameraController.getProjectionMatrix();
        const glm::vec3& cameraPos = cameraController.cameraPos();
        Rendurr::shader_uniform_upload_mat4(shader, "u_ViewMatrix", viewMatrix);
        Rendurr::shader_uniform_upload_mat4(shader, "u_ProjectionMatrix", projectionMatrix);
        Rendurr::shader_uniform_upload_vec3(shader, "u_ViewPos", cameraPos);

        // TODO light
        Rendurr::shader_uniform_upload_vec3(shader, "light.position", {0.0f, 0.0f, 3.0f});
        Rendurr::shader_uniform_upload_vec3(shader, "light.ambient", {0.2f, 0.2f, 0.2f});
        Rendurr::shader_uniform_upload_vec3(shader, "light.diffuse", {0.5f, 0.5f, 0.5f});
        Rendurr::shader_uniform_upload_vec3(shader, "light.specular", {1.0f, 1.0f, 1.0f});

        // TODO material
        // TODO hardcoded to texture slot 0

        // Render to framebuffer
        state.renderContext.framebuffer.bind();

        Rendurr::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Rendurr::clear();

        // todo Unsafe
        // todo pass in state?
        render_scene(state.activeScene, state.assetManager, shader);
        state.renderContext.framebuffer.unbind();

        // UI rendering
        Editurr::ui_frame_begin();
        Editurr::editurr_ui_draw(state);
        Editurr::ui_frame_end();
        // Present frame? currently just done in ui_frame_end

        // Swap window buffers
        Rendurr::window_swap_buffers(window);
    }

    Editurr::ui_shutdown();
    Rendurr::window_destroy(window);
    return 0;
}