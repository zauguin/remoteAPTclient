ADD_DEFINITIONS(-std=c++11)
SET(USE_SHARED ON CACHE BOOL "Use shared and not static libs")
IF(USE_SHARED)
  SET(shared SHARED)
ELSE(USE_SHARED)
  SET(shared STATIC)
ENDIF(USE_SHARED)
cmake_minimum_required (VERSION 2.6)
SET(JUST_PRINT OFF CACHE BOOL "Just print commands, don't execute them")
SET(PACKAGEMANAGER apt CACHE STRING "Packagmanager to use")
SET(HOST localhost CACHE STRING "URI of the server")
SET(PORT 8080 CACHE STRING "Port on the server")
mark_as_advanced(PORT)
project (remoteAPTclient)
SET(USE_DYNAMIC_INSTALLED_LIST OFF CACHE BOOL "Use a file to save the list of installed packages")
CONFIGURE_FILE(
  "${PROJECT_SOURCE_DIR}/remoteAPTclient.sh.in"
  "${PROJECT_BINARY_DIR}/remoteAPTclient"
)
INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/remoteAPTclient DESTINATION bin)
CONFIGURE_FILE(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
IF(USE_DYNAMIC_INSTALLED_LIST)
  SET(INSTALLED_SOURCE installed_dynamic_${PACKAGEMANAGER}.cxx installed_dynamic.cxx)
ELSE(USE_DYNAMIC_INSTALLED_LIST)
  SET(INSTALLED_SOURCE installed_file.cxx)
ENDIF(USE_DYNAMIC_INSTALLED_LIST)
add_library(remoteAPTpm ${shared} packagemanager/common.cxx packagemanager/${PACKAGEMANAGER}.cxx ${INSTALLED_SOURCE})
add_executable(remoteAPTclient.bin remoteAPTclient.cxx)
target_link_libraries(remoteAPTclient.bin remoteAPTpm)
INSTALL(TARGETS remoteAPTclient.bin remoteAPTpm RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
