#pragma once
#include "fsx.h"

/////////////////////////////////////////////////////////////////////////////
// CCallBack:
// See FsxUser.cpp for the implementation of this class
//

class TekscanClient : public ICallClient
{
public:
	TekscanClient(int row, int col);
	~TekscanClient();

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
	void getLatest(BYTE *dRaw, float *dCal);

private:
		int m_nRefCount;
		BYTE *raw;
		float *cal;
		int row, col;
		HANDLE mutex;
};
