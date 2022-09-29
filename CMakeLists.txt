#####################
## setting up harp ##
#####################

cmake_minimum_required(VERSION 3.10)

project(
  harp
  VERSION 0.0.1
  LANGUAGES CXX
  )

set(CMAKE_MODULE_PATH "../")
set(CMAKE_CXX_STANDARD 11)

# set up project paths
set(PACKAGE_ABSDIR "$ENV{HOME}/opt")
set(EXECUTABLE_RELDIR "bin")
set(LIBRARY_RELDIR "lib${LIB_SUFFIX}")
set(EXTERNAL_ABSDIR "${CMAKE_SOURCE_DIR}/../")
set(Eigen3_DIR "${PACKAGE_ABSDIR}/share/eigen3/cmake")
message(STATUS ${Eigen3_DIR})

# set EIGEN3_INCLUDE_DIR
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# set up model parameters
set(Real float)
set(CrossDiskStatusBits 6)
set(MaxReactants 5)
configure_file(configure.hpp.in configure.hpp @ONLY)

add_subdirectory(src)
add_subdirectory(tests)
