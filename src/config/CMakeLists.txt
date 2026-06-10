# ui/src/config/CMakeLists.txt

add_library(ui_config STATIC config.cpp)

target_link_libraries(
    ui_config 
    PUBLIC 
        ui_project_features 
        ui_project_warnings 
        tomlplusplus::tomlplusplus 
        SDL3::SDL3
    )

target_include_directories(ui_config PUBLIC ${PROJECT_SOURCE_DIR}/include)

ui_set_output_dir(ui_config "ui")

add_library(ui::config ALIAS ui_config)


