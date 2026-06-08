# ui/CMakeLists.txt

cmake_minimum_required(VERSION 3.26)

project(ui LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(${PROJECT_SOURCE_DIR}/cmake/features/cxx.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/options/options.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/output/output.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/warnings/strict.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies/sdl3.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies/sdl3_ttf.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dependencies/tomlplusplus.cmake)

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

