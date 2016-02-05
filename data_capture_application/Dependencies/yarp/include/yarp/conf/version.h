// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: (C) 2009 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_CONFIG_VERSION_H
#define YARP_CONFIG_VERSION_H

#ifdef YARP_VERSION_MAJOR
#undef YARP_VERSION_MAJOR
#endif
#ifdef YARP_VERSION_MINOR
#undef YARP_VERSION_MINOR
#endif
#ifdef YARP_VERSION_PATCH
#undef YARP_VERSION_PATCH
#endif
#ifdef YARP_VERSION
#undef YARP_VERSION
#endif

#define YARP_VERSION_MAJOR 2
#define YARP_VERSION_MINOR 3
#define YARP_VERSION_PATCH 20
#define YARP_VERSION_MODIFIER ""
#define YARP_VERSION "2.3.20"

#endif
