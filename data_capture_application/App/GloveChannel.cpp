#include "stdafx.h"
#include "GloveChannel.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <windows.h>
using namespace std;


// Mapping of the raw sensors array of the cyber glove to hand joints. We must provide these coordinates to get the corresponding calibrated values
int sensorjointmap[NUMSENSORS][2];

//
// GloveData routines
//
GloveData::GloveData(string id)
	: ChannelData(id)
{
	memset(transforms, 0, sizeof(transforms));
	memset(rawJointValues, 0, sizeof(rawJointValues));
	memset(calJointValues, 0, sizeof(calJointValues));
}

void GloveData::setTransform(int handPart, double matrix[4][4])
{
	assert(handPart < NUMSENSORS);

	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			transforms[handPart][i][j] = matrix[i][j];
}

void GloveData::setJointValues(int joint, double raw, double cal)
{
	assert(joint < NUMSENSORS);

	rawJointValues[joint] = raw;
	calJointValues[joint] = cal;
}

string GloveData::toString(void)
{
	stringstream strm;

	strm << "glove" << endl;
	for (int i=0; i<NUMSENSORS; i++)
		strm << rawJointValues[i] << ' ';
	strm << endl;

	//for (int i=0; i<NUMSENSORS; i++)
	//	strm << calJointValues[i] << ' ';
	//strm << endl;

	//for (int i=0; i<NUMSENSORS; i++) {
	//	strm << i << ":  ";
	//	for(int j=0; j<4; j++)
	//		for(int k=0; k<4; k++)				
	//			strm << transforms[i][j][k] << ' ';
	//	strm << endl;
	//}

	return string(strm.str());
}

void GloveData::toBottle(Bottle& b)
{
	b.addString("glove");
	Bottle& b1 = b.addList();
	for (int i=0; i<NUMSENSORS; i++)
		b1.addInt(rawJointValues[i]);
			
	b1.addInt(hr);
	b1.addInt(min);
	b1.addInt(sec);
	b1.addInt(ms);
}

int GloveData::toBuffer(byte* b)
{
	int idsz, datasz;
	long start = (long)b, end;

	idsz = id.length() + 1; 
	memcpy((void*)b, (void*)id.c_str(), idsz); b = b + idsz;

	memcpy((void*)b, (void*) &hr, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &min, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &sec, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &ms, sizeof(int)); b = b+sizeof(int);

	datasz = sizeof(rawJointValues);
	memcpy((void*)b, &datasz, sizeof(int)); b = b + sizeof(int);
	memcpy((void*)b, (void *)rawJointValues, datasz); b = b + datasz;

	end = (long)b;

	return end-start;
}
	

