// ui/include/ui/widgets/button.h

#pragma once

#include "ui/widgets/label.h"
#include "ui/widgets/widget.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <functional>
#include <string>

namespace ui::widgets {

class Button : public Widget {
public:
    using Callback = std::function<void()>;

    Button(
            std::string text, float x, float y, float width, float height,
            TTF_Font* font, Callback callback,
            SDL_Color texxt_color = {255, 255, 255, 255},
            std::array<Uint8, 4> bg_color = {80, 120, 220, 255},
            std::array<Uint8, 4> border_color = {255, 255, 255, 255}
            );

    void process_event(const SDL_Event& event) override;

    void render(SDL_Renderer* renderer) override;

    bool contains(float mouse_x, float mouse_y) const;

private:
    Label label_;
    float x_;
    float y_;
    float width_;
    float height_;
    Callback callback_;
    SDL_Color text_color_;
    std::array<Uint8, 4> bg_color_;
    std::array<Uint8, 4> border_color_;

    bool hovered_ = false;
    bool pressed_ = false;
};

} // namespace ui::widgets

