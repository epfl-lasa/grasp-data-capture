#pragma once

#include "resource.h"
#include "SerialClass.h"

// Structure for the data of the Arduino
struct Data_Arduino_str
{
	char StopInd;
	char Start;
	char Stop;
	
};

union Data_Arduino
{
	Data_Arduino_str Data;
	char Buffer[sizeof(Data_Arduino_str)];
	
};

// DlgCapture dialog

class DlgCapture : public CDialogEx
{
	DECLARE_DYNAMIC(DlgCapture)

public:
	DlgCapture(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgCapture();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetLocation();
	afx_msg void OnBnClickedStartCapture();
	afx_msg void OnBnClickedStopCapture();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedInitSession();
	afx_msg void OnBnClickedCloseSession();
	void DisableLocation();
	afx_msg void OnBnClickedGlove();
	afx_msg void OnBnClickedTrack();
	afx_msg void OnBnClickedTekscan();
	afx_msg void OnBnClickedForcetorque();
	long long GetUnixTime();
};
