# ui/CMakeLists.txt

cmake_minimum_required(VERSION 3.26)

project(Ui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(features/cxx)
include(options/options)
include(output/output)
include(warnings/strict)
include(dependencies/sdl3)

add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

