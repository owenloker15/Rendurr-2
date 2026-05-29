#pragma once

#include <filesystem>

#include "Render/Texture.hpp"

namespace Rendurr
{
    class Material
    {
    public:
        Material() = default;
        ~Material() = default;

        void addTexture(const std::filesystem::path& filePath, TextureType type);
        const std::vector<Texture>& getTextures() const;

    private:
        std::vector<Texture> m_textures;
    };
} // namespace Rendurr
