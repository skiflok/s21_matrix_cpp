cmake_minimum_required(VERSION 3.23)
project(s21_matrix_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(Google_tests/lib/googletest/include)
add_subdirectory(Google_tests/lib)

set(HEADER_FILES
        s21_matrix_oop.h
        )

set(SOURCE_FILES
        src/s21_matrix_oop.cpp
        src/tests.cpp
        )

add_executable(s21_matrix_cpp
        src/s21_matrix_oop.cpp
        src/s21_matrix_oop.h
        src/tests.cpp)

add_executable(Google_Tests_run src/tests.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)