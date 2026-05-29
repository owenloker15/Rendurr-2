#include "Mesh.hpp"

namespace Rendurr
{
    Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
        : m_vertexArray(std::move(vertices), std::move(indices))
    {}

    Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, Material&& material)
        : m_vertexArray(std::move(vertices), std::move(indices)), m_material(std::move(material))
    {}

    const VertexArray& Mesh::getVertexArray() const
    {
        return m_vertexArray;
    }

    const Material& Mesh::getMaterial() const
    {
        return m_material;
    }
} // namespace Rendurr
