// DlgCapture.cpp : implementation file
//

#include "stdafx.h"
#include "DlgCapture.h"
#include "afxdialogex.h"

#include "TekscanChannel.h"
#include "TrackerChannel.h"
#include "GloveChannel.h"
#include "ForceTorqueChannel.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>

#include <Windows.h>

using namespace std;
using namespace yarp::os;

#include "conio.h"

extern ICustom* g_CallBackServer;
DWORD WINAPI StartGraspDataSession( LPVOID );
HRESULT BasicFileOpen(char*);
char dataFile[300];
BOOL recordActive, sessionActive;
Network yarpNetwork;
ofstream outFile;
BufferedPort<Bottle> outPort;
long long currentTime;

// Arduino
Serial Arduino;
Data_Arduino DataArduino;


// DlgCapture dialog
IMPLEMENT_DYNAMIC(DlgCapture, CDialogEx)

DlgCapture::DlgCapture(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgCapture::IDD, pParent)
{

}

DlgCapture::~DlgCapture()
{
}

void DlgCapture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgCapture, CDialogEx)
	ON_BN_CLICKED(IDC_SET_LOCATION, &DlgCapture::OnBnClickedSetLocation)
	ON_BN_CLICKED(IDC_START_CAPTURE, &DlgCapture::OnBnClickedStartCapture)
	ON_BN_CLICKED(IDC_STOP_CAPTURE, &DlgCapture::OnBnClickedStopCapture)
	ON_BN_CLICKED(IDOK, &DlgCapture::OnBnClickedOk)
	ON_BN_CLICKED(IDC_INIT_SESSION, &DlgCapture::OnBnClickedInitSession)
	ON_BN_CLICKED(IDC_CLOSE_SESSION, &DlgCapture::OnBnClickedCloseSession)
	ON_BN_CLICKED(IDC_GLOVE, &DlgCapture::OnBnClickedGlove)
	ON_BN_CLICKED(IDC_TRACK, &DlgCapture::OnBnClickedTrack)
	ON_BN_CLICKED(IDC_TEKSCAN, &DlgCapture::OnBnClickedTekscan)
	ON_BN_CLICKED(IDC_FORCETORQUE, &DlgCapture::OnBnClickedForcetorque)
END_MESSAGE_MAP()


// DlgCapture message handlers
void DlgCapture::OnBnClickedSetLocation()
{
	if (BasicFileOpen(dataFile) == S_OK) {
		if (outFile.is_open())
			outFile.close();

		GetDlgItem(IDC_LOCATION_DISP)->SetWindowTextA(dataFile);

		outFile.open(dataFile, ofstream::out | ofstream::binary);
	}
}

void DlgCapture::OnBnClickedStartCapture()
{
	GetDlgItem(IDC_SET_LOCATION)->EnableWindow(0);
	GetDlgItem(IDC_START_CAPTURE)->EnableWindow(0);
	GetDlgItem(IDC_STOP_CAPTURE)->EnableWindow(1);

	currentTime = GetUnixTime();
	std::stringstream cT;
    cT << currentTime;
	std::string timeString = cT.str();
	outFile << timeString << ' ' << endl;
	outFile.flush();

	recordActive = true;
}


void DlgCapture::OnBnClickedStopCapture()
{
	// Data for the arduino

	DataArduino.Data.Start = 0;
	DataArduino.Data.Stop = 1;
	DataArduino.Data.StopInd = 9;
	Arduino.WriteData(DataArduino.Buffer, sizeof(Data_Arduino_str));

	recordActive = false;

	GetDlgItem(IDC_SET_LOCATION)->EnableWindow(1);
	GetDlgItem(IDC_START_CAPTURE)->EnableWindow(1);
	GetDlgItem(IDC_STOP_CAPTURE)->EnableWindow(0);

	if(outFile.is_open())
		outFile.flush();
}


void DlgCapture::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

