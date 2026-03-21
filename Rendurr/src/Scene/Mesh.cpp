#include "Mesh.hpp"

namespace Rendurr
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) : m_vertexArray(vertices, indices) {}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Material material) : m_vertexArray(vertices, indices), m_material(std::move(material)) {}

	const VertexArray& Mesh::getVertexArray() const
	{
		return m_vertexArray;
	}

	const Material& Mesh::getMaterial() const
	{
		return m_material;
	}
}
