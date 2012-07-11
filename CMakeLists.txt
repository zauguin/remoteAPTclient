ADD_DEFINITIONS(-std=c++11)
cmake_minimum_required (VERSION 2.6)
SET(JUST_PRINT OFF CACHE BOOL "Just print commands, don't execute them")
SET(PACKAGEMANAGER apt CACHE STRING "Packagmanager to use")
project (remoteAPTclient)
SET(USE_INSTALLED_FILE ON CACHE BOOL "Use a file to save the list of installed packages")
CONFIGURE_FILE(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
IF(USE_INSTALLED_FILE)
  SET(INSTALLED_SOURCE installed_file.cxx)
ELSE(USE_INSTALLED_FILE)
  SET(INSTALLED_SOURCE installed_dynamic_${PACKAGEMANAGER}.cxx installed_dynamic.cxx)
ENDIF(USE_INSTALLED_FILE)
add_executable(remoteAPTclient remoteAPTclient.cxx ${INSTALLED_SOURCE} packagemanager/common.cxx packagemanager/${PACKAGEMANAGER}.cxx)
