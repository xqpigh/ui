// ui/src/widgets/widget.cpp

#include <SDL3/SDL_render.h>
#include <ui/widgets/widget.h>

namespace ui::widgets {

Widget::~Widget() = default;

void Widget::process_event(const SDL_Event& event) {}

void Widget::render(SDL_Renderer* renderer) {};

} // namespace ui::widget

