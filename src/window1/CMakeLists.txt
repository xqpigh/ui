# ui/src/window1/CMakeLists.txt

add_library(ui_window1 STATIC window1.cpp)

target_link_libraries(ui_window1 PUBLIC ui_project_features ui_project_warnings SDL3::SDL3)

target_include_directories(ui_window1 PUBLIC ${PROJECT_SOURCE_DIR}/include)

ui_set_output_dir(ui_window1 "ui")

add_library(ui::window1 ALIAS ui_window1)

