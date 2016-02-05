#include "stdafx.h"
#include "TekscanChannel.h"
#include "assert.h"
#include <sstream>
#include <iostream>

using namespace std;

BOOL EmitFsxViewErrorMessage(HRESULT hr);
void parseWindowList(unsigned char szWindowsList[], unsigned char* windowName[], int sz[], int maxWindows);

//
// Tekscan routines
//
TekscanData::TekscanData(string id, int r, int c)
	: ChannelData(id), row(r), col(c)
{
	draw = new BYTE[r*c];
	dcal = new float[r*c];
}

TekscanData::~TekscanData()
{
	delete draw;
	delete dcal;
}

string TekscanData::toString()
{
	stringstream strm;
	strm << "tekscan" << endl;
	for(int i=0;i<row;i++) {
		for(int j=0;j<col; j++) {
			strm << (int)(draw[i*col + j]) << ' ';
			strm << dcal[i*col + j] << ' ';
		}
		strm << endl;
	}


	//for(int i=0; i<row*col; i++)
	//	strm << rawBottom[i] << ' ';
	//strm << endl;

	//for(int i=0; i<row*col; i++)
	//	strm << rawTop[i] << ' ';
	//strm << endl;

	//for(int i=0; i<row*col; i++)
	//	strm << calBottom[i] << ' ';
	//strm << endl;

	//for(int i=0; i<row*col; i++)
	//	strm << calTop[i] << ' ';
	//strm << endl;

	return string(strm.str());
}

void TekscanData::toBottle(Bottle& b)
{
	b.addString("tekscan");
	Bottle& b1 = b.addList();
	for(int i=0;i<row;i++) 
		for(int j=0;j<col; j++) {
			b1.addDouble(draw[i*col + j]);						
		}
	for(int i=0;i<row;i++) 
		for(int j=0;j<col; j++) {
			b1.addDouble(dcal[i*col + j]);						
		}
}

int TekscanData::toBuffer(byte *b)
{
	int idsz, datasz; 
	long start = (long)b, end;

	idsz = id.length() + 1;
	memcpy((void*)b, (void*)id.c_str(), idsz); b = b + idsz;

	memcpy((void*)b, (void*) &hr, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &min, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &sec, sizeof(int)); b = b+sizeof(int);
	memcpy((void*)b, (void*) &ms, sizeof(int)); b = b+sizeof(int);
	
	//assert(ms < 1000 && sec < 60 && min < 60 && hr < 24);

	int szRaw = row * col * sizeof(BYTE);
	memcpy((void*)b, &szRaw, sizeof(int)); b = b + sizeof(int);
	memcpy((void*)b, (void*)draw, szRaw); b = b + szRaw;

	int szCal = row * col * sizeof(float);
	memcpy((void*)b, &szCal, sizeof(int)); b = b + sizeof(int);
	memcpy((void *)b, (void *)dcal, szCal); b = b + szCal;	

	//int szRaw = row * col * sizeof(int);
	//memcpy((void*)b, &szRaw, sizeof(int)); b = b + sizeof(int);
	//memcpy((void*)b, (void*)draw, szRaw); b = b + szRaw;

	//int szCal = row * col * sizeof(float);
	//memcpy((void*)b, &szCal, sizeof(int)); b = b + sizeof(int);
	//memcpy((void *)b, (void *)dcal, szCal); b = b + szCal;

	end = (long)b;

	return end-start;
}

//
//  Tekscan Channel routines
//
TekscanChannel::TekscanChannel(ICustom* g_CallBackServer)
	: DataChannel("Tekscan"), server(g_CallBackServer)
{
}

TekscanChannel::~TekscanChannel(void)
{
}

