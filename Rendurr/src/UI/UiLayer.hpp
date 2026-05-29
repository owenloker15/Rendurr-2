#pragma once

#include "Core/Layer.hpp"

namespace Rendurr
{
    class UiLayer : public Layer
    {
    public:
        void onAttach() override;
        void onDetach() override;

        static void startFrame();
        static void endFrame();
    };
} // namespace Rendurr
