# ui/src/window/CMakeLists.txt

add_library(ui_window STATIC window.cpp)

target_link_libraries(ui_window PUBLIC project_features project_warnings)

target_include_directories(ui_window PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_output_dir(ui_window "ui")

add_library(ui::window ALIAS ui_window)

