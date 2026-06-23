// ui/include/ui/widgets/widget.h

#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

namespace ui::widgets {

class Widget {
public:
    virtual ~Widget();

    virtual void process_event(const SDL_Event& event);

    virtual void render(SDL_Renderer* renderer) = 0;

    void set_visible(bool v) { visible_ = v; }
    bool is_visible() const { return visible_; }

private:
    bool visible_ = true;
};

} // namespace ui::widgets

