#include "Material.hpp"

#include "Render/Texture.hpp"

namespace Rendurr
{
    void Material::addTexture(const std::filesystem::path& filePath, TextureType type)
    {
        m_textures.emplace_back(filePath, type);
    }

    const std::vector<Texture>& Material::getTextures() const
    {
        return m_textures;
    }
} // namespace Rendurr
