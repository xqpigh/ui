// ui/src/app/app.cpp

#include "ui/app/app.h"
#include "ui/config/config.h"
#include "ui/widgets/button.h"
#include "ui/widgets/label.h"
#include "ui/window1/window1.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_video.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <array>
#include <memory>

namespace ui::app {

void App::init() {
    //SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "x11");

    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
}

void App::run() {
    init();

    config::Config config {};
    
    config.load("config/config.toml");

    TTF_Font* font = TTF_OpenFont("assets/fonts/Sarasa-Regular.ttc", 16);
    TTF_Font* font96 = TTF_OpenFont("assets/fonts/Sarasa-Regular.ttc", 96);
    //TTF_Font* font128 = TTF_OpenFont("assets/fonts/Sarasa-Regular.ttc", 128);

    auto& window1 = create_window(config.window().title, 400, 300,
                                  SDL_WINDOW_BORDERLESS |
                                  SDL_WINDOW_HIGH_PIXEL_DENSITY);
    //window1.add_widget(std::make_unique<widgets::Label>(config.window().title, 
    //                                                    0, 0, font));
    SDL_SetWindowHitTest(window1.get_window(),
                         [](SDL_Window*, const SDL_Point* area,
                            void*)->SDL_HitTestResult {
                             if (area->x >= 0 && area->x <= 50 &&
                                 area->y >= 0 && area->y <= 20) {
                                 return SDL_HITTEST_DRAGGABLE;
                                 }
                             return SDL_HITTEST_NORMAL;
                         }, nullptr);

    window1.add_widget(std::make_unique<widgets::Label>(config.window().title,
                                                        5, 0, font));
    /*window1.add_widget(std::make_unique<widgets::Button>(config.window().title,
                                                         0, 0, 120, 30, font, 
                                                         [] {
                                                            SDL_Log("callback");
                                                         },
                                                         std::array<Uint8, 4>{0, 0, 0, 0},
                                                         std::array<Uint8, 4>{0, 0, 0, 0}));*/
    window1.add_widget(std::make_unique<widgets::Button>("Button 1", 50, 0,
                                                         90, 20, font, 
                                                         [] {
                                                            SDL_Log("callback");
                                                         },
                                                         std::array<Uint8, 4>{255, 255, 0, 90},
                                                         std::array<Uint8, 4>{0, 0, 0, 0}));
    window1.add_widget(std::make_unique<widgets::Label>("仙界", 200, 150, font96));

    //auto& window2 = create_window("Window 2", 400, 300, 400, 640, SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    //window2.add_widget(std::make_unique<widgets::Button>("Button 2", 50, 50, 160, 50, font));

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
    TTF_Quit();
    SDL_Quit();
}

} // namespace ui::app

