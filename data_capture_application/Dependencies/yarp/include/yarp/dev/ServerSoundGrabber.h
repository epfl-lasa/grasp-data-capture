// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Julio Gomes
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _YARP2_SERVERSOUNDGRABBER_
#define _YARP2_SERVERSOUNDGRABBER_

#include <stdio.h>


#include <yarp/os/BufferedPort.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/GenericSensorInterfaces.h>
#include <yarp/os/Time.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/Vocab.h>
#include <yarp/os/Bottle.h>

//#define NUM_SAMPLES 8192

namespace yarp
{
	namespace dev
	{
		class ServerSoundGrabber;
	}
}


/**
 * @ingroup dev_impl_wrapper
 *
 * Export a microphone device

 * streaming sound samples
 *
 * \author (adapted) J�lio Gomes, VisLab ISR/IST - 2006
 *
 */
class YARP_dev_API yarp::dev::ServerSoundGrabber : public DeviceDriver,
			private yarp::os::Thread,
			public yarp::os::PortReader,
			public IAudioGrabberSound
{
private:
    bool spoke;
    PolyDriver poly;
    IAudioGrabberSound *mic; //The microphone device
    yarp::os::Port p;
    yarp::os::PortWriterBuffer<yarp::os::Bottle> writer;
    yarp::os::PortWriterBuffer<yarp::sig::Sound> writerSound;
public:
    /**
     * Constructor.
     */
    ServerSoundGrabber()
    {
        mic = NULL;
        spoke = false;
    }

    virtual ~ServerSoundGrabber() {
        if (mic != NULL) close();
    }

    /**
     * Configure with a set of options. These are:
     * <TABLE>
     * <TR><TD> subdevice </TD><TD> Common name of device to wrap (e.g. "test_grabber"). </TD></TR>
     * <TR><TD> name </TD><TD> Port name to assign to this server (default /grabber). </TD></TR>
     * </TABLE>
     *
     * @param config The options to use
     * @return true iff the object could be configured.
     */
    virtual bool open(yarp::os::Searchable& config)
    {
        printf("(NOTE: Alternative to ServerSoundGrabber: just use normal ServerFrameGrabber)\n");
        p.setReader(*this);
        //Look for the device name
        yarp::os::Value *name;
        if (config.check("subdevice",name))
			{
				printf("Subdevice %s\n", name->toString().c_str());
				if (name->isString())
                    {
                        // maybe user isn't doing nested configuration
                        yarp::os::Property p;
                        p.fromString(config.toString());
                        p.put("device",name->toString());
                        poly.open(p);
                    }
				else
					poly.open(*name);
				if (!poly.isValid())
					printf("cannot make <%s>\n", name->toString().c_str());
			}
        else
			{
				printf("\"--subdevice <name>\" not set for server_soundgrabber\n");
				return false;
			}
        if (poly.isValid())
            poly.view(mic);

        if (mic!=NULL)
            writerSound.attach(p);

        //Look for the portname to register (--name option)
        if (config.check("name",name))
            p.open(name->asString());
        else
            p.open("/sound_grabber");

        //Look for the portname to register (--name option)
        //			p.open(config.check("name", Value("/microphone")).asString());

        if (mic!=NULL)
			{
				printf("\n\n----------------wrapper--------------\n\n\n\n");
				start();
				return true;
			}
        else
            return false;
    }

    virtual bool close()
    {
        if (mic != NULL) {
            stop();
            mic = NULL;
            return true;
        }
        return false;
    }

    virtual void run()
    {
        while(!isStopping())
			{
				if (mic!=NULL)
                    {
                        yarp::sig::Sound& snd = writerSound.get();
                        getSound(snd);
                        writerSound.write();
                    }
			}
        printf("Sound grabber stopping\n");
    }

    virtual bool read(ConnectionReader& connection)
    {
        yarp::os::Bottle cmd, response;
        cmd.read(connection);
        printf("command received: %s\n", cmd.toString().c_str());
        // We receive a command but don't do anything with it.
        printf("Returning from command reading\n");
        return true;
    }

    virtual bool getSound(yarp::sig::Sound& sound) {
        if (mic==NULL) { return false; }
        return mic->getSound(sound);
    }

    virtual bool getChannels(int *nc)
    {
        if (mic == NULL) { return false; }
        //return mic->getChannels (nc);
        return 1;
    }
};

#endif

