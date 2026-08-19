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
        float viewportWidth, viewportHeight = 0;
        uint64_t selectedEntity = 0;
        bool viewportFocused = false;
    };

    struct RenderContext
    {
        rnd::Framebuffer framebuffer;
    };

    struct EditurrState
    {
        rnd::Input input{};
        AssetManager assetManager{};
        Scene activeScene{};
        UIContext uiContext{};
        RenderContext renderContext{};
    };

} // namespace Editurr
