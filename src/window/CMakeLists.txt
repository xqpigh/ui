# ui/src/window/CMakeLists.txt

add_library(ui_window STATIC window.cpp)

target_link_libraries(
    ui_window 
    PUBLIC 
        ui_project_features 
        ui_project_warnings 
        SDL3::SDL3
    )

target_include_directories(ui_window PUBLIC ${PROJECT_SOURCE_DIR}/include)

ui_set_output_dir(ui_window "ui")

add_library(ui::window ALIAS ui_window)

