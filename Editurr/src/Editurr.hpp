#pragma once

#include <memory>

#include <Scene/Scene.hpp>

namespace Editurr
{
	class Editurr
	{
	public:
		Editurr(const Editurr&) = delete;
		Editurr& operator=(const Editurr&) = delete;
		Editurr(Editurr&&) = delete;
		Editurr& operator=(Editurr&&) = delete;

		static Editurr& getInstance();

		static Rendurr::Scene createScene();
		void setActiveScene(Rendurr::Scene scene);
		std::shared_ptr<Rendurr::Scene> getActiveScene() const;

	private:
		Editurr() = default;
		~Editurr() = default;
	private:
		std::shared_ptr<Rendurr::Scene> m_pActiveScene;
	};
}
