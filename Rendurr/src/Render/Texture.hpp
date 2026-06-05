#pragma once

#include <filesystem>

namespace Rendurr
{
    struct AssetManager;

    typedef uint32_t TextureHandle;

    enum class TextureType : uint8_t
    {
        Ambient
    };

    struct TextureData
    {
        const char* name;
        uint32_t rendererId;
        TextureType type;
    };

    struct TextureUniformData
    {
        const char* uniformName;
        uint16_t textureSlot;
    };

    TextureHandle texture_create(AssetManager& assetManager,
                                 const std::filesystem::path& path,
                                 TextureType type);
    void texture_destroy(TextureHandle handle);
    void texture_bind(TextureHandle handle, uint16_t textureSlot);

    // TODO make this lookup where enum is index in array
    constexpr TextureUniformData texture_uniform_data(TextureType type)
    {
        switch (type) {
            case TextureType::Ambient:
                return {"u_Material_albedo", 0};
        }
        return {};
    }

} // namespace Rendurr
