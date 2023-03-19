#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpuinfo::clog" for configuration "Debug"
set_property(TARGET cpuinfo::clog APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cpuinfo::clog PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/clog.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS cpuinfo::clog )
list(APPEND _IMPORT_CHECK_FILES_FOR_cpuinfo::clog "${_IMPORT_PREFIX}/lib/clog.lib" )

# Import target "cpuinfo::cpuinfo" for configuration "Debug"
set_property(TARGET cpuinfo::cpuinfo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cpuinfo::cpuinfo PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/cpuinfo.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS cpuinfo::cpuinfo )
list(APPEND _IMPORT_CHECK_FILES_FOR_cpuinfo::cpuinfo "${_IMPORT_PREFIX}/lib/cpuinfo.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
