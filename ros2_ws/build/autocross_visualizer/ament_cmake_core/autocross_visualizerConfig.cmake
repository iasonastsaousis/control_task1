# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_autocross_visualizer_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED autocross_visualizer_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(autocross_visualizer_FOUND FALSE)
  elseif(NOT autocross_visualizer_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(autocross_visualizer_FOUND FALSE)
  endif()
  return()
endif()
set(_autocross_visualizer_CONFIG_INCLUDED TRUE)

# output package information
if(NOT autocross_visualizer_FIND_QUIETLY)
  message(STATUS "Found autocross_visualizer: 0.0.0 (${autocross_visualizer_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'autocross_visualizer' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${autocross_visualizer_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(autocross_visualizer_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${autocross_visualizer_DIR}/${_extra}")
endforeach()
