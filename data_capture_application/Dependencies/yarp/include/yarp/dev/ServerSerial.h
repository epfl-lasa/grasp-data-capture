// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Alex Bernardino & Carlos Beltran-Gonzalez
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _YARP2_SERVERSERIAL_
#define _YARP2_SERVERSERIAL_

#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/BufferedPort.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/SerialInterfaces.h>
#include <yarp/os/Time.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/Vocab.h>
#include <yarp/os/Bottle.h>


using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;


namespace yarp
{
	namespace dev
	{
		class ServerSerial;
        class ImplementCallbackHelper2;
	}
}

/**
 * Callback implementation after buffered input.
 */
class yarp::dev::ImplementCallbackHelper2 : public TypedReaderCallback<Bottle> {
protected:
    ISerialDevice *ser;
    
public:
    /**
     * Constructor.
     * @param x is the instance of the container class using the callback.
     */
    ImplementCallbackHelper2();
    ImplementCallbackHelper2(yarp::dev::ServerSerial *x);

    /**
     * Callback function.
     * @param b is the Bottle being received.
     */
    virtual void onRead(Bottle& b);
};


/**
 * @ingroup dev_impl_wrapper
 *
 * Export a serial sensor.
 * The network interface is composed by two ports.
 * The input port accepts bottles and sends their contents as 
 * text to the serial port.
 * The output port streams out whatever information it gets in the
 * serial port as text bottles.
 *
 * @author Alex Bernardino
 */
class YARP_dev_API yarp::dev::ServerSerial : public DeviceDriver, public ISerialDevice, 
			                    private Thread
{
private:
    bool verb;
    PolyDriver poly;
    Port toDevice;
    Port fromDevice;

    PortWriterBuffer <Bottle> reply_buffer;
    PortReaderBuffer <Bottle> command_buffer;

    ISerialDevice *serial;
    yarp::dev::ImplementCallbackHelper2 callback_impl;


    bool closeMain() {
        if (Thread::isRunning()) {
            Thread::stop();
        }
        //close the port connection here
        toDevice.close();
        fromDevice.close();
        poly.close();
        return true;
    }
   
public:
    /**
     * Constructor.
     */
    ServerSerial() : callback_impl(this)
    {
        serial = NULL;
        verb = false;
    }

    virtual ~ServerSerial() {
        closeMain();
    }

    virtual bool send(const Bottle& msg)
    {
        if(verb)
            printf("ConstString to send : %s\n", msg.toString().c_str());
        if(serial != NULL) {
            serial->send(msg);
            return true;
        }
        else
            return false;
    }
    
    virtual bool send(char *msg, size_t size)
    {
        if(verb)
            printf("ConstString to send : %s\n", msg);
        if(serial != NULL) {
            serial->send(msg, size);
            return true;
        }
        else
            return false;
    }

    virtual bool receive(Bottle& msg)
    {
        if(serial != NULL) {
            serial->receive(msg);
            return true;
        }
        else
            return false;
    }

    virtual int receiveChar(char& c)
    {
        if(serial != NULL) {
            return serial->receiveChar(c);
        }
        else
            return -1;
    }

	virtual int flush ()
	{
        if(serial != NULL) {
            return serial->flush();
        }
        else
            return -1;
	}

	virtual int receiveLine(char* line, const int MaxLineLength)
    {
        if(serial != NULL) {
            return serial->receiveLine(line, MaxLineLength);
        }
        else
            return -1;
    }

    /**
    * Default open() method.
    * @return always false since initialization requires certain parameters.
    */

    virtual bool open()  {
        return false;
    }

    /**
    * Close the device driver by deallocating all resources and closing ports.
    * @return true if successful or false otherwise.
    */
    virtual bool close() {
        return closeMain();
    }

    /**
     * Open the device driver.
     * 
     * @param prop is a Searchable object that contains the parameters to use.
     * Allowed parameters are:
     * - verbose or v to print diagnostic information while running,
     * - name to specify the prefix of the port names
     * and all parameters requied by the wrapped device driver.
     * @return true iff the object could be configured.
     */
    virtual bool open(Searchable& prop)
    {
        verb = (prop.check("verbose",Value(0),"Specifies if the device is in verbose mode (0/1).").asInt())>0;
		if (verb)
			printf("running with verbose output\n");

        Value *name;
        if (prop.check("subdevice",name,"name of specific control device to wrap")) {
            printf("Subdevice %s\n", name->toString().c_str());
            if (name->isString()) {
                // maybe user isn't doing nested configuration
                Property p;
                p.setMonitor(prop.getMonitor(),
                             "subdevice"); // pass on any monitoring
                p.fromString(prop.toString());
                p.put("device",name->toString());
                poly.open(p);
            } else {
                Bottle subdevice = prop.findGroup("subdevice").tail();
                poly.open(subdevice);
            }
            if (!poly.isValid()) {
                printf("cannot make <%s>\n", name->toString().c_str());
            }
        } else {
            printf("\"--subdevice <name>\" not set for server_serial\n");
            return false;
        }

        if (!poly.isValid()) {
            return false;
        }

        ConstString rootName = 
            prop.check("name",Value("/serial"),
                       "prefix for port names").asString().c_str();
        
        command_buffer.attach(toDevice);
        reply_buffer.attach(fromDevice);

        command_buffer.useCallback(callback_impl);
        
        toDevice.open((rootName+"/in").c_str());
        fromDevice.open((rootName+"/out").c_str());



        if (poly.isValid())
            poly.view(serial);

        if(serial != NULL) {
            start();
			return true;
        }

        printf("subdevice <%s> doesn't look like a serial port (no appropriate interfaces were acquired)\n",
                       name->toString().c_str());
        
        return false;
    }

   /**
     * The thread main loop deals with writing on ports here.
     */
    virtual void run() {
        printf("Server Serial starting\n");
        //double before, now;
        while (!isStopping()) {
            //before = Time::now();
            Bottle& b = reply_buffer.get();
            b.clear();
			receive( b ); 
            /*if(b.size() > 0)*/ /* this line was creating a memory leak !! */
            reply_buffer.write();
			//now = Time::now();
            // give other threads the chance to run 
            yarp::os::Time::delay(0.010);
        }
        printf("Server Serial stopping\n");
    }
};

// ImplementCallbackHelper class.


yarp::dev::ImplementCallbackHelper2::ImplementCallbackHelper2(yarp::dev::ServerSerial *x) {
    ser = dynamic_cast<yarp::dev::ISerialDevice *> (x);
    //ACE_ASSERT (ser != 0);
    if (ser==0) {
        printf("Could not get serial device\n");
        exit(1);
    }


}

void yarp::dev::ImplementCallbackHelper2::onRead(Bottle &b) {
    //printf("Data received on the control channel of size: %d\n", v.body.size());
    //	int i;
   if (ser) {
        bool ok = ser->send(b);
        if (!ok)
            printf("Problems while trying to send data\n");
    }
}

#endif