DWORD ThreadID;	
HANDLE tH;
void DlgCapture::OnBnClickedInitSession()
{
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);

	// open Serial communication
	if (!Arduino.IsConnected())
		Arduino.OpenSerial("COM2");

	outPort.open("/gloveout1");

	// start the polling thread
	tH = ATL::Win32ThreadTraits::CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) StartGraspDataSession, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID
	); // receive thread identifier

	GetDlgItem(IDC_SET_LOCATION)->EnableWindow(1);
	GetDlgItem(IDC_CLOSE_SESSION)->EnableWindow(1);
	GetDlgItem(IDC_START_CAPTURE)->EnableWindow(1);
	GetDlgItem(IDC_GLOVE)->EnableWindow(1);
	GetDlgItem(IDC_TRACK)->EnableWindow(1);
	GetDlgItem(IDC_TEKSCAN)->EnableWindow(1);
	GetDlgItem(IDC_FORCETORQUE)->EnableWindow(1);
	GetDlgItem(IDC_INIT_SESSION)->EnableWindow(0);

	sessionActive = true;
}

//CFsxUserApp* pApp;
extern DlgCapture m_dlgCapture;
vector<DataChannel*> dch;
DWORD WINAPI StartGraspDataSession( LPVOID )
{
	while (!sessionActive) {
		Sleep(1000);
	}

	// Initialize data channels
	dch.push_back(new TekscanChannel(g_CallBackServer)); 
	dch.push_back(new TrackerChannel("128.178.145.25","128.178.145.172"));
	dch.push_back(new GloveChannel());
	dch.push_back(new ForceTorqueChannel("128.178.145.98")); //128.178.145.98, 128.178.145.212
	//dch.push_back(new ForceTorqueChannel("10.1.1.191"));

	for (int i=0; i<dch.size(); i++) {
		if (!dch[i]->start())
			cout << "Error Starting channel : " << dch[i]->name << endl;
		else
			cout << "Started channel : " << dch[i]->name << endl;
	}

	m_dlgCapture.OnBnClickedGlove();
	m_dlgCapture.OnBnClickedTrack();
	m_dlgCapture.OnBnClickedTekscan();
	m_dlgCapture.OnBnClickedForcetorque();

	cout << "Initialization sequence complete" << endl;

	ChannelData *chd;	
	string s;	
	clock_t start = clock();
	int cnt = 0;

	const int MAXSIZE = 1000000000;
	const int SAFETY = 10000000;
	byte* recordBuffer = (byte*)malloc(MAXSIZE);
	long pos = 0;

	while (sessionActive)
	{
		Sleep(1);

		while (!recordActive && sessionActive)
		{
			if (pos > 0 && outFile.is_open()) 
			{
				outFile.write((const char*)recordBuffer, pos);				
				outFile.flush();				
				memset(recordBuffer, 0, MAXSIZE);
				pos = 0;
			}

			cout << "Diff : " << clock() - start << " cnt : " << cnt << endl;						

			Sleep(1);
			start = clock();
			cnt = 0;
		}

		if (!recordActive)
			continue;
		else {			
			if (cnt == 0) {

				// send the synchronization signal.
					// Data for the arduino
				DataArduino.Data.Start = 1;
				DataArduino.Data.Stop = 0;
				DataArduino.Data.StopInd = 9;
				Arduino.WriteData(DataArduino.Buffer, sizeof(Data_Arduino_str));

			}
		}
	
		//TekscanData *chd	 = (TekscanData *) dch.getLatest();
		//pApp = GetFsxUserApp();

		//if(pApp)
		//	pApp->SetGridData(chd->nrow(), chd->ncol(), FALSE, chd->rawB());					

		Bottle& b = outPort.prepare();
		b.clear();
		//s.clear();

		for (int i=0; i<dch.size(); i++)
		{
			if (!dch[i]->isActive())
				continue;

			chd = dch[i]->getLatest();

			chd->toBottle(b);
			//s.append(chd->toString().c_str());			

			if (pos >= MAXSIZE-SAFETY) {
				printf("Memory Buffer is full !!!");
				continue;
			}

			int size = chd->toBuffer((byte *)recordBuffer + pos);
			//assert(size == 26);
			pos = pos+size;
		}
		
		if (b.size() == 0) 
			continue;

		outPort.write();
		//if (outFile.is_open())
		//	outFile << s;
		//cout << s;

		cnt++;
	}

	free(recordBuffer);

	// shutdown data channels
	for (int i=0; i<dch.size(); i++)
		dch[i]->stop();

	return 0;
}


