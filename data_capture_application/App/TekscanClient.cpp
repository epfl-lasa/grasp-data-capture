#include "stdafx.h"
#include "TekscanClient.h"

TekscanClient::TekscanClient(int r, int c)
	: row(r), col(c)
{
	m_nRefCount = 1;

    mutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

    if (mutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());        
    }

	raw = new BYTE[r*c];
	cal = new float[r*c];

    return;
}

//---------------------------------------------------------------------
//Use as it is.
TekscanClient::~TekscanClient(void)
{
	CloseHandle(mutex);

	delete raw;	
	delete cal;

    return;
}
//---------------------------------------------------------------------
//Use as it is.
STDMETHODIMP TekscanClient::QueryInterface(REFIID riid, LPVOID *ppv)
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
STDMETHODIMP_(ULONG) TekscanClient::AddRef(void)
{
    m_nRefCount ++ ;
    return m_nRefCount ;
}
//---------------------------------------------------------------------
//Use as it is.
STDMETHODIMP_(ULONG) TekscanClient::Release(void)
{
    ULONG ReleaseCount ;

    m_nRefCount -- ;
    ReleaseCount = m_nRefCount ;
	TRACE(TEXT("Reference count inside the TekscanClient::Release %d\n"), ReleaseCount);
    if (m_nRefCount == 0L)
    {   
    	delete this;
    }

    return ReleaseCount ;
}
//---------------------------------------------------------------------
// Server sends back the raw realtime data stored in pData with the sensor
// size (iRow and iCol).  Client may use the sent data at his will.
STDMETHODIMP TekscanClient::OnRTDataReady(int iRow, int iCol, BYTE* pData)
{
	DWORD dwWaitResult; 
	
    dwWaitResult = WaitForSingleObject( 
        mutex,    // handle to mutex
        INFINITE    // no time-out interval
	);

	memcpy(raw, pData, iRow*iCol);

	ReleaseMutex(mutex);

	return S_OK;
}
//--------------------------------------------------------------------------------
// Server sends back the calibrated realtime data stored in a float array pfCalData
// with the sensor size (iRow and iCol).  Client may use the sent data at his will.
STDMETHODIMP TekscanClient::OnCalRTDataReady(int iRow, int iCol, float* pfCalData)
{
	DWORD dwWaitResult; 
	
    dwWaitResult = WaitForSingleObject( 
        mutex,    // handle to mutex
        INFINITE    // no time-out interval
	);

	memcpy(cal, pfCalData, iRow*iCol);

	ReleaseMutex(mutex);

	return S_OK;
}

void TekscanClient::getLatest(BYTE *dRaw, float *dCal)
{
	DWORD dwWaitResult; 
	
    dwWaitResult = WaitForSingleObject( 
        mutex,    // handle to mutex
        INFINITE    // no time-out interval
	);

	memcpy(dRaw, raw, row*col);
	memcpy(dCal, cal, row*col);

	ReleaseMutex(mutex);
}

//--------------------------------------------------------------------------------
//Server is telling this client that the real time window set by the client is
// terminated.
STDMETHODIMP TekscanClient::CurRTTerminated(int c_SizeWin, unsigned char* pWindows)
{
	if(c_SizeWin == 0 || !pWindows)
		return E_FAIL;
	
	return S_OK;
}
//-----------------------------------------------------------------------------------
// Server sends back the image data used for creating a bitmap image.  The created
// bitmap then is set to the view
STDMETHODIMP TekscanClient::OnRTBitmapReady(
											int    BMType,
											int    BMWidth,
											int    BMHeight,
											int    BMWidthBytes,
											short	BMPlanes,
											short	BMBitsPixel,
											unsigned char*  pBMBits
										)
{
	return S_OK;
}
//---------------------------------------------------------------------------
STDMETHODIMP TekscanClient::OnRTBitmapFileReady(
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
	return S_OK;
}