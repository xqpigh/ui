// ui/tests/window_test/window_test.cpp

#include "ui/window/window.h"

#include <print>

int main() {
    ui::window::Window window{};

    std::string window_greet = window.get_greet();
    std::println("{} From ui/tests/window_test/window_test.cpp.", window_greet);

    return 0;
}

