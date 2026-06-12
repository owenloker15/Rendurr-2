#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "AssetManager.h"
#include "Core/Log.h"
#include "Material.h"
#include "Mesh.h"
#include "Render/Texture.hpp"
#include "Render/VertexBuffer.hpp"
#include "Texture.h"

namespace
{
    void load_material_textures(Editurr::AssetManager& assetManager,
                                aiMaterial* aiMat,
                                aiTextureType assimpType,
                                Rendurr::TextureType textureType,
                                const std::filesystem::path& modelDirectory,
                                Editurr::AssetHandle materialHandle)
    {
        uint32_t count = aiMat->GetTextureCount(assimpType);

        for (uint32_t i = 0; i < count; ++i) {
            aiString texturePath;

            if (aiMat->GetTexture(assimpType, i, &texturePath) != AI_SUCCESS) {
                continue;
            }

            std::filesystem::path fullPath = modelDirectory / texturePath.C_Str();

            Editurr::AssetHandle textureHandle =
                Editurr::texture_create(assetManager, fullPath, textureType);

            material_add_texture(assetManager, materialHandle, textureHandle);
        }
    }

    std::vector<Editurr::AssetHandle> load_materials(Editurr::AssetManager& assetManager,
                                                     const aiScene* scene,
                                                     const std::filesystem::path& modelDirectory)
    {
        std::vector<Editurr::AssetHandle> materials;
        materials.reserve(scene->mNumMaterials);

        for (uint32_t i = 0; i < scene->mNumMaterials; ++i) {
            aiMaterial* aiMat = scene->mMaterials[i];

            Editurr::AssetHandle materialHandle = material_create(assetManager);

            load_material_textures(assetManager,
                                   aiMat,
                                   aiTextureType_DIFFUSE,
                                   Rendurr::TextureType::Diffuse,
                                   modelDirectory,
                                   materialHandle);

            load_material_textures(assetManager,
                                   aiMat,
                                   aiTextureType_SPECULAR,
                                   Rendurr::TextureType::Specular,
                                   modelDirectory,
                                   materialHandle);

            load_material_textures(assetManager,
                                   aiMat,
                                   aiTextureType_NORMALS,
                                   Rendurr::TextureType::Normal,
                                   modelDirectory,
                                   materialHandle);

            load_material_textures(assetManager,
                                   aiMat,
                                   aiTextureType_AMBIENT,
                                   Rendurr::TextureType::Ambient,
                                   modelDirectory,
                                   materialHandle);

            materials.push_back(materialHandle);
        }

        return materials;
    }
} // namespace

namespace Editurr
{
    AssetHandle model_import_from_file(AssetManager& assetManager,
                                       const std::filesystem::path& path)
    {
        AssetHandle handle = assetManager.m_models.size();
        ModelData data;

        Assimp::Importer importer;

        const aiScene* scene =
            importer.ReadFile(path.string(),
                              aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                  aiProcess_JoinIdenticalVertices);

        if (!scene) {
            RND_CORE_ERROR("Error reading model at path {} with error: {}",
                           path.string(),
                           importer.GetErrorString());
            throw std::runtime_error(importer.GetErrorString());
            // TODO invalid handle
        }

        std::filesystem::path modelDirectory = path.parent_path();

        auto materialHandles = load_materials(assetManager, scene, modelDirectory);

        for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
            aiMesh* mesh = scene->mMeshes[meshIndex];

            std::vector<Rendurr::Vertex> vertices;
            std::vector<uint32_t> indices;

            for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
                Rendurr::Vertex vertex{};

                vertex.position = {mesh->mVertices[i].x,
                                   mesh->mVertices[i].y,
                                   mesh->mVertices[i].z};

                if (mesh->HasNormals()) {
                    vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
                }

                if (mesh->HasTextureCoords(0)) {
                    vertex.texCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
                }

                vertices.push_back(vertex);
            }

            for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
                const aiFace& face = mesh->mFaces[i];

                // Triangulate guarantees 3 indices.
                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
            }

            AssetHandle materialHandle = materialHandles[mesh->mMaterialIndex];

            data.meshes.emplace_back(
                mesh_create(std::move(vertices), std::move(indices), materialHandle));
        }

        assetManager.m_models.emplace_back(std::move(data));

        return handle;
    }
} // namespace Editurr