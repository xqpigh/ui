// ui/src/widgets/label.cpp

#include "ui/widgets/label.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

namespace ui::widgets {

Label::Label(std::string text, float x, float y, TTF_Font* font, SDL_Color text_color)
    : text_(std::move(text)), x_(x), y_(y), font_(font), text_color_(text_color) {}

void Label::set_position(float x, float y) {
    x_ = x;
    y_ = y;
}

void Label::render(SDL_Renderer* renderer) {
    //SDL_Color color {255, 255, 255, 255};

    SDL_Surface* surface = 
        TTF_RenderText_Blended(font_, text_.c_str(), text_.size(), text_color_);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FRect dst {
        x_,
        y_,
        static_cast<float>(surface->w),
        static_cast<float>(surface->h)
    };

    SDL_RenderTexture(renderer, texture, nullptr, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

}// namespace ui::widgets

