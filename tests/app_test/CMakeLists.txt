# ui/tests/app_test/CMakeLists.txt

add_executable(app_test app_test.cpp)

target_link_libraries(app_test PRIVATE ui::app)

ui_set_output_dir(app_test "ui")

