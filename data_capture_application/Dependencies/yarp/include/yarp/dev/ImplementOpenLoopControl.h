// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006, 2008, 2009 RobotCub Consortium
 * Authors: Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __YARP_OPEN_LOOP_IMPL__
#define __YARP_OPEN_LOOP_IMPL__

#include <yarp/dev/IOpenLoopControl.h>
#include <yarp/dev/api.h>

namespace yarp {
    namespace dev {
        class ImplementOpenLoopControl;
    }
}

class YARP_dev_API yarp::dev::ImplementOpenLoopControl: public IOpenLoopControl
{
    void *helper;
    yarp::dev::IOpenLoopControlRaw *raw;
    double *dummy;
public:
    bool initialize(int k, const int *amap);
    bool uninitialize();
    ImplementOpenLoopControl(IOpenLoopControlRaw *v);
    ~ImplementOpenLoopControl();
    bool setOutput(int j, double v);
    bool setOutputs(const double *v);
    bool setOpenLoopMode();
    bool getOutput(int j, double *v);
    bool getOutputs(double *v);
};

#endif


