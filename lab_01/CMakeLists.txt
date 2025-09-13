add_executable(lab_01_run src/main.cpp src/function.cpp)

enable_testing()

FetchContent_MakeAvailable(googletest)

add_executable(lab_01_tests tests/test_cases.cpp src/function.cpp)

target_include_directories(lab_01_tests PRIVATE ../src)

target_link_libraries(lab_01_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab_01_tests)