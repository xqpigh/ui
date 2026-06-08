// ui/include/ui/widgets/label.h

#pragma once

#include "ui/widgets/widget.h"

#include <SDL3_ttf/SDL_ttf.h>

#include <string>

namespace ui::widgets {

class Label : public Widget {
public:
    Label(std::string text, float x, float y, TTF_Font* font);

    void set_position(float x, float y);

    void render(SDL_Renderer* renderer) override;

private:
    std::string text_;
    float x_;
    float y_;
    TTF_Font* font_;
};

} // namespace ui::widgets

