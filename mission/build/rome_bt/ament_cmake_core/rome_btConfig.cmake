# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_rome_bt_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED rome_bt_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(rome_bt_FOUND FALSE)
  elseif(NOT rome_bt_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(rome_bt_FOUND FALSE)
  endif()
  return()
endif()
set(_rome_bt_CONFIG_INCLUDED TRUE)

# output package information
if(NOT rome_bt_FIND_QUIETLY)
  message(STATUS "Found rome_bt: 0.0.0 (${rome_bt_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'rome_bt' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${rome_bt_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(rome_bt_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${rome_bt_DIR}/${_extra}")
endforeach()
