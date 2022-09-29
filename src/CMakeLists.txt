
############################
## setting up source code ##
############################

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}
  )

file(GLOB _src_harp
  cross_disk_base.cpp
  kinetics7_cross_disk.cpp
  )

add_library(harp STATIC ${_src_harp})
