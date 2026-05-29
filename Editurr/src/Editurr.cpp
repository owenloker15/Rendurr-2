#include "Editurr.hpp"

namespace Editurr
{
    Editurr& Editurr::getInstance()
    {
        static Editurr instance;
        return instance;
    }

    std::shared_ptr<Rendurr::Scene> Editurr::createScene()
    {
        return std::make_shared<Rendurr::Scene>();
    }

    void Editurr::setActiveScene(std::shared_ptr<Rendurr::Scene> pScene)
    {
        m_pActiveScene = pScene;
    }

    std::shared_ptr<Rendurr::Scene> Editurr::getActiveScene() const
    {
        return m_pActiveScene;
    }
} // namespace Editurr
