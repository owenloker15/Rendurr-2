#pragma once

#include <filesystem>

namespace Rendurr
{
    enum class TextureType
    {
        Ambient
    };

    class Texture
    {
    public:
        Texture(const std::filesystem::path& filepath, TextureType type);
        ~Texture() = default;

        TextureType getType() const;

        void bind(uint32_t textureSlot) const;

        static std::pair<std::string, uint32_t> TextureTypeToString(TextureType type);

    private:
        uint32_t m_rendererId;
        TextureType m_type;
    };
} // namespace Rendurr
