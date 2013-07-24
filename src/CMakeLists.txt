include_directories(${PROJECT_SOURCE_DIR})
add_library(lambert lambert.c)

IF (NOT WIN32)
  INSTALL(FILES lambert.h DESTINATION include)
  INSTALL(TARGETS lambert LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
ENDIF()
