####################
## set up project ##
####################

cmake_minimum_required(VERSION 3.18)

project(
  harp2
  VERSION 0.0.1
  LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 14)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

## load all macros
#
file(GLOB _macro_files "cmake/macro_*.cmake")
#message(STATUS "Include ${CMAKE_SOURCE_DIR}/cmake/setup_external_macros.cmake")
#include(${CMAKE_SOURCE_DIR}/cmake/setup_external_macros.cmake)
foreach(_file ${_macro_files})
  message(STATUS "Include ${_file}")
  include(${_file})
endforeach()

#################################################
## check for the existence of optional folders ##
#################################################

if (EXISTS ${CMAKE_SOURCE_DIR}/external/CMakeLists.txt)
  set(HAVE_EXTERNAL_DIRECTORY TRUE)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/doc/CMakeLists.txt)
  set(HAVE_DOC_DIRECTORY TRUE)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt)
  set(HAVE_TESTS_DIRECTORY TRUE)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/examples/CMakeLists.txt)
  set(HAVE_EXAMPLES_DIRECTORY TRUE)
endif()

## set up project paths
#
#set(PACKAGE_ABSDIR "$ENV{HOME}/opt")
set(EXECUTABLE_RELDIR "bin")
set(LIBRARY_RELDIR "lib${LIB_SUFFIX}")

# set EIGEN3_INCLUDE_DIR
find_package(Eigen3 3.3 REQUIRED)
find_package(NetCDF REQUIRED)

# set up model parameters
message(STATUS "Include ${CMAKE_SOURCE_DIR}/cmake/setup_configure.cmake")
include(${CMAKE_SOURCE_DIR}/cmake/setup_configure.cmake)
configure_file(configure.hpp.in configure.hpp @ONLY)

##################################
## compilation and installation ##
##################################

if (HAVE_EXTERNAL_DIRECTORY)
  add_subdirectory(external)
endif()

add_subdirectory(src)

if (HAVE_TESTS_DIRECTORY)
  add_subdirectory(tests)
endif()

if (HAVE_EXAMPLES_DIRECTORY)
  add_subdirectory(examples)
endif()

if (HAVE_DOC_DIRECTORY)
  add_subdirectory(doc)
endif()
