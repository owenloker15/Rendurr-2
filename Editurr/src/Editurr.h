#pragma once

#include <memory>

#include "Core/Input.h"
#include "Render/Framebuffer.hpp"
#include "Scene/AssetManager.h"
#include "Scene/Scene.h"

namespace Editurr
{
    struct UIContext
    {
        float viewportWidth, viewportHeight;
    };

    struct RenderContext
    {
        Rendurr::Framebuffer framebuffer;
    };

    struct EditurrState
    {
        Rendurr::Input input;
        RenderContext renderContext;
        AssetManager assetManager;
        UIContext uiContext;
        Scene activeScene;
    };

} // namespace Editurr
