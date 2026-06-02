# ui/tests/window_test/CMakeLists.txt

add_executable(window_test window_test.cpp)

target_link_libraries(window_test PRIVATE ui::window)

set_output_dir(window_test "ui")

