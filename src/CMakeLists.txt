include_directories(${PROJECT_SOURCE_DIR})
add_library(lambert lambert.c ntf_rg93.c)

IF (NOT WIN32)
  INSTALL(FILES lambert.h ntf_rg93.h DESTINATION include)
  INSTALL(TARGETS lambert LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
ENDIF()
