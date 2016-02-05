// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _YARP2_SHMEMCARRIER_
#define _YARP2_SHMEMCARRIER_

#include <yarp/os/impl/AbstractCarrier.h>

// removing old shmem version
// #include <yarp/os/impl/ShmemTwoWayStream.h>

// new shmem implementation from Alessandro
#include <yarp/os/impl/ShmemHybridStream.h>

//#include <ace/OS.h>

namespace yarp {
    namespace os {
        namespace impl {
            class ShmemCarrier;
        }
    }
}

class yarp::os::impl::ShmemCarrier : public AbstractCarrier {
private:
    int version;
public:
    /**
     * verion 1 is "classic" YARP implementation of shmem.
     * version 2 is "Alessandro" version.
     */
    ShmemCarrier(int version = 2) {
        this->version = version;
    }

    virtual Carrier *create() {
        return new ShmemCarrier(version);
    }

    virtual String getName() {
        return (version==2)?"shmem":"shmem1";
    }

    virtual int getSpecifierCode() {
        // specifier codes are a very old yarp feature,
        // not necessary any more really, should be replaced.
        return (version==1)?2:14;
    }

    virtual bool requireAck() {
        return true;
    }

    virtual bool isConnectionless() {
        return false;
    }

    virtual bool checkHeader(const Bytes& header) {
        return getSpecifier(header)%16 == getSpecifierCode();
    }

    virtual void getHeader(const Bytes& header) {
        createStandardHeader(getSpecifierCode(), header);
    }

    virtual void setParameters(const Bytes& header) {
    }


    /*
      -- unfortunately member templates not working on Visual Studio 6?
    template <class T>
    void becomeShmemVersion(Protocol& proto, bool sender) {
        T *stream = new T();  // Shmem(TwoWay|Hybrid)Stream
        YARP_ASSERT(stream!=NULL);
        Address base;
        try {
            if (!sender) {
                ACE_INET_Addr anywhere((u_short)0, (ACE_UINT32)INADDR_ANY);
                base = Address(anywhere.get_host_addr(),
                               anywhere.get_port_number());
                stream->open(base,sender);
                int myPort = stream->getLocalAddress().getPort();
                proto.writeYarpInt(myPort);
                stream->accept();
                proto.takeStreams(NULL);
                proto.takeStreams(stream);
            } else {
                int altPort = proto.readYarpInt();
                String myName = proto.getStreams().getLocalAddress().getName();
                proto.takeStreams(NULL);
                base = Address(myName,altPort);
                stream->open(base,sender);
                proto.takeStreams(stream);
            }
        } catch (IOException e) {
            delete stream;
            stream = NULL;
            throw e;
        }
    }
    */

    /*
    void becomeShmemVersionTwoWayStream(Protocol& proto, bool sender) {
        ShmemTwoWayStream *stream = new ShmemTwoWayStream();
        YARP_ASSERT(stream!=NULL);
        Address base;
        try {
            if (!sender) {
                ACE_INET_Addr anywhere((u_short)0, (ACE_UINT32)INADDR_ANY);
                base = Address(anywhere.get_host_addr(),
                               anywhere.get_port_number());
                stream->open(base,sender);
                int myPort = stream->getLocalAddress().getPort();
                proto.writeYarpInt(myPort);
                stream->accept();
                proto.takeStreams(NULL);
                proto.takeStreams(stream);
            } else {
                int altPort = proto.readYarpInt();
                String myName = proto.getStreams().getLocalAddress().getName();
                proto.takeStreams(NULL);
                base = Address(myName,altPort);
                stream->open(base,sender);
                proto.takeStreams(stream);
            }
        } catch (IOException e) {
            delete stream;
            stream = NULL;
            throw e;
        }
    }
    */

    bool becomeShmemVersionHybridStream(Protocol& proto, bool sender) {
        ShmemHybridStream *stream = new ShmemHybridStream();
        YARP_ASSERT(stream!=NULL);
        Address base;

        bool ok = true;

        if (!sender) {
            ACE_INET_Addr anywhere((u_short)0, (ACE_UINT32)INADDR_ANY);
            base = Address(anywhere.get_host_addr(),
                           anywhere.get_port_number());
            bool ok = stream->open(base,sender)==0;
            if (ok) {
                int myPort = stream->getLocalAddress().getPort();
                proto.writeYarpInt(myPort);
                stream->accept();
                proto.takeStreams(NULL);
                proto.takeStreams(stream);
            }
        } else {
            int altPort = proto.readYarpInt();
            String myName = proto.getStreams().getLocalAddress().getName();
            proto.takeStreams(NULL);
            base = Address(myName,altPort);
            ok = stream->open(base,sender)==0;
            if (ok) {
                proto.takeStreams(stream);
            }
        }

        if (!ok) {
            delete stream;
            stream = NULL;
            return false;
        }

        return true;
    }

    virtual bool becomeShmem(Protocol& proto, bool sender) {
        if (version==1) {
            // "classic" shmem
            //becomeShmemVersion<ShmemTwoWayStream>(proto,sender);
            //becomeShmemVersionTwoWayStream(proto,sender);
            ACE_OS::printf("Classic shmem no longer exists\n");
            ACE_OS::exit(1);
            return false;
        } else {
            // experimental shmem
            //becomeShmemVersion<ShmemHybridStream>(proto,sender);
            return becomeShmemVersionHybridStream(proto,sender);
        }
    }

    virtual bool respondToHeader(Protocol& proto) {
        // i am the receiver
        return becomeShmem(proto,false);
    }


    virtual bool expectReplyToHeader(Protocol& proto) {
        // i am the sender
        return becomeShmem(proto,true);
    }

};

#endif

