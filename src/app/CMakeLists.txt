# ui/src/app/CMakeLists.txt

add_library(ui_app STATIC app.cpp)

target_link_libraries(ui_app PUBLIC ui_project_features ui_project_warnings SDL3::SDL3 ui::window1)

target_include_directories(ui_app PUBLIC ${PROJECT_SOURCE_DIR}/include)

ui_set_output_dir(ui_app "ui")

add_library(ui::app ALIAS ui_app)

