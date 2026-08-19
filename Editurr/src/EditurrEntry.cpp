#include <EditurrConfig.h>
#include <Rendurr.h>

#include "Core/Window.h"
#include "Editurr.h"
#include "glm/ext/matrix_transform.hpp"
#include "Render/EditurrRender.h"
#include "Render/Framebuffer.hpp"
#include "Render/Renderer.hpp"
#include "Scene/AssetManager.h"
#include "Scene/CameraController.hpp"
#include "Scene/Texture.h"
#include "UI/EditurrUI.h"
#include "UI/UI.h"
#include "Utils/Timer.hpp"

int main()
{
    // Initialize Rendurr library
    rnd::init();

    // Initialize objects

    // Window
    rnd::WindowSpec windowSpec = {.title = "Editurr", .width = 1280, .height = 720};
    rnd::Window window = rnd::window_create(windowSpec);

    // UI
    Editurr::ui_init(window);

    // Framebuffer
    rnd::FramebufferSpecification spec = {
        .width = window.specification.width,
        .height = window.specification.height,
        .attachments = {{.key = "color", .format = rnd::ColorAttachmentFormat::RGBA8},
                        {.key = "red", .format = rnd::ColorAttachmentFormat::RGBA8}}};
    rnd::Framebuffer fb = rnd::framebuffer_create(spec);

    // Log

    // Camera
    rnd::CameraController cameraController = {1280.0 / 720,
                                                  5.0,
                                                  rnd::ProjectionType::Ortho};

    // Shader
    const std::filesystem::path assetDir(EDITURR_ASSETS_DIR);
    const rnd::ShaderData shader =
        rnd::shader_program_create(assetDir / "shaders" / "vertex.glsl",
                                       assetDir / "shaders" / "frag.glsl");

    // Editurr global state
    Editurr::EditurrState state = {.renderContext = {.framebuffer = fb}};

    Editurr::Entity& entity = Editurr::scene_create_entity(state.activeScene, "backpack");
    const auto modelHandle =
        Editurr::model_import_from_file(state.assetManager,
                                        assetDir / "models" / "backpack" / "backpack.obj");
    entity.model = modelHandle;
    entity.transform = {.translation = {0.0f, 0.0f, 0.0f},
                        .rotation = {0.0f, 0.0f, 1.0f},
                        .scale = {1.0f, 1.0f, 1.0f}};

    Editurr::model_import_from_file(state.assetManager, assetDir / "models" / "cube" / "Cube.obj");

    rnd::enableDepthTesting();

    const auto lastFrameTime = rnd::time_current();

    while (!state.input.windowCloseRequested) {
        // Frame time delta
        const auto currentFrameTime = rnd::time_current();
        const auto dt = rnd::time_delta(currentFrameTime, lastFrameTime);

        // Event polling
        rnd::poll_events();
        rnd::window_retrieve_events(window, state.input);

        // Process inputs

        // Update
        if (state.uiContext.viewportFocused) {
            cameraController.update(state.input);
        }
        const glm::mat4 viewMatrix = cameraController.getViewMatrix();
        const glm::mat4 projectionMatrix = cameraController.getProjectionMatrix();
        const glm::vec3& cameraPos = cameraController.cameraPos();
        rnd::shader_uniform_upload_mat4(shader, "u_ViewMatrix", viewMatrix);
        rnd::shader_uniform_upload_mat4(shader, "u_ProjectionMatrix", projectionMatrix);
        rnd::shader_uniform_upload_vec3(shader, "u_ViewPos", cameraPos);

        // TODO light
        rnd::shader_uniform_upload_vec3(shader, "light.position", {0.0f, 0.0f, 3.0f});
        rnd::shader_uniform_upload_vec3(shader, "light.ambient", {0.2f, 0.2f, 0.2f});
        rnd::shader_uniform_upload_vec3(shader, "light.diffuse", {0.5f, 0.5f, 0.5f});
        rnd::shader_uniform_upload_vec3(shader, "light.specular", {1.0f, 1.0f, 1.0f});

        // TODO material
        // TODO hardcoded to texture slot 0

        // Render to framebuffer
        rnd::framebuffer_bind(state.renderContext.framebuffer);

        rnd::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        rnd::clear();

        // todo Unsafe
        // todo pass in state?
        render_scene(state.activeScene, state.assetManager, shader);
        rnd::framebuffer_unbind();

        // UI rendering
        Editurr::ui_frame_begin();
        Editurr::editurr_ui_draw(state);
        Editurr::ui_frame_end();
        // Present frame? currently just done in ui_frame_end

        // Swap window buffers
        rnd::window_swap_buffers(window);
    }

    Editurr::ui_shutdown();
    rnd::window_destroy(window);
    return 0;
}