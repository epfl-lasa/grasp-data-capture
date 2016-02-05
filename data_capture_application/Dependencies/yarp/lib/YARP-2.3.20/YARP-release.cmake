#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "YARP_OS" for configuration "Release"
SET_PROPERTY(TARGET YARP_OS APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_OS PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_OS.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "winmm;${_IMPORT_PREFIX}/../ace-6.1.0/lib/ACE.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_OS.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_OS )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_OS "${_IMPORT_PREFIX}/lib/YARP_OS.lib" "${_IMPORT_PREFIX}/lib/YARP_OS.dll" )

# Import target "YARP_sig" for configuration "Release"
SET_PROPERTY(TARGET YARP_sig APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_sig PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_sig.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_sig.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_sig )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_sig "${_IMPORT_PREFIX}/lib/YARP_sig.lib" "${_IMPORT_PREFIX}/lib/YARP_sig.dll" )

# Import target "YARP_math" for configuration "Release"
SET_PROPERTY(TARGET YARP_math APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_math PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_math.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_sig;YARP_OS;${_IMPORT_PREFIX}/../gsl-1.14/lib/gsl.lib;${_IMPORT_PREFIX}/../gsl-1.14/lib/gslcblas.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_math.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_math )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_math "${_IMPORT_PREFIX}/lib/YARP_math.lib" "${_IMPORT_PREFIX}/lib/YARP_math.dll" )

# Import target "YARP_dev" for configuration "Release"
SET_PROPERTY(TARGET YARP_dev APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_dev PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_dev.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_sig;YARP_OS"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_dev.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_dev )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_dev "${_IMPORT_PREFIX}/lib/YARP_dev.lib" "${_IMPORT_PREFIX}/lib/YARP_dev.dll" )

# Import target "wire_rep_utils" for configuration "Release"
SET_PROPERTY(TARGET wire_rep_utils APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(wire_rep_utils PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/wire_rep_utils.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/wire_rep_utils.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS wire_rep_utils )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_wire_rep_utils "${_IMPORT_PREFIX}/lib/wire_rep_utils.lib" "${_IMPORT_PREFIX}/lib/wire_rep_utils.dll" )

# Import target "xmlrpc_carrier" for configuration "Release"
SET_PROPERTY(TARGET xmlrpc_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(xmlrpc_carrier PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/xmlrpc_carrier.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/xmlrpc_carrier.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS xmlrpc_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_xmlrpc_carrier "${_IMPORT_PREFIX}/lib/xmlrpc_carrier.lib" "${_IMPORT_PREFIX}/lib/xmlrpc_carrier.dll" )

# Import target "tcpros_carrier" for configuration "Release"
SET_PROPERTY(TARGET tcpros_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(tcpros_carrier PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/tcpros_carrier.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "wire_rep_utils;YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/tcpros_carrier.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS tcpros_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_tcpros_carrier "${_IMPORT_PREFIX}/lib/tcpros_carrier.lib" "${_IMPORT_PREFIX}/lib/tcpros_carrier.dll" )

# Import target "bayer_carrier" for configuration "Release"
SET_PROPERTY(TARGET bayer_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(bayer_carrier PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/bayer_carrier.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/bayer_carrier.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS bayer_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_bayer_carrier "${_IMPORT_PREFIX}/lib/bayer_carrier.lib" "${_IMPORT_PREFIX}/lib/bayer_carrier.dll" )

# Import target "priority_carrier" for configuration "Release"
SET_PROPERTY(TARGET priority_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(priority_carrier PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/priority_carrier.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/priority_carrier.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS priority_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_priority_carrier "${_IMPORT_PREFIX}/lib/priority_carrier.lib" "${_IMPORT_PREFIX}/lib/priority_carrier.dll" )

# Import target "yarpcar" for configuration "Release"
SET_PROPERTY(TARGET yarpcar APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(yarpcar PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/yarpcar.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev;wire_rep_utils;xmlrpc_carrier;tcpros_carrier;bayer_carrier;priority_carrier"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/yarpcar.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS yarpcar )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_yarpcar "${_IMPORT_PREFIX}/lib/yarpcar.lib" "${_IMPORT_PREFIX}/lib/yarpcar.dll" )

# Import target "YARP_name" for configuration "Release"
SET_PROPERTY(TARGET YARP_name APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_name PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_name.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_name.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_name )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_name "${_IMPORT_PREFIX}/lib/YARP_name.lib" "${_IMPORT_PREFIX}/lib/YARP_name.dll" )

# Import target "YARP_init" for configuration "Release"
SET_PROPERTY(TARGET YARP_init APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
SET_TARGET_PROPERTIES(YARP_init PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/YARP_init.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "YARP_OS;YARP_sig;YARP_math;YARP_dev;yarpcar;wire_rep_utils;xmlrpc_carrier;tcpros_carrier;bayer_carrier;priority_carrier;YARP_name;yarpcar"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/YARP_init.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_init )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_init "${_IMPORT_PREFIX}/lib/YARP_init.lib" "${_IMPORT_PREFIX}/lib/YARP_init.dll" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
