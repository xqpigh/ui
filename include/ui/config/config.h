// ui/include/ui/config/config.h

#pragma once

#include <string>

namespace ui::config {

struct WindowConfig {
    std::string title;
};

class Config {
public:
    bool load(const std::string& config_filepath);

    const WindowConfig& window() const;

private:
    WindowConfig window_;
};

} // namespace ui::config

