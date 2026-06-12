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
        .attachments = {{.key = "color", .format = Rendurr::ColorAttachmentFormat::RGBA8},
                        {.key = "red", .format = Rendurr::ColorAttachmentFormat::RGBA8}}};
    Rendurr::Framebuffer fb = Rendurr::framebuffer_create(spec);

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
                                   .renderContext = {.framebuffer = fb},
                                   .assetManager = {},
                                   .uiContext = {.viewportWidth = 0.0f, .viewportHeight = 0.0f},
                                   .activeScene = {}};

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
        if (state.uiContext.viewportFocused) {
            cameraController.update(state.input);
        }
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
        Rendurr::framebuffer_bind(state.renderContext.framebuffer);

        Rendurr::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Rendurr::clear();

        // todo Unsafe
        // todo pass in state?
        render_scene(state.activeScene, state.assetManager, shader);
        Rendurr::framebuffer_unbind();

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