/*
 * $Header:   G:/core/msvc/fsxuser/fsxuser.cpv   1.5   Oct 02 2002 16:42:04   FCHEN  $
 *
 * $Log:   G:/core/msvc/fsxuser/fsxuser.cpv  $
 * 
 *    Rev 1.5   Oct 02 2002 16:42:04   FCHEN
 * Added, modified testing routines for new API2 calls.
 * 
 *    Rev 1.4   Jan 25 2002 17:04:42   FCHEN
 * Added OnRTBitmapFileReady().  Added a dialog to display
 * the data transfer rate.
 * 
 *    Rev 1.3   Apr 16 2001 17:09:58   FCHEN
 * Test for the window name's validity.
 * 
 *    Rev 1.2   Apr 13 2001 14:42:14   FCHEN
 * GetSnapShotFiles() -> GetWindowSnapShotInfo().
 * 
 *    Rev 1.1   Mar 27 2001 13:28:52   FCHEN
 * Added Request real time image part.  Some clean up and re-organization.
 * 
 *    Rev 1.0   Jan 09 2001 11:51:28   FCHEN
 * Initial revision.
 * 
*/

// FsxUser.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "objbase.h"
#include "resource.h"
#include "DlgInfo.h"
#include "FsxUser.h"
#include "dlgwin.h"
#include "DlgCapture.h"
#include "MainFrm.h"
#include "FsxUDoc.h"
#include "FsxUVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RETURN_NEWLINE "\r\n"

ICustom* g_CallBackServer = NULL;
ICustom* g_remoteCallBackServer = NULL;
CInforDialog m_dlgInfo;
DlgCapture m_dlgCapture;

BOOL EmitErrorMessage(HRESULT hr)
{
	if(SUCCEEDED(hr)) return TRUE;

	void* pMsgBuf ;

	::FormatMessage( 
	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	NULL,
	hr,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	(LPTSTR)&pMsgBuf,
	0,
	NULL 
		) ;

	char buf[256] ;
	sprintf(buf, TEXT("Error (%x): %s"), hr, (char*)pMsgBuf);


	MessageBox(NULL, buf, "", 0);
	
	return FALSE;
}

