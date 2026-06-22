// ui/include/ui/app/app.h

#pragma once

#include "ui/window/window.h"

#include <SDL3/SDL_video.h>

#include <memory>
#include <vector>

namespace ui::app {

class App {
public:
    void init();

    void run();

    window::Window& create_window(
            std::string title, int width, int height,
            SDL_WindowFlags flags
            );

    window::Window& create_window(
            std::string title, int width, int height,
            int x, int y, SDL_WindowFlags flags
            );

    void cleanup_windows();

    void shutdown();

private:
    std::vector<std::unique_ptr<window::Window>> windows_;

    bool running_ = true;
};

} // namespace ui::app
