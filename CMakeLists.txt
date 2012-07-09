ADD_DEFINITIONS(-std=c++11)
cmake_minimum_required (VERSION 2.6)
project (remoteAPTclient)
CONFIGURE_FILE(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")
OPTION(USE_INSTALLED_FILE "Use a file to save the list of installed packages" ON)
IF(USE_INSTALLED_FILE)
  SET(INSTALLED_SOURCE installed_file.cxx)
ELSE(USE_INSTALLED_FILE)
  SET(INSTALLED_SOURCE installed_dynamic.cxx)
ENDIF(USE_INSTALLED_FILE)
add_executable(remoteAPTclient remoteAPTclient.cxx ${INSTALLED_SOURCE})
