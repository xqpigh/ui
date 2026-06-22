// ui/src/app/app.cpp

#include "ui/app/app.h"
#include "ui/widgets/button.h"
#include "ui/widgets/label.h"
#include "ui/widgets/menu.h"
#include "ui/window1/window1.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_video.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <array>
#include <memory>

namespace ui::app {

void App::init() {
    // 优先使用原生 Wayland 驱动:XWayland(x11)不上报分数缩放,
    // 会导致高 DPI 下由合成器拉伸窗口、文字模糊
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland,x11");

    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
}

void App::run() {
    init();

    auto& window1 = create_window(
            "Title", 600, 400,
            SDL_WINDOW_BORDERLESS |
            SDL_WINDOW_HIGH_PIXEL_DENSITY
            );

    int window_width = 0;
    int window_height = 0;
    SDL_GetWindowSizeInPixels(window1.get_window(), &window_width, &window_height);

    // 方案 A:按物理像素渲染。字体和布局坐标都要乘以像素密度
    float scale = SDL_GetWindowPixelDensity(window1.get_window());

    TTF_Font* font = TTF_OpenFont(
            "assets/fonts/Sarasa-Regular.ttc", 14 * scale);
    TTF_Font* font96 = TTF_OpenFont(
            "assets/fonts/Sarasa-Regular.ttc", 96 * scale);
    int title_h = TTF_GetFontHeight(font);

    SDL_SetWindowHitTest(
            window1.get_window(),
            [](SDL_Window* win, const SDL_Point* area, void*)->SDL_HitTestResult {
                int window_w, window_h;
                SDL_GetWindowSize(win, &window_w, &window_h);
                if (area->x >= 0 && area->x <= 50 &&
                    area->y >= window_h - 20 && area->y <= window_h) {
                    return SDL_HITTEST_DRAGGABLE;
                }
                return SDL_HITTEST_NORMAL;
            },
            nullptr
            );

    window1.add_widget(
            std::make_unique<widgets::Label>(
                "Title",
                5 * scale, window_height - title_h, font,
                SDL_Color {125, 125, 125, 255}
                )
            );

    /*window1.add_widget(
            std::make_unique<widgets::Button>(
                "≡", 5, 5,20, 20, font,
                [] {
                    SDL_Log("callback menu");
                },
                SDL_Color {125, 125, 125, 255},
                std::array<Uint8, 4>{0, 0, 0, 0},
                std::array<Uint8, 4>{125, 125, 125, 255}
                )
            );*/

    auto menu = std::make_unique<widgets::Menu>(
            "≡", 5 * scale, 5 * scale, 20 * scale, 20 * scale,
            90 * scale, 20 * scale, font,
            SDL_Color {255, 255, 255, 255},
            std::array<Uint8, 4>{40, 40, 40, 40},
            std::array<Uint8, 4>{255, 255, 255, 255},
            5.0f * scale   // toggle 与第一项之间的缝隙
            );
    menu->add_item(
            "Button 1", 
            [] {
                SDL_Log("menu New");
            }
            );
    menu->add_item(
            "New1",
            [] {
                SDL_Log("menu New1");
            }
            );
    menu->add_item(
            "Quit",
            [] {
                SDL_Log("menu Quit");
            },
            90 * scale, 20 * scale,                   // 自定义宽高
            SDL_Color {255, 80, 80, 255},             // 红色文字
            std::array<Uint8, 4>{60, 0, 0, 255},      // 暗红背景
            std::array<Uint8, 4>{255, 80, 80, 255}    // 红色边框
            );
    window1.add_widget(std::move(menu));

    window1.add_widget(
            std::make_unique<widgets::Button>(
                "Button 1", 30 * scale, 5 * scale, 90 * scale, 20 * scale, font,
                [] {
                    SDL_Log("callback button 1");
                },
                SDL_Color {125, 125, 125, 255},
                std::array<Uint8, 4>{0, 0, 0, 0},
                std::array<Uint8, 4>{125, 125, 125, 255}
                )
            );

    window1.add_widget(
            std::make_unique<widgets::Button>(
                "Button 2", 125 * scale, 5 * scale, 90 * scale, 20 * scale, font,
                [] {
                    SDL_Log("callback button 2");
                },
                SDL_Color {125, 125, 125, 255},
                std::array<Uint8, 4>{0, 0, 0, 0},
                std::array<Uint8, 4>{125, 125, 125, 255}
                )
            );

    window1.add_widget(
            std::make_unique<widgets::Label>(
                "仙界", 200 * scale, 150 * scale, font96
                )
            );

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

window1::Window1& App::create_window(
        std::string title, int width, int height, 
        SDL_WindowFlags flags) {
    return create_window(
            title, width, height,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            flags
            );
}

window1::Window1& App::create_window(
        std::string title, int width, int height,
        int x, int y, SDL_WindowFlags flags) {
    auto window = std::make_unique<window1::Window1>();

    window->create_window(title, width, height, x, y, flags);

    windows1_.push_back(std::move(window));

    return *windows1_.back();
}

void App::cleanup_windows() {
    windows1_.erase(
            std::remove_if(
                windows1_.begin(),
                windows1_.end(),
                [](auto& w) {
                    if (w->is_close()) {
                        w->destroy();
                        return true;
                    }
                return false;
                }
                ),
            windows1_.end()
            );
}

void App::shutdown() {
    TTF_Quit();
    SDL_Quit();
}

} // namespace ui::app

