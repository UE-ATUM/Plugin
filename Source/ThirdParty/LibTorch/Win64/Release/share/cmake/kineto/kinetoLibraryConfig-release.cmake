#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kineto" for configuration "Release"
set_property(TARGET kineto APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(kineto PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/kineto.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS kineto )
list(APPEND _IMPORT_CHECK_FILES_FOR_kineto "${_IMPORT_PREFIX}/lib/kineto.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
