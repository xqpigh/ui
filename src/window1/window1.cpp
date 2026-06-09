// ui/src/window1/window1.cpp

#include "ui/window1/window1.h"
#include "ui/widgets/widget.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include <memory>
#include <string>

namespace ui::window1 {

void Window1::run() {
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
    SDL_DestroyWindow(window1_);
    SDL_Quit();
}

void Window1::init() {
    running_ = true;
}

void Window1::create_window(const std::string& title,
                            int width,
                            int height,
                            int x,
                            int y,
                            SDL_WindowFlags flags) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER,flags);
    window1_ = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    renderer_ = SDL_CreateRenderer(window1_, nullptr);
    //SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_STRETCH);

    window1_id_ = SDL_GetWindowID(window1_);
}

void Window1::create_window() {
    create_window("Window", 400, 300, 
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOW_BORDERLESS);
}

void Window1::create_window(const std::string& title,
                            int width,
                            int height,
                            SDL_WindowFlags flags) {
    create_window(title.c_str(),
                  width,
                  height,
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  flags);
}

void Window1::add_widget(std::unique_ptr<widgets::Widget> widget) {
    widgets_.push_back(std::move(widget));
}

void Window1::process_event(const SDL_Event& event) {
    if (event.type >= SDL_EVENT_WINDOW_FIRST &&
        event.type <= SDL_EVENT_WINDOW_LAST) {
        if (event.window.windowID != window1_id_) {
            return;
        }
    }

    if (event.window.windowID != window1_id_) {
        return;
    }

    for (auto& widget : widgets_) {
        widget->process_event(event);
    }

    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            SDL_Log("window %d %s down", window1_id_, SDL_GetKeyName(event.key.key));

            if (event.key.key == SDLK_ESCAPE) {
                SDL_Log("window %d esc down", window1_id_);
            }
            
            break;

        case SDL_EVENT_KEY_UP:
            if (event.key.key == SDLK_ESCAPE) {
                SDL_Log("window %d esc up", window1_id_);
                SDL_Log("window %d hello", window1_id_);
            }

            SDL_Log("window %d %s up", window1_id_, SDL_GetKeyName(event.key.key));
            break;

        case SDL_EVENT_MOUSE_MOTION:
            SDL_Log("window %d mouse motion x: %f y: %f", window1_id_, event.motion.x, event.motion.y);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            SDL_Log("window %d mouse wheel incremental x: %f y: %f pos x: %f, y: %f",
                    window1_id_, event.wheel.x, event.wheel.y, event.wheel.mouse_x, event.wheel.mouse_y);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_Log("window %d mouse button down left x: %f, y: %f",
                        window1_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_RIGHT) {
                SDL_Log("window %d mouse button down right x: %f, y: %f",
                        window1_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_X1) {
                SDL_Log("window %d mouse button down back", window1_id_);
            }

            if (event.button.button == SDL_BUTTON_X2) {
                SDL_Log("window %d mouse button down forward", window1_id_);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                SDL_Log("window %d mouse button up left x: %f, y: %f",
                        window1_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_RIGHT) {
                SDL_Log("window %d mouse button up right x: %f, y: %f",
                        window1_id_, event.button.x, event.button.y);
            }

            if (event.button.button == SDL_BUTTON_X1) {
                SDL_Log("window %d mouse button up back", window1_id_);
            }

            if (event.button.button == SDL_BUTTON_X2) {
                SDL_Log("window %d mouse button up forward", window1_id_);
            }
            break;

        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            if (event.window.windowID == window1_id_) {

                should_close_ = true;
                SDL_Log("window %d closed", window1_id_);
            }
            break;
    }
}

void Window1::render() {
    begin_frame();

    draw();

    end_frame();
}

void Window1::begin_frame() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Window1::draw() {
    for (auto& widget : widgets_) {
        widget->render(renderer_);
    }
}

void Window1::end_frame() {
    SDL_RenderPresent(renderer_);
}

void Window1::destroy() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window1_) {
        SDL_DestroyWindow(window1_);
        window1_ = nullptr;
    }
}

bool Window1::is_close() const {
    return should_close_;
}

SDL_Window* Window1::get_window() {
    return window1_;
}

} // namespace ui::window1

