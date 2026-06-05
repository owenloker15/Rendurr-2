#pragma once

#include <Rendurr.hpp>

#include "Render/Framebuffer.hpp"
#include "Render/Texture.hpp"
#include "Render/VertexArray.hpp"
#include "Scene/AssetManager.h"
#include "Scene/Camera.hpp"
#include "Scene/CameraController.hpp"
#include "Scene/Mesh.hpp"

namespace Editurr
{
    class EditurrLayer : public Rendurr::Layer
    {
    public:
        EditurrLayer(std::string name);

        void onAttach() override;
        void onUpdate(float dt) override;
        void onUiRender() override;

    private:
        Rendurr::CameraController m_cameraController;
        glm::vec2 m_viewportSize;

        Rendurr::ShaderHandle m_shaderHandle;
        std::unique_ptr<Rendurr::Framebuffer> m_pFramebuffer;
        Rendurr::AssetManager m_assetManager;
    };
} // namespace Editurr
