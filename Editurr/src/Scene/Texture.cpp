#include "Texture.h"

namespace Editurr
{
    AssetHandle texture_create(AssetManager& assetManager,
                               const std::filesystem::path& path,
                               Rendurr::TextureType type)
    {
        AssetHandle handle = assetManager.m_textures.size();
        assetManager.m_textures.emplace_back(Rendurr::texture_create(path, type));
        return handle;
    }
} // namespace Editurr