void DlgCapture::OnBnClickedCloseSession()
{
	cout << "Shutting down grasp data capture session ... " << endl;
	//Arduino.~Serial();

	if (recordActive)
		OnBnClickedStopCapture();

	sessionActive = false;
	WaitForSingleObject(tH, INFINITE);
	CloseHandle(tH);

	DisableLocation();
	outPort.close();
	
	GetDlgItem(IDC_SET_LOCATION)->EnableWindow(0);
	GetDlgItem(IDC_CLOSE_SESSION)->EnableWindow(0);
	GetDlgItem(IDC_GLOVE)->EnableWindow(0);
	GetDlgItem(IDC_TRACK)->EnableWindow(0);
	GetDlgItem(IDC_TEKSCAN)->EnableWindow(0);
	GetDlgItem(IDC_FORCETORQUE)->EnableWindow(0);
	GetDlgItem(IDC_START_CAPTURE)->EnableWindow(0);
	GetDlgItem(IDC_INIT_SESSION)->EnableWindow(1);

	for (int i=0; i<dch.size(); i++)
		delete(dch[i]);
	dch.clear();

	//cout << "Shutdown complete. Press a key to exit";
	//getch();
	FreeConsole();
}

void DlgCapture::DisableLocation()
{
	if (outFile.is_open())
		outFile.close();

	GetDlgItem(IDC_LOCATION_DISP)->SetWindowTextA("No Location Selected");
	GetDlgItem(IDC_SET_LOCATION)->EnableWindow(0);
	GetDlgItem(IDC_START_CAPTURE)->EnableWindow(0);
}

void DlgCapture::OnBnClickedTekscan()
{
	bool allow = IsDlgButtonChecked(IDC_TEKSCAN);
	for (int i=0; i<dch.size(); i++)
		if (dch[i]->name.compare("Tekscan") == 0)
			dch[i]->suppress(!allow);
}

void DlgCapture::OnBnClickedTrack()
{
	bool allow = IsDlgButtonChecked(IDC_TRACK);
	for (int i=0; i<dch.size(); i++)
		if (dch[i]->name.compare("Optitrack") == 0)
			dch[i]->suppress(!allow);
}

void DlgCapture::OnBnClickedGlove()
{
	bool allow = IsDlgButtonChecked(IDC_GLOVE);
	for (int i=0; i<dch.size(); i++)
		if (dch[i]->name.compare("Glove") == 0)
			dch[i]->suppress(!allow);
}



void DlgCapture::OnBnClickedForcetorque()
{
	bool allow = IsDlgButtonChecked(IDC_FORCETORQUE);
	for (int i=0; i<dch.size(); i++)
		if (dch[i]->name.compare("ForceTorque") == 0)
			dch[i]->suppress(!allow);
}

long long DlgCapture::GetUnixTime()
{
    SYSTEMTIME sysUnixEpoch;
    sysUnixEpoch.wYear = 1970;
    sysUnixEpoch.wMonth = 1;
    sysUnixEpoch.wDayOfWeek = 4;
    sysUnixEpoch.wDay = 1;
    sysUnixEpoch.wHour = 0;
    sysUnixEpoch.wMinute = 0;
    sysUnixEpoch.wSecond = 0;
    sysUnixEpoch.wMilliseconds = 0;

    FILETIME unixEpoch;
    SystemTimeToFileTime(&sysUnixEpoch, &unixEpoch);

    ULARGE_INTEGER unixEpochValue;
    unixEpochValue.HighPart = unixEpoch.dwHighDateTime;
    unixEpochValue.LowPart = unixEpoch.dwLowDateTime;

    FILETIME systemTime;
    GetSystemTimeAsFileTime(&systemTime);

    ULARGE_INTEGER systemTimeValue;
    systemTimeValue.HighPart = systemTime.dwHighDateTime;
    systemTimeValue.LowPart = systemTime.dwLowDateTime;

    long long diffHundredNanos = systemTimeValue.QuadPart - unixEpochValue.QuadPart;
    return diffHundredNanos / 10000;
}
