// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __YARP2_SERVICEINTERFACES__
#define __YARP2_SERVICEINTERFACES__

#include <yarp/dev/DeviceDriver.h>


namespace yarp {
    namespace dev {
        class IService;
    }
}

/** 
 * @ingroup dev_iface_other
 *
 * Common interface for devices that act like services (by which we
 * mean they do something for remote users, with minimal interaction
 * with their creator other than initial configuration).
 */
class YARP_dev_API yarp::dev::IService {
public:
    virtual ~IService() {}

    /**
     * Initiate the service, whatever it is.  The service should
     * then run by itself, without any further interaction with
     * its creator until stopService() is called.
     * @return true if the service started and needs no help running.
     * If false is returned, the service expects updateService() to
     * be called repeatedly until that function too returns false.
     * This is useful for devices that don't want to manage their
     * own service threads.
     */
    virtual bool startService() {
        return false;
    }
    
    /**
     * Give the service the chance to run for a while.  This is an
     * alternative to calling startService().  It is more 
     * appropriate in a single-threaded environment.
     * @return true iff the service is willing to run
     * some more.  A return value of false means that the service 
     * would like to stop.
     */
    virtual bool updateService() {
        return false;
    }
    
    /**
     * Shut down the service, whatever it is.
     * @return true iff the service shut down ok.
     */
    virtual bool stopService() {
        return false;
    }
};

#endif