int TekscanChannel::doStart()
{
	HRESULT hr = 0;	

	if (server == NULL)
		return 0;

	// retrieve names of the real time windows corresponding to the bottom and top sensors
	unsigned char szWindowsList[2000] = "";
	int iWinNumber = 0;
	int iBufSize = sizeof(szWindowsList);	
	hr = server->GetOpenedWindowNames(&iBufSize, szWindowsList, &iWinNumber, REAL_MOVIE);
	if(!EmitFsxViewErrorMessage(hr) || iWinNumber == 0)
		return 0;	

	unsigned char *windowName[2];
	int sz[2];
	parseWindowList(szWindowsList, windowName, sz, 1);
	strncpy_s(window, (char*)windowName[0], sz[0]); window[sz[0]] = '\0';

	// retrieve the dimensions of the data and create a new data object
	int row, col;
	hr = server->GetWindowMapSize(strlen((char *)windowName[0])+1, (unsigned char *)windowName[0], &row, &col);
	if(!EmitFsxViewErrorMessage(hr))
		return 0;	
	td = new TekscanData("tekscan", row, col);

	/*
	bottom = new TekscanClient(row, col);
	top = new TekscanClient(row, col);
	hr = server->RequestRealTimeData(bottom, strlen(windowBottom) + 1, (unsigned char*)windowBottom, 1);
	if(!EmitFsxViewErrorMessage(hr))
		return 0;	

	hr = server->RequestRealTimeData(top, strlen(windowTop) + 1, (unsigned char*)windowTop, 1);
	if(!EmitFsxViewErrorMessage(hr))
		return 0;	
	*/

	cout << "Tekscan channel initialized successfully" << endl;

	return 1;
}

#define RETURN_NEWLINE "\r\n"
void parseWindowList(unsigned char szWindowsList[], unsigned char* windowName[], int sz[], int maxWindows)
{
	unsigned char *pszBeginPos = szWindowsList;
	unsigned char *pszEndPos = NULL;
	int i = 0;
 
	int iLength = 0;
	while((pszEndPos = (unsigned char *)strpbrk( (char *)pszBeginPos, RETURN_NEWLINE)) != NULL && i < maxWindows)
	{
		iLength = pszEndPos - pszBeginPos;
		if(iLength > 0)
		{
			windowName[i] = pszBeginPos;
			sz[i] = iLength;
		}
 
		pszBeginPos = pszEndPos + 2;

		if(pszBeginPos > szWindowsList + strlen((char *)szWindowsList))
		break;
		i++;
	}
}

int TekscanChannel::doStop()
{
	delete td;
	//bottom->Release();
	//top->Release();

	cout << "Tekscan channel stopped" << endl;
	return 1;
}

template <class T> void fixdata(T *data);
ChannelData* TekscanChannel::getLatest()
{
	HRESULT hr = 0;	
	int sizeData = td->row*td->col;
	
	// raw
	hr = server->GetFrameData(strlen(window) + 1, (unsigned char*)window, FALSE, &sizeData, td->draw);
	if(!EmitFsxViewErrorMessage(hr))
		return NULL;

	// cal
	hr = server->GetCalFrameData(strlen(window) + 1, (unsigned char*)window, FALSE, &sizeData, td->dcal);	
	if(!EmitFsxViewErrorMessage(hr))
		return NULL;

	setTimestamp(td);

	/* if using a client.
	bottom->getLatest(td->rawBottom, td->calBottom);
	top->getLatest(td->rawTop, td->calTop);
	*/

	return td;
}

template <class T> void fixdata(T *data)
{
	for (int i=0; i<23; i++)
		fixrow<T>(&data(i), 51, 6, 25);

	for (int i=23; i<29; i++)
		fixrow<T>(&data(i), 51, 0, 25);
}

template <class T> void fixrow(T *row, int ncol, int padsize, int sensorsize)
{
	T r[col];

	for (int i=0; i<col; i+)
		r[i] = row[i];

	// SENSOR 1
	int s = findStart(row, 0, 24, padsize);
	for (int cnt=0, i=s; cnt < sensorsize; cnt++, i=next(i, 0, 24))
		row[cnt] = r[s];
	
	// SENSOR 2
	int s = findStart(row, 25, 50, padsize+1);
	for (int cnt=0, i=s; cnt < sensorsize; cnt++, i=next(i, 25, 50))
		row[cnt] = r[s];
}

template <class T> int findStart(T *r, int s, int e, int spad)
{
	for (int cnt=0, int pdsz = 0; cnt <= e-s+1 && pdsz < spad; cnt++, i=next(i, s, e))
	{
		if (r[i] == 1)
			pdsz++;
		else
			pdsz = 0;

		cnt++;
	}

	return i;
}

int next(int i, int s, int e)
{
	return (i+1) > e ? s : i+1;
}


