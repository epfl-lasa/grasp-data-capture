// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick and Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __YARP2_FRAME_GRABBER__
#define __YARP2_FRAME_GRABBER__

#include <yarp/dev/DeviceDriver.h>
#include <yarp/sig/Image.h>

/*! \file FrameGrabberInterfaces.h define common interfaces for frame
  grabber devices */

namespace yarp{
    namespace dev {
        class IFrameGrabberImageSize;
        class IFrameGrabber;
        class IFrameGrabberRgb;
        class IFrameGrabberImage;
        class IFrameGrabberImageRaw;
        class IFrameGrabberControls;
		class IFrameGrabberControlsDC1394;
        class FrameGrabberOpenParameters;
        class IFrameWriterImage;
    }
}

/** 
 * @ingroup dev_iface_media
 *
 * Common interface to a FrameGrabber.
 */
class YARP_dev_API yarp::dev::IFrameGrabber
{
public:
    virtual ~IFrameGrabber(){}
    
    /**
     * Get the raw buffer from the frame grabber. The driver returns 
     * a copy of the internal memory buffer acquired by the frame grabber, no
     * post processing is applied (e.g. no color reconstruction/demosaicking).
     * The user must allocate the buffer; the size of the buffer, in bytes, 
     * is determined by calling getRawBufferSize().
     * @param buffer: pointer to the buffer to be filled (must be previously allocated)
     * @return true/false upon success/failure
     */
    virtual bool getRawBuffer(unsigned char *buffer)=0;

    /**
     * Get the size of the card's internal buffer, the user should use this 
     * method to allocate the storage to contain a raw frame (getRawBuffer).
     * @return the size of the internal buffer, in bytes.
     **/
    virtual int getRawBufferSize()=0;

    /** 
     * Return the height of each frame.
     * @return image height
     */
    virtual int height() const =0;

    /** 
     * Return the width of each frame.
     * @return image width
     */
    virtual int width() const =0;
};

/** 
 * @ingroup dev_iface_media
 *
 * RGB Interface to a FrameGrabber device.
 */
class YARP_dev_API yarp::dev::IFrameGrabberRgb
{
public:
    virtual ~IFrameGrabberRgb(){}
    /**
     * Get a rgb buffer from the frame grabber, if required
     * demosaicking/color reconstruction is applied
     * 
     * @param buffer: pointer to the buffer to be filled (must be previously allocated)
     * @return true/false upon success/failure
     */
    virtual bool getRgbBuffer(unsigned char *buffer)=0;

    /** 
     * Return the height of each frame.
     * @return image height
     */
    virtual int height() const =0;

    /** 
     * Return the width of each frame.
     * @return image width
     */
    virtual int width() const =0;
};

/**
 * @ingroup dev_iface_media
 *
 * Read a YARP-format image from a device.
 */
class YARP_dev_API yarp::dev::IFrameGrabberImage
{
public:
    /**
     * Destructor.
     */
    virtual ~IFrameGrabberImage(){}
    /**
     * Get an rgb image from the frame grabber, if required
     * demosaicking/color reconstruction is applied
     * 
     * @param image the image to be filled
     * @return true/false upon success/failure
     */
    virtual bool getImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>& image) = 0;

    /** 
     * Return the height of each frame.
     * @return image height
     */
    virtual int height() const =0;

    /** 
     * Return the width of each frame.
     * @return image width
     */
    virtual int width() const =0;
};

/**
 * @ingroup dev_iface_media
 *
 * Read a YARP-format image from a device.
 */
class YARP_dev_API yarp::dev::IFrameGrabberImageRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IFrameGrabberImageRaw(){}
    /**
     * Get a raw image from the frame grabber
     * 
     * @param image the image to be filled
     * @return true/false upon success/failure
     */
    virtual bool getImage(yarp::sig::ImageOf<yarp::sig::PixelMono>& image) = 0;

    /** 
     * Return the height of each frame.
     * @return image height
     */
    virtual int height() const =0;

    /** 
     * Return the width of each frame.
     * @return image width
     */
    virtual int width() const =0;
};

