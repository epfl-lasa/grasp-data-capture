#pragma once
#include "DataChannel.h"
#include "fsx.h"
#include "TekscanClient.h"

class TekscanData : public ChannelData
{
friend class TekscanChannel;
public:
	TekscanData(string id, int row, int col);
	~TekscanData();
	string toString();
	void toBottle(Bottle& b);
	int toBuffer(byte* b);

	int nrow() { return row; }
	int ncol() { return col; }
	//BYTE* raw() { return draw; }
	//float* cal() { return dcal; }

private:
	int row, col;
	BYTE *draw;
	float *dcal;
};

class TekscanChannel : public DataChannel
{

protected:
	int doStart();
	int doStop();

public:
	TekscanChannel(ICustom* g_CallBackServer);
	~TekscanChannel(void);
	ChannelData* getLatest();

private:
	ICustom* server;
	char window[200];
	TekscanData *td;
	//TekscanClient *bottom;
	//TekscanClient *top;
};

