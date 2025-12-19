cmake_minimum_required(VERSION 4.0)

project(elink)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(test)
