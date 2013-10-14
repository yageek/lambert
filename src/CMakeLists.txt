include_directories(${PROJECT_SOURCE_DIR})
add_library(lambert lambert.c rgf93.c)
TARGET_LINK_LIBRARIES(lambert m)

IF (NOT WIN32)
  INSTALL(FILES lambert.h config.h rgf93.h DESTINATION include/lambert)
  INSTALL(TARGETS lambert LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
ENDIF()
