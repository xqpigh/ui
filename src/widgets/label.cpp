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

Label::~Label() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
    }
}

void Label::set_position(float x, float y) {
    x_ = x;
    y_ = y;
}

void Label::render(SDL_Renderer* renderer) {
    if (!texture_) {
        SDL_Surface* surface =
            TTF_RenderText_Blended(font_, text_.c_str(), text_.size(), text_color_);

        texture_ = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_DestroySurface(surface);
    }

    float tex_w = 0;
    float tex_h = 0;
    SDL_GetTextureSize(texture_, &tex_w, &tex_h);

    SDL_FRect dst {
        x_,
        y_,
        tex_w,
        tex_h
    };

    SDL_RenderTexture(renderer, texture_, nullptr, &dst);
}

}// namespace ui::widgets
