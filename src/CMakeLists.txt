
############################
## setting up source code ##
############################

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${TEMPEST_INCLUDE_DIR}
  ${ATHENAPP_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}
  )

file(GLOB _src_harp
  absorbers/absorber.cpp
  crossdisk/cross_disk_base.cpp
  crossdisk/kinetics7_cross_disk.cpp
  )

add_library(harp STATIC ${_src_harp})
