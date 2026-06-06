# ui/tests/window1_test/CMakeLists.txt

add_executable(window1_test window1_test.cpp)

target_link_libraries(window1_test PRIVATE ui::window1)

ui_set_output_dir(window1_test "ui")

