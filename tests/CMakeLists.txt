add_executable(test_basic test_basic.cpp)
target_link_libraries(test_basic PRIVATE rippercasted::rippercasted)

# Register with CTest
add_test(NAME rippercasted_test_basic COMMAND test_basic)
