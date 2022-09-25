cmake_minimum_required(VERSION 3.23)
project(s21_matrix)

set(CMAKE_CXX_STANDARD 14)


#include_directories(src)
add_subdirectory(src)
#add_subdirectory(test)
#add_subdirectory(Google_tests/lib)
#include_directories(Google_tests/lib/googletest/include)
#add_subdirectory(Google_tests/lib)
#
#set(HEADER_FILES
#        s21_matrix_oop.h
#        )
#
#set(SOURCE_FILES
#        src/s21_matrix_oop.cpp
#        src/tests.cpp
#        )

#add_executable(s21_matrix_cpp
#        src/s21_matrix_oop.cpp
#        src/s21_matrix_oop.h)
#        src/tests.cpp)

#add_executable(Google_Tests_run test/tests.cpp)
#
#target_link_libraries(Google_Tests_run gtest gtest_main)
add_subdirectory(Google_tests)