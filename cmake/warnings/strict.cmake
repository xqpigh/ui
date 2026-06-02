# ui/cmake/warnings/strict.cmake

add_library(project_warnings INTERFACE)

target_compile_options(
    project_warnings
    INTERFACE
        -Wall
        -Wextra
        -Wpedantic
)

