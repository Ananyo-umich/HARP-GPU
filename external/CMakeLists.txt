###############################
## set up external libraries ##
###############################

## extract cdisort library
#
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cdisort213/CMakeLists.txt)
  message(STATUS "Found cdisort2.3.1 ...")
else()
  message(STATUS "Extracting cdisort2.3.1 ...")
  file(ARCHIVE_EXTRACT 
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cdisort2.1.3-cli.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(cdisort213)

## extract tempest library
#
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tempest/CMakeLists.txt)
  message(STATUS "Found temest ...")
else()
  message(STATUS "Extracting tempest ...")
  file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/tempest.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(tempest)

## extract athena++ library
#
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/athenapp21/CMakeLists.txt)
  message(STATUS "Found athenapp21 ...")
else()
  message(STATUS "Extracting athena++ ...")
  file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/athenapp21.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(athenapp21)

## extract climath library
#
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/climath/CMakeLists.txt)
  message(STATUS "Found climath ...")
else()
  message(STATUS "Extracting climath ...")
  file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/climath.tar.gz
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_subdirectory(climath)
