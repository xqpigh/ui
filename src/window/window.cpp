// ui/src/window/window.cpp

#include "ui/window/window.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include <string>

namespace ui::window {

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
    SDL_Window* window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);

    //SDL_Window* window = SDL_CreateWindow(title.c_str(), width, height, flags);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Event event;
    bool running = true;

    while (running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_ESCAPE) {
                        SDL_Log("esc down");
                    }

                    SDL_Log("%s down", SDL_GetKeyName(event.key.key));
                    break;

                case SDL_EVENT_KEY_UP:
                    if (event.key.key == SDLK_ESCAPE) {
                        SDL_Log("esc up");
                        SDL_Log("hello");
                    }

                    SDL_Log("%s up", SDL_GetKeyName(event.key.key));
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    SDL_Log("mouse motion x: %f y: %f", event.motion.x, event.motion.y);
                    break;

                case SDL_EVENT_MOUSE_WHEEL:
                    SDL_Log("mouse wheel incremental x: %f y: %f pos x: %f, y: %f",
                            event.wheel.x, event.wheel.y, event.wheel.mouse_x, event.wheel.mouse_y);
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Log("mouse button down left x: %f, y: %f",
                                event.button.x, event.button.y);
                    }

                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        SDL_Log("mouse button down right x: %f, y: %f",
                                event.button.x, event.button.y);
                    }

                    if (event.button.button == SDL_BUTTON_X1) {
                        SDL_Log("mouse button down back");
                    }

                    if (event.button.button == SDL_BUTTON_X2) {
                        SDL_Log("mouse button down forward");
                    }
                    break;

                case SDL_EVENT_MOUSE_BUTTON_UP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Log("mouse button up left x: %f, y: %f",
                                event.button.x, event.button.y);
                    }

                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        SDL_Log("mouse button up right x: %f, y: %f",
                                event.button.x, event.button.y);
                    }


                    if (event.button.button == SDL_BUTTON_X1) {
                        SDL_Log("mouse button up back");
                    }

                    if (event.button.button == SDL_BUTTON_X2) {
                        SDL_Log("mouse button up forward");
                    }
                    break;

                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::create_window() {
    create_window(
            "Window", 800, 600, 
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

} // namespace ui::window

