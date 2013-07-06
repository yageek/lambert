cmake_minimum_required(VERSION 2.8)

project(lambert)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
enable_testing()
add_subdirectory(lib)
add_subdirectory(tests)
