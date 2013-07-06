enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} lambert)

include_directories(. ../lib)
add_executable(test_lambert test_lambert.c)
target_link_libraries(test_lambert ${LIBS})
add_test(test_lambert ${CMAKE_CURRENT_BINARY_DIR}/test_lambert)
