cmake_minimum_required(VERSION 3.24)
project(PROI_23L_101_Apteka)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/Catch2)

add_executable(my_tests  tests/test.cpp)
target_link_libraries(my_tests PRIVATE Catch2::Catch2WithMain)
add_executable(PROI_23L_101_Apteka main.cpp)
