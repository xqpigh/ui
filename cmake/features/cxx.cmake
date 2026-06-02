# ui/cmake/options/cxx26.cmake

add_library(project_features INTERFACE)

target_compile_features(project_features INTERFACE cxx_std_26)

