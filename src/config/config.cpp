// ui/src/config/config.cpp

#include "ui/config/config.h"
#include <toml++/impl/parse_error.hpp>
#include <toml++/impl/parser.hpp>
#include <toml++/toml.hpp>

#include <string>

namespace ui::config {

bool Config::load(const std::string& config_filepath) {
    try {
        auto toml = toml::parse_file(config_filepath);

        window_.title = 
            toml["window"]["title"].value_or("window 1 c");

        return true;
    } catch (const toml::parse_error&) {
        return false;
    }
}

const WindowConfig& Config::window() const {
    return window_;
}

} // namespace ui::config

