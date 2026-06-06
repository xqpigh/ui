// ui/src/app/app.cpp

#include "ui/app/app.h"
#include "ui/window1/window1.h"

#include <SDL3/SDL_events.h>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <algorithm>
#include <memory>

namespace ui::app {

void App::init() {
    SDL_Init(SDL_INIT_VIDEO);
}

void App::run() {
    init();

    create_window("Window 1", 400, 300, 0);
    create_window("Window 2", 400, 300, 0);

    SDL_Event event;

    while (running_) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running_ = false;
            }

            for (auto& w : windows1_) {
                w->process_event(event);
            }
        }

        for (auto& w: windows1_) {
            w->render();
        }

        cleanup_windows();
    }

    shutdown();
}

window1::Window1& App::create_window(std::string title, int width, int height,
                                     SDL_WindowFlags flags) {
    return create_window(title, width, height, SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED,
                                               flags);
}

window1::Window1& App::create_window(std::string title, int width, int height,
                                     int x, int y, SDL_WindowFlags flags) {
    auto window = std::make_unique<window1::Window1>();

    window->create_window(title, width, height, x, y, flags);

    windows1_.push_back(std::move(window));

    return *windows1_.back();
}

void App::cleanup_windows() {
    windows1_.erase(std::remove_if(windows1_.begin(),
                                   windows1_.end(),
                                   [](auto& w) {
                                       if (w->is_close()) {
                                       w->destroy();
                                       return true;
                                       }
                                   return false;
                                   }),
                    windows1_.end());
}

void App::shutdown() {
    SDL_Quit();
}

}

