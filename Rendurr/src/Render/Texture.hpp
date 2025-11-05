#pragma once

#include <string>

namespace Rendurr
{
	class Texture
	{
	public:
		Texture(const std::string& filepath);
		~Texture() = default;

		void bind(uint32_t textureSlot) const;
	private:
		uint32_t m_rendererId;
	};
}
