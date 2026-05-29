#pragma once

#include <Scene/Scene.hpp>
#include <memory>

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

        static std::shared_ptr<Rendurr::Scene> createScene();
        void setActiveScene(std::shared_ptr<Rendurr::Scene> pScene);
        std::shared_ptr<Rendurr::Scene> getActiveScene() const;

    private:
        Editurr() = default;
        ~Editurr() = default;

    private:
        std::shared_ptr<Rendurr::Scene> m_pActiveScene;
    };
} // namespace Editurr
