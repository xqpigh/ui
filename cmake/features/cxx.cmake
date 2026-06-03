# ui/cmake/options/cxx26.cmake

add_library(ui_project_features INTERFACE)

target_compile_features(ui_project_features INTERFACE cxx_std_26)

