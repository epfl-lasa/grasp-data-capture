#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "YARP_OS" for configuration "Debug"
SET_PROPERTY(TARGET YARP_OS APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_OS PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_OSd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "winmm;${_IMPORT_PREFIX}/../ace-6.1.0/lib/ACEd.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_OSd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_OS )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_OS "${_IMPORT_PREFIX}/lib/YARP_OSd.lib" "${_IMPORT_PREFIX}/lib/YARP_OSd.dll" )

# Import target "YARP_sig" for configuration "Debug"
SET_PROPERTY(TARGET YARP_sig APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_sig PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_sigd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_sigd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_sig )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_sig "${_IMPORT_PREFIX}/lib/YARP_sigd.lib" "${_IMPORT_PREFIX}/lib/YARP_sigd.dll" )

# Import target "YARP_math" for configuration "Debug"
SET_PROPERTY(TARGET YARP_math APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_math PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_mathd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_sig;YARP_OS;${_IMPORT_PREFIX}/../gsl-1.14/lib/debug/gsl.lib;${_IMPORT_PREFIX}/../gsl-1.14/lib/debug/gslcblas.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_mathd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_math )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_math "${_IMPORT_PREFIX}/lib/YARP_mathd.lib" "${_IMPORT_PREFIX}/lib/YARP_mathd.dll" )

# Import target "YARP_dev" for configuration "Debug"
SET_PROPERTY(TARGET YARP_dev APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_dev PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_devd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_sig;YARP_OS"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_devd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_dev )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_dev "${_IMPORT_PREFIX}/lib/YARP_devd.lib" "${_IMPORT_PREFIX}/lib/YARP_devd.dll" )

# Import target "wire_rep_utils" for configuration "Debug"
SET_PROPERTY(TARGET wire_rep_utils APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(wire_rep_utils PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/wire_rep_utilsd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/wire_rep_utilsd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS wire_rep_utils )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_wire_rep_utils "${_IMPORT_PREFIX}/lib/wire_rep_utilsd.lib" "${_IMPORT_PREFIX}/lib/wire_rep_utilsd.dll" )

# Import target "xmlrpc_carrier" for configuration "Debug"
SET_PROPERTY(TARGET xmlrpc_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(xmlrpc_carrier PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/xmlrpc_carrierd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/xmlrpc_carrierd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS xmlrpc_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_xmlrpc_carrier "${_IMPORT_PREFIX}/lib/xmlrpc_carrierd.lib" "${_IMPORT_PREFIX}/lib/xmlrpc_carrierd.dll" )

# Import target "tcpros_carrier" for configuration "Debug"
SET_PROPERTY(TARGET tcpros_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(tcpros_carrier PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/tcpros_carrierd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "wire_rep_utils;YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/tcpros_carrierd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS tcpros_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_tcpros_carrier "${_IMPORT_PREFIX}/lib/tcpros_carrierd.lib" "${_IMPORT_PREFIX}/lib/tcpros_carrierd.dll" )

# Import target "bayer_carrier" for configuration "Debug"
SET_PROPERTY(TARGET bayer_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(bayer_carrier PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/bayer_carrierd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/bayer_carrierd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS bayer_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_bayer_carrier "${_IMPORT_PREFIX}/lib/bayer_carrierd.lib" "${_IMPORT_PREFIX}/lib/bayer_carrierd.dll" )

# Import target "priority_carrier" for configuration "Debug"
SET_PROPERTY(TARGET priority_carrier APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(priority_carrier PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/priority_carrierd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/priority_carrierd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS priority_carrier )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_priority_carrier "${_IMPORT_PREFIX}/lib/priority_carrierd.lib" "${_IMPORT_PREFIX}/lib/priority_carrierd.dll" )

# Import target "yarpcar" for configuration "Debug"
SET_PROPERTY(TARGET yarpcar APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(yarpcar PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/yarpcard.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev;wire_rep_utils;xmlrpc_carrier;tcpros_carrier;bayer_carrier;priority_carrier"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/yarpcard.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS yarpcar )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_yarpcar "${_IMPORT_PREFIX}/lib/yarpcard.lib" "${_IMPORT_PREFIX}/lib/yarpcard.dll" )

# Import target "YARP_name" for configuration "Debug"
SET_PROPERTY(TARGET YARP_name APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_name PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_named.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_named.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_name )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_name "${_IMPORT_PREFIX}/lib/YARP_named.lib" "${_IMPORT_PREFIX}/lib/YARP_named.dll" )

# Import target "YARP_init" for configuration "Debug"
SET_PROPERTY(TARGET YARP_init APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(YARP_init PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/YARP_initd.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "YARP_OS;YARP_sig;YARP_math;YARP_dev;yarpcar;wire_rep_utils;xmlrpc_carrier;tcpros_carrier;bayer_carrier;priority_carrier;YARP_name;yarpcar"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/YARP_initd.dll"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS YARP_init )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_YARP_init "${_IMPORT_PREFIX}/lib/YARP_initd.lib" "${_IMPORT_PREFIX}/lib/YARP_initd.dll" )

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
