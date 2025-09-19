project(lab_01 LANGUAGES CXX)

add_executable(lab_01_run src/main.cpp src/function.cpp)

add_executable(lab_01_tests tests/test_cases.cpp src/function.cpp)

target_link_libraries(lab_01_tests PRIVATE gtest gtest_main)