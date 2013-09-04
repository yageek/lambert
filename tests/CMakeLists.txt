enable_testing()
find_package(CUnit REQUIRED)
include_directories(${CUNIT_INCLUDE_DIR})
set(LIBS ${LIBS} ${CUNIT_LIBRARY} lambert)

include_directories(. ../lib)
add_executable(test_lambert test_lambert_cunit.c)
target_link_libraries(test_lambert ${LIBS} m)
add_test(test_lambert ${CMAKE_CURRENT_BINARY_DIR}/test_lambert)
