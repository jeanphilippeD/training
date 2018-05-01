cmake_minimum_required (VERSION 3.1)
project (test_feature)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(test_feature catch.cpp test.cpp)

