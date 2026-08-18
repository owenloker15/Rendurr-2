#pragma once

namespace Editurr
{
    struct Texture
    {
        Rendurr::TextureData textureData;
        AssetHandle handle = generate_asset_handle();
    };
} // namespace Editurr
