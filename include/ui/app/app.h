// ui/include/ui/app/app.h

#pragma once

#include "ui/window1/window1.h"

#include <SDL3/SDL_video.h>

#include <memory>
#include <vector>

namespace ui::app {

class App {
public:
    void init();

    void run();

    window1::Window1& create_window(
            std::string title, int width, int height,
            SDL_WindowFlags flags
            );

    window1::Window1& create_window(
            std::string title, int width, int height,
            int x, int y, SDL_WindowFlags flags
            );

    void cleanup_windows();

    void shutdown();

private:
    std::vector<std::unique_ptr<window1::Window1>> windows1_;

    bool running_ = true;
};

} // namespace ui::app

