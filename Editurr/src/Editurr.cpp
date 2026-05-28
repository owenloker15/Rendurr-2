#include "Editurr.hpp"

namespace Editurr
{
	Editurr& Editurr::getInstance()
	{
		static Editurr instance;
		return instance;
	}

	Rendurr::Scene Editurr::createScene()
	{
		return Rendurr::Scene{};
	}

	void Editurr::setActiveScene(Rendurr::Scene scene)
	{
		m_pActiveScene = std::make_shared<Rendurr::Scene>(std::move(scene));
	}

	std::shared_ptr<Rendurr::Scene> Editurr::getActiveScene() const
	{
		return m_pActiveScene;
	}
}
