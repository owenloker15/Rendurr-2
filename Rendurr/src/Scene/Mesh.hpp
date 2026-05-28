#pragma once

#include "Material.hpp"

#include <Render/VertexArray.hpp>
#include <Render/VertexBuffer.hpp>

namespace Rendurr
{
	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Material material);

		const VertexArray& getVertexArray() const;

		const Material& getMaterial() const;
	private:
		VertexArray m_vertexArray;
		Material m_material;
	};
}
