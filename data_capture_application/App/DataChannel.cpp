#include "stdafx.h"
#include "DataChannel.h"


ChannelData::ChannelData(string id) 
	: id(id)
{
	hr = min = sec = ms = 0;
}


void ChannelData::setTimeStamp(int hr, int min, int sec, int ms)
{
	this->hr = hr;
	this->min = min;
	this->sec = sec;
	this->ms = ms;
}

DataChannel::~DataChannel(void)
{
}

int DataChannel::start(void)
{
	if (!active && doStart()) {
		active = true;
		return 1;
	}

	return 0;
}

int DataChannel::stop(void)
{
	if (active && doStop()) {
		active = false;
		return 1;
	}

	return 0;
}

void DataChannel::setTimestamp(ChannelData* chd)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	chd->setTimeStamp(st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);	
}