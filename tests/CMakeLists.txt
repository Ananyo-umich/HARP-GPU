
##################
## set up tests ##
##################

file(GLOB _tests *.cpp)
foreach(_test ${_tests})
  get_filename_component(_name ${_test} NAME_WE)

  add_executable(${_name} ${_test})

  set_target_properties(${_name}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${EXECUTABLE_RELDIR}"
    )

  target_include_directories(${_name}
    SYSTEM PRIVATE
    ${EIGEN3_INCLUDE_DIR}
    ${CDISORT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}
    )

  target_link_libraries(${_name}
    harp
    ${NETCDF_LIBRARIES}
    ${CDISORT_LIBRARY}
    )

  #install(TARGETS ${_name})
endforeach()
