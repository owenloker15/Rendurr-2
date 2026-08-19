/*
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
    class EditurrLayer : public rnd::Layer
    {
    public:
        EditurrLayer(std::string name);

        void onAttach() override;
        void onUpdate(float dt) override;
        void onUiRender() override;

    private:
        rnd::AssetManager m_assetManager;
        rnd::CameraController m_cameraController;
        std::unique_ptr<rnd::Framebuffer> m_pFramebuffer;
        rnd::ShaderHandle m_shaderHandle;
        glm::vec2 m_viewportSize;
    };
} // namespace Editurr
*/
