cmake_minimum_required (VERSION 3.1)
project (cpp11resource)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp11resource catch.cpp non_resource.cpp resource_regular.cpp resource_semi_regular.cpp resource_movable.cpp resource_non_movable.cpp)

