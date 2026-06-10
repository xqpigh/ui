// ui/src/widgets/button.cpp

#include "ui/widgets/button.h"
#include "ui/widgets/label.h"

#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <array>
#include <iterator>
#include <string>

namespace {
float center_text_x(
        const std::string& text, float x, float width, TTF_Font* font) {
    int text_w = 0;
    int text_h = 0;
    TTF_GetStringSize(font, text.c_str(), text.size(), &text_w, &text_h);

    return x + (width - static_cast<float>(text_w)) / 2.0f;
}

float center_text_y(
        const std::string& text, float y, float height, TTF_Font* font) {
    int text_w = 0;
    int text_h = 0;
    TTF_GetStringSize(font, text.c_str(), text.size(), &text_w, &text_h);

    return y + (height - static_cast<float>(text_h)) / 2.0f;
}

}

namespace ui::widgets {

Button::Button(
        std::string text, float x, float y, float width, float height,
        TTF_Font* font, Callback callback,
        SDL_Color text_color,
        std::array<Uint8, 4> bg_color,
        std::array<Uint8, 4> border_color)
    : label_(
            text,
            center_text_x(text, x, width, font),
            center_text_y(text, y, height, font),
            font,
            text_color
            ),
      x_(x), y_(y), width_(width), height_(height),
      callback_(std::move(callback)),
      bg_color_(bg_color), border_color_(border_color) {}

void Button::process_event(const SDL_Event& event) {
    /*if (event.type != SDL_EVENT_MOUSE_BUTTON_DOWN) {
        return;
    }

    float mouse_x = event.button.x;
    float mouse_y = event.button.y;

    bool inside = mouse_x >= x_ && mouse_x <= x_ + width_ &&
                  mouse_y >= y_ && mouse_y <= y_ + height_;

    if (inside && callback_) {
        callback_();
    }*/
    switch (event.type) {
    case SDL_EVENT_MOUSE_MOTION:
        hovered_ = contains(event.motion.x, event.motion.y);
        if (!hovered_) {
            pressed_ = false;
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event.button.button == SDL_BUTTON_LEFT &&
            contains(event.motion.x, event.motion.y)) {
            pressed_ = true;
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (event.button.button == SDL_BUTTON_LEFT) {
            bool inside = contains(event.motion.x, event.motion.y);

            if (pressed_ && inside && callback_) {
                callback_();
            }

            pressed_ = false;
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_FRect rect {x_, y_, width_, height_};

    auto color = bg_color_;
    
    if (pressed_) {
        color = {80, 80, 80, 255};
    } else if (hovered_) {
        color = {55, 55, 55, 255};
    }

    SDL_SetRenderDrawColor(
            renderer, color[0], color[1], 
            color[2], color[3]
            );
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(
            renderer, border_color_[0], border_color_[1],
            border_color_[2], border_color_[3]
            );
    SDL_RenderRect(renderer, &rect);

    label_.render(renderer);
}

bool Button::contains(float mouse_x, float mouse_y) const {
    return mouse_x >= x_ && mouse_x <= x_ + width_ &&
           mouse_y >= y_ && mouse_y <= y_ + height_;
}

} // namespace ui::widgets

