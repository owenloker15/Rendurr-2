#pragma once
#include "Core/Window.h"

namespace Editurr
{
    void ui_init(Rendurr::Window& window);
    void ui_shutdown();

    void ui_frame_begin();
    void ui_frame_end();
} // namespace Editurr