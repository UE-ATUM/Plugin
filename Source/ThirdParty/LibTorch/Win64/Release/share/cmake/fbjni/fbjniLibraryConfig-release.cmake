#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fbjni" for configuration "Release"
set_property(TARGET fbjni APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fbjni PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fbjni.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/fbjni.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fbjni )
list(APPEND _IMPORT_CHECK_FILES_FOR_fbjni "${_IMPORT_PREFIX}/lib/fbjni.lib" "${_IMPORT_PREFIX}/bin/fbjni.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
