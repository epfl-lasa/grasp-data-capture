// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: (C) 2009 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_CONFIG_SYSTEM_H
#define YARP_CONFIG_SYSTEM_H

#define YARP_CMAKE_CONFIG

#ifdef YARP_INT16
#undef YARP_INT16
#endif

#ifdef YARP_INT32
#undef YARP_INT32
#endif

#ifdef YARP_INT64
#undef YARP_INT64
#endif

#ifdef YARP_FLOAT32
#undef YARP_FLOAT32
#endif

#ifdef YARP_FLOAT64
#undef YARP_FLOAT64
#endif

#ifdef YARP_BIG_ENDIAN
#undef YARP_BIG_ENDIAN
#endif

#ifdef YARP_LITTLE_ENDIAN
#undef YARP_LITTLE_ENDIAN
#endif

#define YARP_INT16 short
#define YARP_INT32 int
#define YARP_INT64 long long
#define YARP_FLOAT32 float
#define YARP_FLOAT64 double

/* #undef YARP_BIG_ENDIAN */
#define YARP_LITTLE_ENDIAN

/* #undef YARP_USE_STL_STRING */
#define YARP_USE_ACE_STRING

#define YARP_HAS_ACE

#define YARP_USE_ACE_STRING_BASE_CONST_SIZE_TYPE
/* #undef YARP_ACE_ADDR_HAS_LOOPBACK_METHOD */
/* #undef YARP_ACE_COMPILES_WITHOUT_INLINE */

#endif
