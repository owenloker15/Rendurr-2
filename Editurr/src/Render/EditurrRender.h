#pragma once

#include "../Scene/AssetManager.h"
#include "../Scene/Scene.h"
#include "Render/Shader.hpp"

namespace Editurr
{
    void render_scene(const Scene& scene,
                      const AssetManager& assetManager,
                      const Rendurr::ShaderData& shader);
}