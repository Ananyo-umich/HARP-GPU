###############################
## set up external libraries ##
###############################

## extract cdisort library
#
if (NOT EXISTS cdisort213/CMakeLists.txt)
  message(STATUS "Extracting cdisort2.3.1 ...")
  file(ARCHIVE_EXTRACT 
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cdisort2.1.3-cli.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(cdisort213)

## extract tempest library
#
if (NOT EXISTS tempest/CMakeLists.txt)
  message(STATUS "Extracting tempest ...")
  file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/tempest.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(tempest)

## extract athena++ library
#
if (NOT EXISTS athenapp21)
  message(STATUS "Extracting athea++ ...")
  file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/athenapp21.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(athenapp21)
