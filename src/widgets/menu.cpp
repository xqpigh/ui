// ui/src/widgets/menu.cpp

#include "ui/widgets/menu.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>
#include <optional>
#include <string>
#include <utility>

namespace ui::widgets {

Menu::Menu(
        std::string title,
        float x, float y,
        float toggle_width, float toggle_height,
        float item_width, float item_height,
        TTF_Font* font, SDL_Color text_color,
        std::array<Uint8, 4> bg_color,
        std::array<Uint8, 4> border_color,
        float gap
        )
    : x_(x), y_(y), toggle_height_(toggle_height),
    item_width_(item_width), item_height_(item_height), gap_(gap),
    font_(font), text_color_(text_color), bg_color_(bg_color),
    border_color_(border_color),
    toggle_(
            std::move(title), x, y, toggle_width, toggle_height, font,
            [this] { open_ = !open_; },   // 点击翻转展开状态
            text_color, bg_color, border_color
            ) {}

void Menu::add_item(
        std::string text, Callback callback,
        std::optional<float> width,
        std::optional<float> height,
        std::optional<SDL_Color> text_color,
        std::optional<std::array<Uint8, 4>> bg_color,
        std::optional<std::array<Uint8, 4>> border_color) {
    // 未指定的参数回退到 Menu 默认值
    float w = width.value_or(item_width_);
    float h = height.value_or(item_height_);

    // 菜单项从 toggle 底部加缝隙开始,按各项实际高度累计堆叠
    float item_y = y_ + toggle_height_ + gap_ + items_height_;

    items_.emplace_back(
            std::move(text), x_, item_y, w, h,
            font_, std::move(callback),
            text_color.value_or(text_color_),
            bg_color.value_or(bg_color_),
            border_color.value_or(border_color_)
            );

    items_height_ += h;
}

void Menu::process_event(const SDL_Event& event) {
    toggle_.process_event(event);   // toggle 永远响应

    if (open_) {
        for (auto& item : items_) {
            item.process_event(event);
        }
    }
}

void Menu::render(SDL_Renderer* renderer) {
    toggle_.render(renderer);       // toggle 永远显示

    if (open_) {
        for (auto& item : items_) {
            item.render(renderer);
        }
    }
}

} // namespace ui::widgets
