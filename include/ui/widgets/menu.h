// ui/include/ui/widgets/menu.h

#pragma once

#include "ui/widgets/button.h"
#include "ui/widgets/widget.h"

#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <array>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace ui::widgets {

class Menu : public Widget {
public:
    using Callback = std::function<void()>;

    Menu(
            std::string title,
            float x, float y,
            float toggle_width, float toggle_height,
            float item_width, float item_height,
            TTF_Font* font, SDL_Color text_color = {255, 255, 255, 255},
            std::array<Uint8, 4> bg_color = {40, 40, 40, 40},
            std::array<Uint8, 4> border_color = {255, 255, 255, 255},
            float gap = 0.0f   // toggle 与第一个菜单项之间的缝隙
        );

    // toggle 回调捕获 this,禁止拷贝/移动以防 this 失效
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    // 各参数留空(std::nullopt)时回退到 Menu 的默认尺寸/颜色
    void add_item(
            std::string text, Callback callback,
            std::optional<float> width = std::nullopt,
            std::optional<float> height = std::nullopt,
            std::optional<SDL_Color> text_color = std::nullopt,
            std::optional<std::array<Uint8, 4>> bg_color = std::nullopt,
            std::optional<std::array<Uint8, 4>> border_color = std::nullopt
            );

    void process_event(const SDL_Event& event) override;

    void render(SDL_Renderer* renderer) override;

private:
    float x_;
    float y_;
    float toggle_height_;
    float item_width_;
    float item_height_;
    float gap_;                   // toggle 与第一个菜单项之间的缝隙
    TTF_Font* font_;
    SDL_Color text_color_;
    std::array<Uint8, 4> bg_color_;
    std::array<Uint8, 4> border_color_;

    Button toggle_;            // 标题按钮,点击展开/收起
    std::vector<Button> items_;
    float items_height_ = 0.0f;   // 已有菜单项累计高度,用于堆叠布局
    bool open_ = false;
};

}// namespace ui::widgets

