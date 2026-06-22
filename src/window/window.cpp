// ui/src/window/window.cpp

#include "ui/window/window.h"
#include "ui/widgets/widget.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <memory>
#include <string>

namespace ui::window {

void Window::run() {
    init();

    create_window();

    SDL_Event event;

    while (running_) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running_ = false;
            }

            process_event(event);
        }

        render();
    }

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::init() {
    running_ = true;
}

void Window::create_window(
        const std::string& title, int width, int height,
        int x, int y, SDL_WindowFlags flags) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER,flags);
    window_ = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    renderer_ = SDL_CreateRenderer(window_, nullptr);

    window_id_ = SDL_GetWindowID(window_);
}

void Window::create_window() {
    create_window(
            "Window", 400, 300,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOW_BORDERLESS
            );
}

void Window::create_window(
        const std::string& title, int width, int height,
        SDL_WindowFlags flags) {
    create_window(
            title.c_str(),
            width,
            height,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            flags
            );
}

void Window::add_widget(std::unique_ptr<widgets::Widget> widget) {
    widgets_.push_back(std::move(widget));
}

void Window::process_event(const SDL_Event& event) {
    // 过滤属于其他窗口的事件
    // SDL_Event 是 union,必须按事件类型访问对应的 windowID 成员
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        if (event.key.windowID != window_id_) return;
        break;
    case SDL_EVENT_MOUSE_MOTION:
        if (event.motion.windowID != window_id_) return;
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (event.button.windowID != window_id_) return;
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        if (event.wheel.windowID != window_id_) return;
        break;
    default:
        // 窗口事件通过范围判断(可能有多种子类型)
        if (event.type >= SDL_EVENT_WINDOW_FIRST &&
            event.type <= SDL_EVENT_WINDOW_LAST &&
            event.window.windowID != window_id_) {
            return;
        }
        break;
    }

    // 渲染按物理像素,鼠标事件是窗口逻辑坐标,转发前按像素密度缩放
    float density = SDL_GetWindowPixelDensity(window_);
    SDL_Event scaled = event;
    switch (scaled.type) {
        case SDL_EVENT_MOUSE_MOTION:
            scaled.motion.x *= density;
            scaled.motion.y *= density;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            scaled.button.x *= density;
            scaled.button.y *= density;
            break;
    }

    for (auto& widget : widgets_) {
        widget->process_event(scaled);
    }

    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            SDL_Log("window %d %s down",
                    window_id_, SDL_GetKeyName(event.key.key));

            if (event.key.key == SDLK_ESCAPE) {
                SDL_Log("window %d esc down", window_id_);
            }

            break;

        case SDL_EVENT_KEY_UP:
            if (event.key.key == SDLK_ESCAPE) {
                SDL_Log("window %d esc up", window_id_);
                SDL_Log("window %d hello", window_id_);
            }

            SDL_Log("window %d %s up",
                    window_id_, SDL_GetKeyName(event.key.key));
            break;

        case SDL_EVENT_MOUSE_MOTION:
            SDL_Log("window %d mouse motion x: %f y: %f",
                    window_id_, event.motion.x, event.motion.y);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            SDL_Log("window %d mouse wheel incremental x: %f y: %f pos x: %f, y: %f",
                    window_id_, event.wheel.x, event.wheel.y,
                    event.wheel.mouse_x, event.wheel.mouse_y);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_Log("window %d mouse button down left x: %f, y: %f",
                        window_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_RIGHT) {
                SDL_Log("window %d mouse button down right x: %f, y: %f",
                        window_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_X1) {
                SDL_Log("window %d mouse button down back", window_id_);
            }

            if (event.button.button == SDL_BUTTON_X2) {
                SDL_Log("window %d mouse button down forward", window_id_);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_Log("window %d mouse button up left x: %f, y: %f",
                        window_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_RIGHT) {
                SDL_Log("window %d mouse button up right x: %f, y: %f",
                        window_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_X1) {
                SDL_Log("window %d mouse button up back", window_id_);
            }

            if (event.button.button == SDL_BUTTON_X2) {
                SDL_Log("window %d mouse button up forward", window_id_);
            }
            break;

        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            if (event.window.windowID == window_id_) {

                should_close_ = true;
                SDL_Log("window %d closed", window_id_);
            }
            break;
    }
}

void Window::render() {
    begin_frame();

    draw();

    end_frame();
}

void Window::begin_frame() {
    SDL_SetRenderDrawColor(renderer_, 25, 25, 25, 255);
    SDL_RenderClear(renderer_);
}

void Window::draw() {
    int window_w = 0;
    int window_h = 0;
    // 渲染按物理像素,边框需用像素尺寸才能铺满整个画布
    SDL_GetWindowSizeInPixels(window_, &window_w, &window_h);

    SDL_FRect rect = {
        0, 0, static_cast<float>(window_w), static_cast<float>(window_h)
    };
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 55);
    SDL_RenderRect(renderer_, &rect);

    for (auto& widget : widgets_) {
        widget->render(renderer_);
    }
}

void Window::end_frame() {
    SDL_RenderPresent(renderer_);
}

void Window::destroy() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

bool Window::is_close() const {
    return should_close_;
}

SDL_Window* Window::get_window() {
    return window_;
}

} // namespace ui::window