BOOL EmitFsxViewErrorMessage(HRESULT hr)
{
	if(hr == S_OK) return TRUE;

	if(!g_CallBackServer)
		return FALSE;

	char szBuffer[256] = "";
	int cSize = sizeof(szBuffer);
	g_CallBackServer->GetErrorMessage(hr, &cSize, (unsigned char*)szBuffer);
	AfxMessageBox(szBuffer);

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CFsxUserApp

BEGIN_MESSAGE_MAP(CFsxUserApp, CWinApp)
	//{{AFX_MSG_MAP(CFsxUserApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_SET_CALLBACK, OnRequestRealTimeData)
	ON_COMMAND(IDM_GET_UNITS, OnGetUnits)
	ON_COMMAND(IDM_DEACT_CALLBACK, OnDeactCallback)
	ON_COMMAND(IDM_STOP_DATA_TRANSFER, OnStopDataTransfer)
	ON_COMMAND(IDM_GET_PIXEL_SIZE, OnGetPixelSize)
	ON_COMMAND(IDM_GET_FILE_NAMES, OnGetFileNames)
	ON_COMMAND(IDM_SHOW_RT_IMAGE, OnShowRealTimeImage)
	ON_COMMAND(IDM_SHOW_CAL_DATA, OnShowCalData)
	ON_COMMAND(ID_ACTION_CAPTUREDATARECORD, OnCaptureDataRecord)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsxUserApp construction

CCallClient*	CFsxUserApp::m_pCallback = NULL;

CFsxUserApp::CFsxUserApp()
			:m_bSetCallBack(FALSE)
			,m_iRow(0)
			,m_iCol(0)
			,m_pData(NULL)
			,m_fPixelX(0.0f)
			,m_fPixelY(0.0f)
			,m_bShowBitmap(FALSE)
			,m_pfCalData(NULL)
{}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFsxUserApp object

CFsxUserApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFsxUserApp initialization

BOOL CFsxUserApp::InitInstance()
{
	HANDLE hMod = GetModuleHandle ("ole32.dll") ;


	typedef HRESULT (WINAPI *MYPTR)(void *, DWORD);
	HRESULT hr;

	
	//Initialize COM.  Use CoInitializeEx with multithread, if not, use CoInitialize instead.
	MYPTR fpCoInitializeEx = (MYPTR) GetProcAddress ((HINSTANCE)hMod, "CoInitializeEx") ;

	
	if (fpCoInitializeEx == NULL)
	{
		MessageBox (NULL, "This version of the operating system does not support\
			the free threading model.\nThe NewBalance method in this client wouldn't work", "Error", MB_OK) ;

		CoInitialize(NULL);	
		return FALSE ;
	}
	else
		hr = fpCoInitializeEx (NULL, COINIT_MULTITHREADED);

	

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFsxUserDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFsxUserView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	
	//Create the COM object first
	CLSID clsid;
	hr = CLSIDFromProgID(L"FsxView.FsxCom", &clsid);

	if(!g_CallBackServer)
	{
		hr = CoCreateInstance (
		clsid,
		NULL,
		//CLSCTX_LOCAL_SERVER,
		CLSCTX_ALL,  // for 64 bit mode
		IID_ICustom, 
		(void **) &g_CallBackServer);
	}
	

	m_dlgInfo.Create(IDD_INFO);
	m_dlgInfo.ShowWindow(SW_SHOW);	

	EmitErrorMessage(hr);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFsxUserApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////
// CCallClient for callback method from server
// In order for the client to use this set of APIs, the client must implement 
// interface ICallClient, you can use the class CCallClient directly.  Or use 
// as it is.

CCallClient::CCallClient()

{
	m_nRefCount = 1;
    return;
}
//---------------------------------------------------------------------
//Use as it is.
CCallClient::~CCallClient(void)
{
    return;
}
//---------------------------------------------------------------------
//Use as it is.
STDMETHODIMP CCallClient::QueryInterface(REFIID riid, LPVOID *ppv)
{
    if (IsEqualIID(riid, IID_IUnknown)
        || IsEqualIID(riid, IID_ICallClient))
    {
		*ppv = (LPVOID)this;
        AddRef();

        return S_OK ;
    }
    else
    {
    	*ppv = NULL;       
    	return  ResultFromScode(E_NOINTERFACE) ;
    }
}
//---------------------------------------------------------------------
//Use as it is.
STDMETHODIMP_(ULONG) CCallClient::AddRef(void)
{
    m_nRefCount ++ ;
    return m_nRefCount ;
}
//---------------------------------------------------------------------
//Use as it is.
STDMETHODIMP_(ULONG) CCallClient::Release(void)
{
    ULONG ReleaseCount ;

    m_nRefCount -- ;
    ReleaseCount = m_nRefCount ;
	TRACE(TEXT("Reference count inside the CCallClient::Release %d\n"), ReleaseCount);
    if (m_nRefCount == 0L)
    {   
    	delete this;
		GetFsxUserApp()->ResCallback();
    }

    return ReleaseCount ;
}
//---------------------------------------------------------------------
// Server sends back the raw realtime data stored in pData with the sensor
// size (iRow and iCol).  Client may use the sent data at his will.
STDMETHODIMP CCallClient::OnRTDataReady(int iRow, int iCol, BYTE* pData)
{
	CFsxUserApp* pApp = GetFsxUserApp();

	if(pApp)
		pApp->SetGridData(iRow, iCol, FALSE, pData);

	return S_OK;
}
//--------------------------------------------------------------------------------
// Server sends back the calibrated realtime data stored in a float array pfCalData
// with the sensor size (iRow and iCol).  Client may use the sent data at his will.
STDMETHODIMP CCallClient::OnCalRTDataReady(int iRow, int iCol, float* pfCalData)
{
	CFsxUserApp* pApp = GetFsxUserApp();

	if(pApp)
		pApp->SetGridData(iRow, iCol, TRUE, pfCalData);

	return S_OK;
}
//--------------------------------------------------------------------------------
//Server is telling this client that the real time window set by the client is
// terminated.
STDMETHODIMP CCallClient::CurRTTerminated(int c_SizeWin, unsigned char* pWindows)
{
	if(c_SizeWin == 0 || !pWindows)
		return E_FAIL;
	
	CFsxUserApp* pApp = GetFsxUserApp();
	pApp->m_strCurWindowName = "";
	pApp->m_iRow = pApp->m_iCol = 0;

	return S_OK;
}
//-----------------------------------------------------------------------------------
// Server sends back the image data used for creating a bitmap image.  The created
// bitmap then is set to the view
STDMETHODIMP CCallClient::OnRTBitmapReady(
											int    BMType,
											int    BMWidth,
											int    BMHeight,
											int    BMWidthBytes,
											short	BMPlanes,
											short	BMBitsPixel,
											unsigned char*  pBMBits
										)
{
	CFsxUserApp* pApp = GetFsxUserApp();
	
	//Will not report even if nothing has been done
	if(!pApp) return S_OK;

	BITMAP Bitmap = {
						BMType,
						BMWidth,
						BMHeight,
						BMWidthBytes,
						BMPlanes,
						BMBitsPixel,
						pBMBits	
					};
	
	pApp->SetViewBitmap(&Bitmap);

	return S_OK;
}
//---------------------------------------------------------------------------
STDMETHODIMP CCallClient::OnRTBitmapFileReady(
												int    BMType,
												int    BMWidth,
												int    BMHeight,
												int    BMWidthBytes,
												short	BMPlanes,
												short	BMBitsPixel,
												short  iNameSize,
												unsigned char*  pFileName
											)
{
	CFsxUserApp* pApp = GetFsxUserApp();
	
	if(!pApp) return S_OK;

	if(pFileName)
	{
		HANDLE hMappedFile = NULL;
		const int cnSize = BMHeight * BMWidthBytes;
		LPSTR lpMappedStr = NULL;
		hMappedFile = ::CreateFileMapping((HANDLE)0xFFFFFFFF, NULL,
													PAGE_READONLY, 0, cnSize, (char*)pFileName);	


		lpMappedStr = (LPSTR)::MapViewOfFile(hMappedFile, FILE_MAP_READ, 0, 0, cnSize);
		if(lpMappedStr)
		{
			BITMAP Bitmap = {
								BMType,
								BMWidth,
								BMHeight,
								BMWidthBytes,
								BMPlanes,
								BMBitsPixel,
								lpMappedStr	
							};

			pApp->SetViewBitmap(&Bitmap);
		}
		else
		{
			HRESULT hr = GetLastError();
			EmitErrorMessage(hr);

			if(SUCCEEDED(hr) != S_OK)
				return hr;
		
		}
		
		if(hMappedFile)
			::UnmapViewOfFile(lpMappedStr);
	}
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////
// CFsxUserApp message handlers

void CFsxUserApp::OnShowRealTimeImage() 
{
	prvShowRealTime(FALSE, TRUE /* Image */);
}
//--------------------------------------------------------------------------------------
void CFsxUserApp::OnRequestRealTimeData()
{
	prvShowRealTime(FALSE, /*not calibrated*/ FALSE /* Data in text format */);
	m_bCalibrated = FALSE;
}
//--------------------------------------------------------------------------------------
void CFsxUserApp::OnShowCalData() 
{
	prvShowRealTime(TRUE /* calibrated */, FALSE /*text instead of image*/);
	m_bCalibrated = TRUE;
}

void CFsxUserApp::OnCaptureDataRecord()
{
	if (m_dlgCapture.m_hWnd == NULL)
		m_dlgCapture.Create(IDD_DIALOG1);
	m_dlgCapture.ShowWindow(SW_SHOW);
}

//--------------------------------------------------------------------------------------
// Request the server to transfer back the real time data in either data or image format.
// For the form of text data, it has to differentiate whether it is requesting calibrated
// or not.  For the calibrated data request, get the pressure unit at the same time.
// Create a callback pointer if it does not exist and pass it to the server for calling 
// back location.
void CFsxUserApp::prvShowRealTime(BOOL bCalibrated, BOOL bImage)
{
	if(!g_CallBackServer)
		return;

	HRESULT hr = 0;
	
	//Select server's realtime window
	if(!m_strCurWindowName.IsEmpty())
		OnDeactCallback();

	OnSelectWindow();

	if(m_strCurWindowName.IsEmpty()) return;

	char uszName[200] = "";
	strcpy(uszName, m_strCurWindowName);

	if(!m_pCallback)
		m_pCallback = new CCallClient;

	if(bImage)
		hr = g_CallBackServer->RequestRealTimeImage(m_pCallback, strlen(uszName) + 1, (unsigned char*)uszName);
	else
	{
		//Get the calibrated data and unit
		if(bCalibrated)
		{
			hr = g_CallBackServer->RequestCalRealTimeData(m_pCallback, strlen(uszName) + 1, (unsigned char*)uszName, 1);
			OnGetUnits();
		}
		else
			hr = g_CallBackServer->RequestRealTimeData(m_pCallback, strlen(uszName) + 1, (unsigned char*)uszName, 1);
	}
	if(!EmitFsxViewErrorMessage(hr))
		return;

	else if(!m_bSetCallBack)
	{
		m_bSetCallBack = TRUE;
		m_pCallback->Release();
	}
}
//---------------------------------------------------------------------
// Remove the callback connection from the server, etc.
void CFsxUserApp::OnDeactCallback()
{
	if(!g_CallBackServer || m_strCurWindowName.IsEmpty())
		return;
	
	char uszName[200] = "";
	strcpy(uszName, m_strCurWindowName);

	HRESULT hr = g_CallBackServer->DeactivateCallback(strlen(uszName) + 1, (unsigned char*)uszName);

	m_strCurWindowName = "";

	EmitFsxViewErrorMessage(hr);
}
//---------------------------------------------------------------------
// Inform the server to stop sending back the realtime data, but keep the 
// callback connection
void CFsxUserApp::OnStopDataTransfer() 
{
	if(!g_CallBackServer || m_strCurWindowName.IsEmpty())
		return;
	
	char uszName[200] = "";
	strcpy(uszName, m_strCurWindowName);

	HRESULT hr = g_CallBackServer->StopCallbackTransfer(strlen(uszName) + 1, (unsigned char*)uszName);
	EmitFsxViewErrorMessage(hr);
}
//---------------------------------------------------------------------
int CFsxUserApp::ExitInstance() 
{
	if(m_pData)
		delete [] m_pData;

	if(m_pfCalData)
		delete [] m_pfCalData;

	::CoUninitialize ( );

	if(m_dlgInfo.m_hWnd)
		m_dlgInfo.DestroyWindow();

	return CWinApp::ExitInstance();
}
//---------------------------------------------------------------------
// MainFrame is closing, release the Server object
void CFsxUserApp::OnMainFrameClose()
{
	if(g_CallBackServer)
	{
		OnDeactCallback();
		g_CallBackServer->Release();
	}
}
//---------------------------------------------------------------------
// Get all the realtime windows from the server, and select one 
// for this client
void CFsxUserApp::OnSelectWindow()
{
	if(!g_CallBackServer)
		return;

	HRESULT hr = 0;	

	char szWindowsList[2000] = "";
	int iWinNumber = 0;
	int iBufSize = sizeof(szWindowsList);
	
	hr = g_CallBackServer->GetOpenedWindowNames(&iBufSize, (BYTE*)szWindowsList, &iWinNumber, REAL_MOVIE);

	if(!EmitFsxViewErrorMessage(hr))
	return;

	CGetWindowsList dlgWindowList(szWindowsList);
	if(dlgWindowList.DoModal() == IDOK)
		m_strCurWindowName = dlgWindowList.GetCurrentWindowName();

}
//-----------------------------------------------------------------------
// Get the length and pressure units in one trip, the units are stored
// in the out string and seperated by "\r\n".
void CFsxUserApp::OnGetUnits() 
{
	if(!g_CallBackServer)
		return;

	if(m_strCurWindowName.IsEmpty())
		OnSelectWindow();

	if(m_strCurWindowName.IsEmpty()) return;

	HRESULT hr = 0;	
	char szLengthPressUnits[2000] = "";	
	char szCurWindow[200] = "";
	int iBufSize = sizeof(szLengthPressUnits);
	strcpy(szCurWindow, m_strCurWindowName);
	hr = g_CallBackServer->GetCurrentSizePresssureUnits(strlen(szCurWindow) + 1, (unsigned char*)szCurWindow, &iBufSize, (unsigned char*)szLengthPressUnits);

	char szUnit[100] = "";
	char *pszBeginPos = szLengthPressUnits;
	char *pszEndPos = NULL;
	CString *astrUnits[2] = {&m_strUnitLength, &m_strUnitPressure};
	
	int iLength = 0;
	int iCount = 0;
	while((pszEndPos = strpbrk( pszBeginPos, RETURN_NEWLINE)) != NULL)
	{
		iLength = pszEndPos - pszBeginPos;
		if(iLength > 0)
		{
			strncpy(szUnit, pszBeginPos, iLength);
			*astrUnits[iCount++] = szUnit;
			ZeroMemory(szUnit, sizeof(szUnit));
		}
		
		pszBeginPos = pszEndPos + 2;

		if(pszBeginPos > szLengthPressUnits + strlen(szLengthPressUnits))
			break;
	}

	if(!EmitFsxViewErrorMessage(hr))
	return;

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CFsxUserView* pView = (CFsxUserView*)pFrame->GetActiveView();
	if(pView)
		pView->Invalidate();
}
//--------------------------------------------------------------------------
// This is called by the callback interface and pass the grid data from the 
// server.  Here the grid data is copied and set it up to the view
void CFsxUserApp::SetGridData(int iRow, int iCol, BOOL bCalibrated, void *pData)
{
	ASSERT(iRow > 0 && iCol > 0);

	static int c_statStartTime = ::GetTickCount();
	static int c_statCurrentTime;
	
	static int c_nCount = 0;
	c_statCurrentTime = ::GetTickCount();
	++c_nCount;

	if(m_dlgInfo.m_hWnd && (c_statCurrentTime - c_statStartTime >= 2000))
	{
		double dElapsedTime = (c_statCurrentTime - c_statStartTime)/1000.f;
		float fSpeed = (float)(c_nCount/dElapsedTime);
		
		CString strMessage;
		strMessage.Format("%.3f frames/sec", fSpeed);
		m_dlgInfo.SetInfoText(strMessage);

		c_nCount = 0;
		c_statCurrentTime = ::GetTickCount();
		c_statStartTime = c_statCurrentTime;
	}

	m_bShowBitmap = FALSE;	
	if((bCalibrated && m_pfCalData == NULL) || (!bCalibrated && m_pData == NULL) || m_iRow != iRow || m_iCol != iCol)
	{
		m_iRow = iRow;
		m_iCol = iCol;

		if(!bCalibrated)
		{
			if(m_pData)
				delete [] m_pData;
			
			m_pData = new BYTE[m_iRow * m_iCol];
		}
		else
		{
			if(m_pfCalData)
				delete [] m_pfCalData;
			
			m_pfCalData = new float[m_iRow * m_iCol];		
		}
	}

	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
	CFsxUserView* pView = (CFsxUserView*)pFrame->GetActiveView();

	if(!bCalibrated && m_pData)
		CopyMemory(m_pData, pData, m_iRow*m_iCol);
	else if(bCalibrated && m_pfCalData)
		CopyMemory(m_pfCalData, pData, sizeof(float)*m_iRow*m_iCol);

	if(pView)
		pView->Invalidate();
}
//---------------------------------------------------------------------------
// This is called by the callback interface and pass in image bitmap from the 
// server.  The image is then copied and set it up to the view
void CFsxUserApp::SetViewBitmap(BITMAP* pBitmap)
{
	static int c_statStartTime = ::GetTickCount();
	static int c_statCurrentTime;
	
	static int c_nCount = 0;
	c_statCurrentTime = ::GetTickCount();
	++c_nCount;

	if(m_dlgInfo.m_hWnd && (c_statCurrentTime - c_statStartTime >= 2000))
	{
		double dElapsedTime = (c_statCurrentTime - c_statStartTime)/1000.f;
		float fSpeed = (float)(c_nCount/dElapsedTime);
		
		CString strMessage;
		strMessage.Format("%.3f frames/sec", fSpeed);
		m_dlgInfo.SetInfoText(strMessage);

		c_nCount = 0;
		c_statCurrentTime = ::GetTickCount();
		c_statStartTime = c_statCurrentTime;
	}

	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
	CFsxUserView* pView = (CFsxUserView*)pFrame->GetActiveView();
	
	if(pView)
	{
		if(!m_bShowBitmap)
			pView->CleanUp();
		
		m_bShowBitmap = TRUE;
		pView->SetViewBitmap(pBitmap);
	}
}
//---------------------------------------------------------------------------
void CFsxUserApp::OnGetPixelSize() 
{
	if(!g_CallBackServer)
		return;

	if(m_strCurWindowName.IsEmpty())
		OnSelectWindow();

	if(m_strCurWindowName.IsEmpty()) return;

	HRESULT hr = 0;	
	char szLengthPressUnits[2000] = "";	
	char szCurWindow[200] = "";
	strcpy(szCurWindow, m_strCurWindowName);
	hr = g_CallBackServer->GetWindowPixelSize(	strlen(szCurWindow) + 1,
												(unsigned char*)szCurWindow,
												&m_fPixelX, &m_fPixelY);

	if(!EmitFsxViewErrorMessage(hr))
	return;

	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CFsxUserView* pView = (CFsxUserView*)pFrame->GetActiveView();
	if(pView)
		pView->Invalidate();
}
//---------------------------------------------------------------------------
void CFsxUserApp::OnGetFileNames() 
{
	if(!g_CallBackServer)
		return;

	if(m_strCurWindowName.IsEmpty())
		OnSelectWindow();

	if(m_strCurWindowName.IsEmpty()) return;

	char szCurWindow[200] = "";
	strcpy(szCurWindow, m_strCurWindowName);

	char sz2dViewFileName[100] = "";
	char sz2dCtViewFileName[100] = "";
	char sz3dViewFileName[100] = "";
	char szLegendFileName[100] = "";
	char szASCIIFileName[100] = "";

	float fArea;
	float fForce;
	float fMinPress;
	float fMaxPress;
	HRESULT hr = 0;	

	hr = g_CallBackServer->GetWindowSnapShotInfo	(strlen(szCurWindow) + 1,
												(unsigned char*)szCurWindow,
												sizeof(sz2dViewFileName),
												(unsigned char*)sz2dViewFileName,
												sizeof(sz2dCtViewFileName),
												(unsigned char*)sz2dCtViewFileName,
												sizeof(sz3dViewFileName),
												(unsigned char*) sz3dViewFileName,
												sizeof(szLegendFileName),
												(unsigned char*)szLegendFileName,
												&fArea,
												&fForce,
												&fMinPress,
												&fMaxPress,
												JPG,
												sizeof(szASCIIFileName),
												(unsigned char*)szASCIIFileName);


	EmitFsxViewErrorMessage(hr);

	ShellExecute(AfxGetMainWnd()->m_hWnd, "open", sz2dViewFileName, NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(AfxGetMainWnd()->m_hWnd, "open", sz2dCtViewFileName, NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(AfxGetMainWnd()->m_hWnd, "open", sz3dViewFileName, NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(AfxGetMainWnd()->m_hWnd, "open", szLegendFileName, NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(AfxGetMainWnd()->m_hWnd, "open", szASCIIFileName, NULL, NULL, SW_SHOWNORMAL);

}