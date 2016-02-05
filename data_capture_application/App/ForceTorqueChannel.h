#pragma once
#include "DataChannel.h"

#define PORT 49152 /* Port the Net F/T always uses */
#define COMMAND 2 /* Command code 2 starts streaming */
#define NUM_SAMPLES 1 /* Will send 1 sample before stopping */
#define INFINITE_SAMPLES 0 /* continue sending data */

/* Typedefs used so integer sizes are more explicit */
typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char byte;
typedef struct response_struct {
	uint32 rdt_sequence;
	uint32 ft_sequence;
	uint32 status;
	int32 FTData[6];
} RESPONSE;

class ForceTorqueData : public ChannelData
{
friend class ForceTorqueChannel;
public:
	ForceTorqueData(string id);
	ForceTorqueData(const ForceTorqueData& td);
	~ForceTorqueData();
	string toString();
	void toBottle(Bottle& b);
	int toBuffer(byte* b);
	void setForceTorque(int32 ftdata[]);
	void setScale(double fscale, double tscale);
	
private:
	double fx, fy, fz, tx, ty, tz;
	double forceScale, torqueScale;
};

class ForceTorqueChannel : public DataChannel
{
protected:
	int doStart();
	int doStop();

public:
	ForceTorqueChannel(string ipaddress);
	~ForceTorqueChannel(void);
	ChannelData* getLatest();

private:
	ForceTorqueData ftdata;

	string ipaddress;
	SOCKET socketHandle;		/* Handle to UDP socket used to communicate with Net F/T. */
	WSADATA wsaData;
	WORD wVersionRequested;
	struct sockaddr_in addr;	/* Address of Net F/T. */
	struct hostent *he;			/* Host entry for Net F/T. */
	byte request[8];			/* The request data sent to the Net F/T. */
	RESPONSE resp;				/* The structured response received from the Net F/T. */
	byte response[36];			/* The raw response data received from the Net F/T. */

	const double counts_per_force;  
	const double counts_per_torque;
};

