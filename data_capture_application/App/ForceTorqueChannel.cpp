#include "stdafx.h"
#include "ForceTorqueChannel.h"
using namespace std;

#include <iostream>
#include <sstream>
#include <assert.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//
// Tracker Data routines
//
ForceTorqueData::ForceTorqueData(string id)
	: ChannelData(id)
{
}

ForceTorqueData::~ForceTorqueData()
{
}

ForceTorqueData::ForceTorqueData(const ForceTorqueData& td)
	: ChannelData(td.id)
{
	assert(0);
}

void ForceTorqueData::setForceTorque(int32 ftdata[])
{
	fx = ftdata[0]*forceScale;
	fy = ftdata[1]*forceScale;
	fz = ftdata[2]*forceScale;
	tx = ftdata[3]*torqueScale;
	ty = ftdata[4]*torqueScale;
	tz = ftdata[5]*torqueScale;
}

void ForceTorqueData::setScale(double fScale, double tScale)
{
	forceScale = fScale;
	torqueScale = tScale;
}

string ForceTorqueData::toString()
{
	stringstream strm;

	strm << id << endl;
	strm << fx << ' ' << fy << ' ' << fz << ' ' << tx << ' ' << ty << ' ' << tz << endl;

	return string(strm.str());
}

void ForceTorqueData::toBottle(Bottle& b)
{
	b.addString(id.c_str());
	Bottle& b1 = b.addList();
	b1.addDouble(fx);
	b1.addDouble(fy);
	b1.addDouble(fz);
	b1.addDouble(tx);
	b1.addDouble(ty);
	b1.addDouble(tz);
}

int ForceTorqueData::toBuffer(byte *b)
{
	int idsz;
	long start = (long)b, end;

	idsz = id.length() + 1;
	memcpy((void*)b, (void*)id.c_str(), idsz); b = b + idsz;

	memcpy((void*)b, (void*) &hr, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &min, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &sec, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &ms, sizeof(int)); b = b+sizeof(int);

	int ftsz = sizeof(double)*6;
	memcpy((void*)b, &ftsz, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, &fx, sizeof(double)); b = b+sizeof(double);
	memcpy((void*)b, &fy, sizeof(double)); b = b+sizeof(double);
	memcpy((void*)b, &fz, sizeof(double)); b = b+sizeof(double);
	memcpy((void*)b, &tx, sizeof(double)); b = b+sizeof(double);
	memcpy((void*)b, &ty, sizeof(double)); b = b+sizeof(double);
	memcpy((void*)b, &tz, sizeof(double)); b = b+sizeof(double);

	end = (long)b;

	return end-start;
}

//
//  ForceTorqueChannel routines
//
ForceTorqueChannel::ForceTorqueChannel(string ipadd)
	: DataChannel("ForceTorque"), counts_per_force(1000000), counts_per_torque(1000000), ftdata("forcetorque")
{
	ipaddress = ipadd;
	ftdata.setScale(1/counts_per_force, 1/counts_per_torque);
}

ForceTorqueChannel::~ForceTorqueChannel(void)
{
	stop();
}

int ForceTorqueChannel::doStart(void)
{
	int err;

	/* Calculate number of samples, command code, and open socket here. */
	socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketHandle == -1) {
		fprintf(stderr, "Socket could not be opened.\n");
		return 0;
	}
	
	*(uint16*)&request[0] = htons(0x1234); /* standard header. */
	*(uint16*)&request[2] = htons(COMMAND); /* per table 9.1 in Net F/T user manual. */
	*(uint32*)&request[4] = htonl(INFINITE_SAMPLES); /* see section 9.1 in Net F/T user manual. */
	
	/* Sending the request. */
	he = gethostbyname(ipaddress.c_str());
	memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	
	err = connect( socketHandle, (struct sockaddr *)&addr, sizeof(addr) );
	if (err == -1) {
		fprintf(stderr, "Error Connecting to Net F/T box. \n");
		return 0;
	}
	send( socketHandle, (const char *)request, 8, 0 );
		
	// Ready to receive force torque data stream
	printf("\nForce Torque channel is connect and listening for data ... \n");
	return 1;
}

int ForceTorqueChannel::doStop(void)
{
	closesocket(socketHandle);

	cout << "Force Torque channel stopped" << endl;
	return 1;
}

ChannelData* ForceTorqueChannel::getLatest()
{
	/* Receiving the response. */
	recv( socketHandle, (char *)response, 36, 0 );
	resp.rdt_sequence = ntohl(*(uint32*)&response[0]);
	resp.ft_sequence = ntohl(*(uint32*)&response[4]);
	resp.status = ntohl(*(uint32*)&response[8]);
	for(int i = 0; i < 6; i++ ) {
		resp.FTData[i] = ntohl(*(int32*)&response[12 + i * 4]);
	}

	ftdata.setForceTorque(resp.FTData);
	setTimestamp(&ftdata);

	return &ftdata;
}

