# ui/src/widgets/CMakeLists.txt

add_library(ui_widgets STATIC widget.cpp button.cpp label.cpp)

target_link_libraries(ui_widgets PUBLIC ui_project_features ui_project_warnings SDL3::SDL3 SDL3_ttf::SDL3_ttf)

target_include_directories(ui_widgets PUBLIC ${PROJECT_SOURCE_DIR}/include)

ui_set_output_dir(ui_widgets "ui")

add_library(ui::widgets ALIAS ui_widgets)

