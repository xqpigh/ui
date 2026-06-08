// ui/include/ui/widgets/button.h

#pragma once

#include "ui/widgets/label.h"
#include "ui/widgets/widget.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace ui::widgets {

class Button : public Widget {
public:
    Button(std::string test, float x, float y, float width, float height, TTF_Font* font);

    void process_event(const SDL_Event& event) override;

    void render(SDL_Renderer* renderer) override;

private:
    Label label_;
    float x_;
    float y_;
    float width_;
    float height_;
};

} // namespace ui::widgets

