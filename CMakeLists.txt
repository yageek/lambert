cmake_minimum_required(VERSION 2.8)

project(lambert)
add_subdirectory(src)

option(CUNIT_TEST "CUNIT_TEST" OFF)

IF(CUNIT_TEST)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
	enable_testing()
	add_subdirectory(tests)
ENDIF(CUNIT_TEST)