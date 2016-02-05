#pragma once

#include "DataChannel.h"
#include "vhtBase.h"
#include <vhtHumanHand.h>
#include <vhtKinematics.h>

// Raw sensor array of the cyber glove hand
enum cyberglovesensors {
	TR = 0,		//  Thumb rotation over palm keeping finger joints locked)
	TP = 1,		//  Thumb Proximal, Where Thumb meets the palm
	TD = 2,		//  Thumb Distal
	TIA = 3,	//  Thumb-Index abduction. 
	IM = 4,		//  Index Metacarpal
	IP = 5,		//  Index Proximal
	ID = 6,		//  Index Distal
	NOTUSED = 7,//  Unused index
	MM = 8,		//  Middle Metacarpal
	MP = 9,		//  Middle Proximal
	MD = 10,	//  Middle Distal
	IMA = 11,	//  Index-Middle Abduction 
	RM = 12,	//  Ring Metacarpal
	RP = 13,	//  Ring Proximal
	RD = 14,	//  Ring Distal
	MRA = 15,	//  Middle-Ring abduction
	PM = 16,	//  Pinky Metacarpal
	PP = 17,	//  Pinky Proximal
	PD = 18,	//  Pinky Distal
	RPA = 19,	//  Ring-Pinky abduction
	PA = 20,	//  Palm Arch. Rotation of Pinky across palm
	WP = 21,	//  Wrist Pitch or Flexion/Extension (up-down) motion of the wrist
	WY = 22,	//  Wrist Yaw or Abduction/Adduction (side-to-side) motion of the wrist
	NUMSENSORS = 23
};

class GloveData : public ChannelData
{
public:
	GloveData(string id);
	void setTransform(int handPart, double matrix[4][4]);
	void setJointValues(int joint, double value, double cal);
	string toString(void);
	void toBottle(Bottle& b);
	int toBuffer(byte* b);

private:
	double transforms[NUMSENSORS][4][4];
	double rawJointValues[NUMSENSORS];
	double calJointValues[NUMSENSORS];
};

class GloveChannel : public DataChannel
{
public:
	GloveChannel(void);
	~GloveChannel(void);
	ChannelData* getLatest();

protected:
	int doStart(void);
	int doStop(void);	

private:
	//vhtHumanHand *hand;
	//vhtKinematics *hKin;
	vhtCyberGlove *glove;
	GloveData gd;
};
