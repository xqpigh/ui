// ui/include/ui/window1/window1.h

#pragma once

#include "ui/widgets/widget.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include <memory>
#include <string>
#include <vector>

namespace ui::window1 {

class Window1 {
public:
    void run();

    void init();

    void create_window(
            const std::string &title, int width, int height,
            int x, int y, SDL_WindowFlags flags
            );

    void create_window();

    void create_window(
            const std::string &title, int width, int height,
            SDL_WindowFlags flags);

    void add_widget(std::unique_ptr<widgets::Widget> widget);

    void process_event(const SDL_Event &event);

    void render();

    void begin_frame();

    void draw();

    void end_frame();

    void destroy();

    bool is_close() const;

    SDL_Window* get_window();

private:
    bool running_ = true;

    bool should_close_ = false;

    SDL_Window *window1_;

    std::vector<std::unique_ptr<widgets::Widget>> widgets_;

    SDL_Renderer *renderer_;

    Uint32 window1_id_;
};

} // namespace ui::window1

