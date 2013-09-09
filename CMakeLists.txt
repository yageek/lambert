cmake_minimum_required(VERSION 2.8)

project(lambert)

option(CUNIT_TEST "CUNIT_TEST" OFF)
option(DEBUG "Display itermediate values" OFF)

SET(RESOURCES_PATH ${CMAKE_INSTALL_PREFIX}/share/lambert)
configure_file(${PROJECT_SOURCE_DIR}/src/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

add_subdirectory(src)
add_subdirectory(share)

IF(CUNIT_TEST)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
	enable_testing()
	add_subdirectory(tests)
ENDIF(CUNIT_TEST)