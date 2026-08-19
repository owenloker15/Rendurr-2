#pragma once

namespace Editurr
{
    struct Texture
    {
        rnd::TextureData textureData;
        AssetHandle handle = generate_asset_handle();
    };
} // namespace Editurr
