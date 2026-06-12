#pragma once

#include <filesystem>

namespace Rendurr
{
    struct AssetManager;

    enum class TextureType : uint8_t
    {
        Diffuse,
        Specular,
        Normal,
        Ambient,
        Roughness,
        Metallic,
        Emissive
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

    TextureData texture_create(const std::filesystem::path& path, TextureType type);
    void texture_destroy();
    void texture_bind(TextureData data, uint16_t textureSlot);

    // TODO make this lookup where enum is index in array
    constexpr TextureUniformData texture_uniform_data(TextureType type)
    {
        switch (type) {
            case TextureType::Diffuse:
                return {"material.diffuse", 0};
            case TextureType::Specular:
                return {"material.specular", 1};
            case TextureType::Normal:
                return {"material.normal", 2};
            case TextureType::Ambient:
                return {"material.ambient", 3};
            case TextureType::Roughness:
                return {"material.roughness", 4};
            case TextureType::Metallic:
                return {"material.metallic", 5};
            case TextureType::Emissive:
                return {"material.emissive", 6};
        }
        return {};
    }

} // namespace Rendurr
