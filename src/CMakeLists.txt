include_directories(${PROJECT_SOURCE_DIR})
add_library(lambert lambert.c ntf_rg93.c ntv2.c)
TARGET_LINK_LIBRARIES(lambert m)

IF (NOT WIN32)
  INSTALL(FILES lambert.h ntf_rg93.h config.h ntv2.h DESTINATION include/lambert)
  INSTALL(TARGETS lambert LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
ENDIF()