/**
 * @ingroup dev_iface_media
 *
 * Read a YARP-format image to a device.
 */
class YARP_dev_API yarp::dev::IFrameWriterImage
{
public:
    /**
     * Destructor.
     */
    virtual ~IFrameWriterImage(){}

    /**
     * Write an image to the device.
     * 
     * @param image the image to write
     * @return true/false upon success/failure
     */
    virtual bool putImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>& image) = 0;
};

/**
 * @ingroup dev_iface_media
 *
 * Control interface for frame grabber devices.
 */
class YARP_dev_API yarp::dev::IFrameGrabberControls
{
public:
    /**
     * Destructor.
     */
    virtual ~IFrameGrabberControls(){}

// set
    /**
     * Set the brightness.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setBrightness(double v)=0;
    /**
     * Set the exposure.
     * @param v new value for parameter.
     * @return true on success.
     */
    virtual bool setExposure(double v)=0;
    /**
     * Set the sharpness.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setSharpness(double v)=0;
	/**
     * Set the white balance for the frame grabber.
     * @param blue component gain.
     * @param red component gain.
     * @return true/false if successful or not.
     */
	virtual bool setWhiteBalance(double blue, double red)=0;
    /**
     * Set the hue.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setHue(double v)=0;
    /**
     * Set the saturation.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setSaturation(double v)=0;
    /**
     * Set the gamma.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setGamma(double v)=0;
    /**
     * Set the shutter parameter.
     * @param v new value for parameter.
     * @return true on success.
     */
	virtual bool setShutter(double v)=0;
    /**
     * Set the gain.
     * @param v new value for parameter.
     * @return true on success.
     */
    virtual bool setGain(double v)=0;
    /**
     * Set the iris.
     * @param v new value for parameter.
     * @return true on success.
     */
    virtual bool setIris(double v)=0;

    // not implemented
    //virtual bool setTemperature(double v)=0;
    //virtual bool setWhiteShading(double r,double g,double b)=0;
    //virtual bool setOpticalFilter(double v)=0;
    //virtual bool setCaptureQuality(double v)=0;
    
// get
    /**
     * Read the brightness parameter.
     * @return the current brightness value.
     */
	virtual double getBrightness()=0;
    /**
     * Read the exposure parameter.
     * @return the current exposure value.
     */
	virtual double getExposure()=0;
    /**
     * Read the sharpness parameter.
     * @return the current sharpness value.
     */	
	virtual double getSharpness()=0;
	/**
     * Read the white balance parameters.
     * @param blue reference to return value for the red parameter.
	 * @param red reference to return value for the green parameter.
	 * @return true/false.
     */
    virtual bool getWhiteBalance(double &blue, double &red)=0;
    /**
     * Read the hue parameter.
     * @return the current hue value.
     */	
	virtual double getHue()=0;
    /**
     * Read the saturation parameter.
     * @return the current saturation value.
     */	
	virtual double getSaturation()=0;
    /**
     * Read the gamma parameter.
     * @return the current gamma value.
     */	
	virtual double getGamma()=0;
    /**
     * Read the shutter parameter.
     * @return the current shutter value.
     */
    virtual double getShutter()=0;
    /**
     * Read the gain parameter.
     * @return the current gain value.
     */
    virtual double getGain()=0;
    /**
     * Read the iris parameter.
     * @return the current iris value.
     */
    virtual double getIris()=0;
    
    // not implemented
    //virtual double getTemperature() const=0;
    //virtual bool getWhiteShading(double &r,double &g,double &b) const=0;
    //virtual double getOpticalFilter() const=0;
    //virtual double getCaptureQuality() const=0;
};

class YARP_dev_API yarp::dev::IFrameGrabberControlsDC1394 : public yarp::dev::IFrameGrabberControls
{
public:	
	// 00 01 02
	virtual bool hasFeatureDC1394(int feature)=0;//{ return true; }
	virtual bool setFeatureDC1394(int feature,double value)=0;//{ return true; }
	virtual double getFeatureDC1394(int feature)=0;//{ return 0.5; }

