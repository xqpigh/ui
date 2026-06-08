// ui/src/widgets/button.cpp

#include "ui/widgets/button.h"
#include "ui/widgets/label.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <string>
#include <utility>

namespace {
float center_text_x(const std::string& text, float x, float width, TTF_Font* font) {
    int text_w = 0;
    int text_h = 0;
    TTF_GetStringSize(font, text.c_str(), text.size(), &text_w, &text_h);

    return x + (width - static_cast<float>(text_w)) / 2.0f;
}

float center_text_y(const std::string& text, float y, float height, TTF_Font* font) {
    int text_w = 0;
    int text_h = 0;
    TTF_GetStringSize(font, text.c_str(), text.size(), &text_w, &text_h);

    return y + (height - static_cast<float>(text_h)) / 2.0f;
}

}

namespace ui::widgets {

Button::Button(std::string text, float x, float y, float width, float height, TTF_Font* font)
    : label_(text,
             center_text_x(text, x, width, font),
             center_text_y(text, y, height, font),
             font),
      x_(x), y_(y), width_(width), height_(height) {}

void Button::process_event(const SDL_Event& event) {

}

void Button::render(SDL_Renderer* renderer) {
    SDL_FRect rect {x_, y_, width_, height_};

    SDL_SetRenderDrawColor(renderer, 80, 120, 220, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderRect(renderer, &rect);

    label_.render(renderer);
}

} // namespace ui::widgets

