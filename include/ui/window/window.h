// ui/include/ui/window/window.h

#pragma once

#include <SDL3/SDL_video.h>

#include <string>

namespace ui::window {

class Window {
public:
    void create_window(
            const std::string &title, int width, int height, 
            int x, int y, SDL_WindowFlags flags
            );

    void create_window();

    void create_window(
            const std::string &title, int width, int height,
            SDL_WindowFlags flags
            );
};

} // namespace ui::window

