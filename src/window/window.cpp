// ui/src/window/window.cpp

#include "ui/window/window.h"

#include <SDL3/SDL.h>

namespace ui::window {

void Window::create_window() {
    SDL_Init(SDL_INIT_VIDEO);

    /*
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Window1");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 600);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 400);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER,SDL_WINDOW_BORDERLESS);
    SDL_Window* window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    */

    SDL_Window* window = SDL_CreateWindow("Window", 600, 400, SDL_WINDOW_BORDERLESS);

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

}