// 
//  GloveChannel Routines
//
GloveChannel::GloveChannel(void)
	: DataChannel("Glove"), gd("glove")
{
	// Initialize the raw sensor-hand joint map
	sensorjointmap[TR][0] = GHM::Fingers::thumb; sensorjointmap[TR][1] = GHM::Joints::metacarpal;
	sensorjointmap[TP][0] = GHM::Fingers::thumb; sensorjointmap[TP][1] = GHM::Joints::proximal;
	sensorjointmap[TD][0] = GHM::Fingers::thumb; sensorjointmap[TD][1] = GHM::Joints::distal;	
	sensorjointmap[TIA][0] = GHM::Fingers::thumb; sensorjointmap[TIA][1] = GHM::Joints::abduct;

	sensorjointmap[IM][0] = GHM::Fingers::index; sensorjointmap[IM][1] = GHM::Joints::metacarpal;
	sensorjointmap[IP][0] = GHM::Fingers::index; sensorjointmap[IP][1] = GHM::Joints::proximal;
	sensorjointmap[ID][0] = GHM::Fingers::index; sensorjointmap[ID][1] = GHM::Joints::distal;
	sensorjointmap[NOTUSED][0] = GHM::Fingers::index; sensorjointmap[NOTUSED][1] = GHM::Joints::abduct;

	sensorjointmap[MM][0] = GHM::Fingers::middle; sensorjointmap[MM][1] = GHM::Joints::metacarpal;
	sensorjointmap[MP][0] = GHM::Fingers::middle; sensorjointmap[MP][1] = GHM::Joints::proximal;
	sensorjointmap[MD][0] = GHM::Fingers::middle; sensorjointmap[MD][1] = GHM::Joints::distal;
	sensorjointmap[IMA][0] = GHM::Fingers::middle; sensorjointmap[IMA][1] = GHM::Joints::abduct;

	sensorjointmap[RM][0] = GHM::Fingers::ring; sensorjointmap[RM][1] = GHM::Joints::metacarpal;
	sensorjointmap[RP][0] = GHM::Fingers::ring; sensorjointmap[RP][1] = GHM::Joints::proximal;
	sensorjointmap[RD][0] = GHM::Fingers::ring; sensorjointmap[RD][1] = GHM::Joints::distal;
	sensorjointmap[MRA][0] = GHM::Fingers::ring; sensorjointmap[MRA][1] = GHM::Joints::abduct;

	sensorjointmap[PM][0] = GHM::Fingers::pinky; sensorjointmap[PM][1] = GHM::Joints::metacarpal;
	sensorjointmap[PP][0] = GHM::Fingers::pinky; sensorjointmap[PP][1] = GHM::Joints::proximal;
	sensorjointmap[PD][0] = GHM::Fingers::pinky; sensorjointmap[PD][1] = GHM::Joints::distal;
	sensorjointmap[RPA][0] = GHM::Fingers::pinky; sensorjointmap[RPA][1] = GHM::Joints::abduct;

	sensorjointmap[PA][0] = GHM::HandParts::palm; sensorjointmap[PA][1] = GHM::Joints::palmArch;
	sensorjointmap[WP][0] = GHM::HandParts::palm; sensorjointmap[WP][1] = GHM::Joints::wristFlexion;
	sensorjointmap[WY][0] = GHM::HandParts::palm; sensorjointmap[WY][1] = GHM::Joints::wristAbduction;
}

GloveChannel::~GloveChannel(void)
{
	stop();
}

int GloveChannel::doStart(void)
{
	vhtIOConn *gloveDict;
	//vhtCyberGlove *glove;
	//vhtTracker *tracker;

	try
	{
		// Connect to the glove.
		gloveDict = vhtIOConn::getDefault( vhtIOConn::glove );
		// Expand the CyberGlove connection to the CyberTouch capabilities.
		glove = new vhtCyberGlove(gloveDict);

		assert(glove->getDimensionRange() == NUMSENSORS);

		// Connect to the tracker
		//tracker = new vhtTrackerEmulator();
		//tracker = new VisionEmulator();
	}
	catch (vhtBaseException *e)
	{
		printf("Error starting glove: %s\n", e->getMessage());
		return 0;
	}

	//hand = new vhtHumanHand(glove, tracker);
	//hKin = hand->getKinematics();

	cout << "Glove Channel initialized successfully" << endl;
	return 1;
}

int GloveChannel::doStop()
{
	//vhtGlove *glove = hand->getHandMaster()->getGlove();
	//vhtTracker *tracker = hand->getHandMaster()->getTracker();

	//delete glove;
	//delete tracker;
	//delete hand;

	cout << "Glove channel stopped" << endl;

	return 1;
}

ChannelData* GloveChannel::getLatest()
{
	//hand->update();
	glove->update();

	//vhtHandMaster *hM = hand->getHandMaster();
	//vhtCyberGlove *g = (vhtCyberGlove *)hM->getGlove();
	//vhtTransform3D xform;
	//double matrix[4][4];

	for (int i=0; i<NUMSENSORS; i++) {
		gd.setJointValues(
			i,
			glove->getRawData(i),
			glove->getData(i)
		);

		//xform = hKin->getKinematics(sensorjointmap[i][0], sensorjointmap[i][1]);
		//xform.getTransform(matrix);
		//gd.setTransform(i, matrix);
	}

	setTimestamp(&gd);

	return &gd;
}