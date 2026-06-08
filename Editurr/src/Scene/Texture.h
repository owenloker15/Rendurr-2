#pragma once
#include "AssetManager.h"

namespace Editurr
{
    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type);
}