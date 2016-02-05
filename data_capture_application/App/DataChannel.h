#pragma once

#include <string>
#include <ctime>
#include <string>
#include <yarp/os/Bottle.h>

using namespace std;
using namespace yarp::os;

class ChannelData
{
public:
	ChannelData(string id);
	void setTimeStamp(int hr, int min, int sec, int ms);
	virtual string toString() = 0;
	virtual void toBottle(Bottle&) = 0;
	virtual int toBuffer(byte* buf) = 0;

	int hr, min, sec, ms;
	string id;
};

class DataChannel
{	
private:
	bool active;
	bool suppressed;

protected:	
	virtual int doStart() = 0;
	virtual int doStop() = 0;

public:
	DataChannel(string n) : name(n) { active = false; suppressed = false; }
	~DataChannel(void);

	int start();
	int stop();
	void suppress(bool val) { suppressed = val; }
	bool isActive() { return active && !suppressed; }
	void setTimestamp(ChannelData* chd);
	virtual ChannelData* getLatest() = 0;

	string name;
};