	// 03 04 05 	
	virtual bool hasOnOffDC1394(int feature)=0;//{ return true; }
	virtual bool setActiveDC1394(int feature, bool onoff)=0;//{ return true; }
	virtual bool getActiveDC1394(int feature)=0;//{ return true; }
	
	// 06 07 08 09 10 11
	virtual bool hasAutoDC1394(int feature)=0;//{ return true; }
	virtual bool hasManualDC1394(int feature)=0;//{ return true; }
	virtual bool hasOnePushDC1394(int feature)=0;//{ return true; }
	virtual bool setModeDC1394(int feature, bool auto_onoff)=0;//{ return true; }
	virtual bool getModeDC1394(int feature)=0;//{ return true; }
	virtual bool setOnePushDC1394(int feature)=0;//{ return true; }

	// 12 13 14 
	virtual unsigned int getVideoModeMaskDC1394()=0;//{ return 0xFFFFFFFF; }
	virtual unsigned int getVideoModeDC1394()=0;//{ return 0; }
	virtual bool setVideoModeDC1394(int video_mode)=0;//{ return true; }

	// 15 16 17
	virtual unsigned int getFPSMaskDC1394()=0;//{ return 0xFFFFFFFF; }
	virtual unsigned int getFPSDC1394()=0;//{ return 0; }
	virtual bool setFPSDC1394(int fps)=0;//{ return true; }

	// 18 19
	virtual unsigned int getISOSpeedDC1394()=0;//{ return 0; }
	virtual bool setISOSpeedDC1394(int speed)=0;//{ return true; }

	// 20 21 22
	virtual unsigned int getColorCodingMaskDC1394(unsigned int video_mode)=0;//{ return 0xFFFFFFFF; }
	virtual unsigned int getColorCodingDC1394()=0;//{ return 0; }
	virtual bool setColorCodingDC1394(int coding)=0;//{ return true; }

	// 23 24
	virtual bool setWhiteBalanceDC1394(double b, double r)=0;//{ return true; }
	virtual bool getWhiteBalanceDC1394(double &b, double &r)=0;
    /*{
        b=r=0.5;
        return true;
    }*/

	// 25 26 27
	virtual bool getFormat7MaxWindowDC1394(unsigned int &xdim,unsigned int &ydim,unsigned int &xstep,unsigned int &ystep,unsigned int &xoffstep,unsigned int &yoffstep)=0;
	/*{
		xdim=324; ydim=244; xstep=2; ystep=2;
		return true;
	}*/
	virtual bool getFormat7WindowDC1394(unsigned int &xdim,unsigned int &ydim,int &x0,int &y0)=0;
	/*{
		xdim=324; ydim=244;
		return true;
	}*/
	virtual bool setFormat7WindowDC1394(unsigned int xdim,unsigned int ydim,int x0,int y0)=0;//{ return true; }

	// 28
	virtual bool setOperationModeDC1394(bool b1394b)=0;//{ return true; }
	// 29
	virtual bool getOperationModeDC1394()=0;//{ return true; } 
	// 30
	virtual bool setTransmissionDC1394(bool bTxON)=0;//{ return true; }
	// 31
	virtual bool getTransmissionDC1394()=0;//{ return true; }
	// 32
	//virtual bool setBayerDC1394(bool bON)=0;//{ return true; }
	// 33
	//virtual bool getBayerDC1394()=0;//{ return true; }

	// 34 35 36 37
	virtual bool setBroadcastDC1394(bool onoff)=0;//{ return true; }
	virtual bool setDefaultsDC1394()=0;//{ return true; }
	virtual bool setResetDC1394()=0;//{ return true; }
	virtual bool setPowerDC1394(bool onoff)=0;//{ return true; }

	// 38
	virtual bool setCaptureDC1394(bool bON)=0;//{ return true; }

	// 39
	virtual unsigned int getBytesPerPacketDC1394()=0;//{ return 0; }

	// 40
	virtual bool setBytesPerPacketDC1394(unsigned int bpp)=0;//{ return true; }
};

#endif
