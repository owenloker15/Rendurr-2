#pragma once

#include "Material.hpp"

#include <Render/VertexArray.hpp>
#include <Render/VertexBuffer.hpp>

namespace Rendurr
{
	class Mesh
	{
	public:
		Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, Material&& material);

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&&) = default;
		Mesh& operator=(Mesh&&) = default;

		const VertexArray& getVertexArray() const;

		const Material& getMaterial() const;
	private:
		VertexArray m_vertexArray;
		Material m_material;
	};
}
