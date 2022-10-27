cmake_minimum_required(VERSION 3.10)
project(ascii_donut_3d_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(donut_3d main.cc Canvas.cc Canvas.hpp Preload.hpp)

target_include_directories(donut_3d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
