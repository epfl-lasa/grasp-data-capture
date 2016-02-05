// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2012 IITRBCS
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _YARP2_MODIFYINGCARRIER_
#define _YARP2_MODIFYINGCARRIER_

#include <yarp/os/impl/AbstractCarrier.h>
#include <yarp/os/impl/Protocol.h>

namespace yarp {
    namespace os {
        namespace impl {
            class ModifyingCarrier;
        }
    }
}

/**
 * A starter class for implementing simple modifying carriers.
 * These are not standalone carriers, they just tweak payload data
 * in custom ways.
 */
class yarp::os::impl::ModifyingCarrier : public AbstractCarrier {
public:

    virtual Carrier *create() = 0;

    virtual String getName() = 0;

    virtual bool checkHeader(const yarp::os::Bytes& header) {
      return false;
    }

    virtual void getHeader(const yarp::os::Bytes& header) {
      if (header.length()==8) {
	String target = "ohbehave";
	for (int i=0; i<8; i++) {
	  header.get()[i] = target[i];
	}
      }        
    }


    virtual bool respondToHeader(Protocol& proto) {
      return false;
    }

     virtual bool modifiesIncomingData() {
       return true;
     }

     // only remains to implement modifyIncomingData()
};

#endif
