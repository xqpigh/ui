# ui/cmake/warnings/strict.cmake

add_library(ui_project_warnings INTERFACE)

target_compile_options(
    ui_project_warnings
    INTERFACE
        -Wall
        -Wextra
        -Wpedantic
)

