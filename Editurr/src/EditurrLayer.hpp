#pragma once

#include <Rendurr.hpp>

#include "Render/Framebuffer.hpp"
#include "Render/Texture.hpp"
#include "Render/VertexArray.hpp"

#include "Scene/Camera.hpp"
#include "Scene/CameraController.hpp"

namespace Editurr
{
	class EditurrLayer : public Rendurr::Layer
	{
	public:
		EditurrLayer(std::string name);

		void onAttach() override;
		void onUpdate(float dt) override;
		void onUiRender() override;
	private:
		Rendurr::CameraController m_cameraController;
		glm::vec2 m_viewportSize;

		std::unique_ptr<Rendurr::Shader> m_shader;
		std::unique_ptr<Rendurr::VertexArray> m_vertexArray;
		std::unique_ptr<Rendurr::Texture> m_texture;
		std::unique_ptr<Rendurr::Framebuffer> m_framebuffer;
	};
}
