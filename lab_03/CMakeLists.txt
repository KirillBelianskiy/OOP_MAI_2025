project(lab_03 LANGUAGES CXX)

add_executable(lab_03_run src/main.cpp src/classes.cpp)

add_executable(lab_03_tests tests/test_cases.cpp src/classes.cpp)

target_link_libraries(lab_03_tests PRIVATE gtest gtest_main)