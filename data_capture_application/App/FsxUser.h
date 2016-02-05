/*
 * $Header:   G:/core/msvc/fsxuser/fsxuser.h_v   1.3   Oct 02 2002 16:42:46   FCHEN  $
 *
 * $Log:   G:/core/msvc/fsxuser/fsxuser.h_v  $
 * 
 *    Rev 1.3   Oct 02 2002 16:42:46   FCHEN
 * Added, modified testing routines for new API2 calls.
 * 
 *    Rev 1.2   Jan 25 2002 17:06:22   FCHEN
 * Added OnRTBitmapFileReady().  Added a dialog to display
 * the data transfer rate.
 * 
 *    Rev 1.1   Mar 27 2001 13:29:36   FCHEN
 * Added Request real time image part.
 * 
 *    Rev 1.0   Jan 09 2001 11:51:28   FCHEN
 * Initial revision.
*/

// FsxUser.h : main header file for the FSXUSER application
//

#if !defined(AFX_FSXUSER_H__05194D88_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
#define AFX_FSXUSER_H__05194D88_CA91_11D4_B729_00A0CC56138A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "fsx.h"

interface ICustom;
interface ICallClient;
/////////////////////////////////////////////////////////////////////////////
// CCallBack:
// See FsxUser.cpp for the implementation of this class
//

class CCallClient : public ICallClient
{
public:
	CCallClient();
	~CCallClient();

    //IAdvisSink interface members
    STDMETHODIMP	QueryInterface(REFIID, LPVOID *);
    STDMETHODIMP_(ULONG)	AddRef(void);
    STDMETHODIMP_(ULONG)	Release(void);

	STDMETHODIMP OnRTDataReady(int iRow, int iCol, BYTE* pData);
	STDMETHODIMP OnCalRTDataReady(int iRow, int iCol, float* pfCalData);
	STDMETHODIMP CurRTTerminated(int c_SizeWin, unsigned char* pWindows);

	STDMETHODIMP OnRTBitmapReady(
									int    BMType,
									int    BMWidth,
									int    BMHeight,
									int    BMWidthBytes,
									short	BMPlanes,
									short	BMBitsPixel,
									unsigned char*  pBMBits
								);

	STDMETHODIMP  OnRTBitmapFileReady
		(
			int    bmType,
			int    bmWidth,
			int    bmHeight,
			int    bmWidthBytes,
			short	bmPlanes,
			short	bmBitsPixel,
			short  iNameSize,
			unsigned char*  pFileName
		);
private:
		int m_nRefCount;
};

/////////////////////////////////////////////////////////////////////////////
// CFsxUserApp:
// See FsxUser.cpp for the implementation of this class
//

class CFsxUserApp : public CWinApp
{
public:
	CFsxUserApp();
	void OnMainFrameClose();
	void SetGridData(int iRow, int iCol, BOOL bCalibrated, void *pData);
	void ResCallback() { m_pCallback = NULL; }
	void SetViewBitmap(BITMAP* pBitmap);
	BOOL IsDataCalibrated() { return m_bCalibrated; }
public:
	static CCallClient* m_pCallback;
	CString m_strCurWindowName;
	CString m_strUnitLength;
	CString m_strUnitPressure;

	int m_iRow;
	int m_iCol;
	BYTE* m_pData;
	float* m_pfCalData;
	float m_fPixelX;
	float m_fPixelY;

	BOOL m_bShowBitmap;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsxUserApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFsxUserApp)
	afx_msg void OnAppAbout();
	afx_msg void OnRequestRealTimeData();
	afx_msg void OnGetUnits();
	afx_msg void OnDeactCallback();
	afx_msg void OnStopDataTransfer();
	afx_msg void OnGetPixelSize();
	afx_msg void OnGetFileNames();
	afx_msg void OnShowRealTimeImage();
	afx_msg void OnShowCalData();
	afx_msg void OnCaptureDataRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnSelectWindow();

private:
	void prvShowRealTime(BOOL bCalibrated, BOOL bImage);

private:
	BOOL m_bSetCallBack;
	ICustom* m_CallBackServer;
	BOOL m_bCalibrated;
};

inline CFsxUserApp* GetFsxUserApp(){    return((CFsxUserApp *)AfxGetApp());    }

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSXUSER_H__05194D88_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
