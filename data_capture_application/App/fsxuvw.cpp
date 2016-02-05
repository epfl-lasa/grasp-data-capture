/*
 * $Header:   G:/core/msvc/fsxuser/fsxuvw.cpv   1.5   Apr 03 2009 11:57:52   FChen  $
 *
 * $Log:   G:/core/msvc/fsxuser/fsxuvw.cpv  $
 * 
 *    Rev 1.5   Apr 03 2009 11:57:52   FChen
 * Display the mask pix with -1 for both Raw and calibrated data.
 * 
 *    Rev 1.4   Apr 02 2009 16:21:48   FChen
 * Display 1 if the data is the mask pix.
 * 
 *    Rev 1.3   Oct 02 2002 16:59:28   FCHEN
 * Be able to show the calibrated, float type frame data.
 * 
 *    Rev 1.2   Apr 17 2001 11:59:04   FCHEN
 * Do not copy the bmbits pointer when copying the BITMAP structure.
 * 
 *    Rev 1.1   Mar 27 2001 13:22:58   FCHEN
 * Added drawing the image part.  Eliminate the screen flickering
 * problem.
 * 
 *    Rev 1.0   Jan 09 2001 11:52:10   FCHEN
 * Initial revision.
 * 
*/

// FsxUVw.cpp : implementation of the CFsxUserView class
//

#include "stdafx.h"
#include "Fsxuser.h"
#include "FsxUDoc.h"
#include "FsxUVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFsxUserView

IMPLEMENT_DYNCREATE(CFsxUserView, CView)

BEGIN_MESSAGE_MAP(CFsxUserView, CView)
	//{{AFX_MSG_MAP(CFsxUserView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsxUserView construction/destruction

CFsxUserView::CFsxUserView()
{
	ZeroMemory(&m_structBM, sizeof(BITMAP));
}

CFsxUserView::~CFsxUserView()
{
	delete [] m_structBM.bmBits;
}

BOOL CFsxUserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFsxUserView drawing

void CFsxUserView::OnDraw(CDC* pDC)
{
	prvDrawBitmap(pDC);
}
////////////////////////////////////////////////////////////////////////////////
// According to the menu selection, show either the text data or the image transfered 
// from the server software.  Use the CDC::BitBlt to reduce the screen flashing.
//------------------------------------------------------------------------------
void CFsxUserView::prvDrawBitmap(CDC* pDC)
{
	CRect rect, rectTmp;
	GetClientRect(&rect);
	rectTmp = rect;
	pDC->DPtoLP(&rectTmp);

    CDC dcMem;
	dcMem.CreateCompatibleDC (pDC);

	CBitmap bitmap;
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));

	if(!GetFsxUserApp()->m_bShowBitmap)
	{
		dcMem.SetBkColor(RGB(255,255,255));
		dcMem.SetMapMode (pDC->GetMapMode());
		bitmap.CreateCompatibleBitmap( pDC, rect.Width(), rect.Height());
	}
	else
	{
		dcMem.SetMapMode (pDC->GetMapMode());
		dcMem.FillRect(rectTmp, &brush);

		bitmap.CreateBitmapIndirect(&m_structBM);
		bitmap.SetBitmapBits(m_structBM.bmHeight*m_structBM.bmWidthBytes, m_structBM.bmBits);
	}

	CBitmap* pOldBitmap = dcMem.SelectObject (&bitmap);


	if(!GetFsxUserApp()->m_bShowBitmap)
	{
		dcMem.FillRect(rectTmp, &brush);
		dcMem.SetBkMode(TRANSPARENT);
	}

	if(!GetFsxUserApp()->m_bShowBitmap)
		prvDrawView(&dcMem);

	pDC->BitBlt (0, 0, rectTmp.Width(), rectTmp.Height(), &dcMem, 0, 0, SRCCOPY);		

	dcMem.SelectObject (pOldBitmap);	
}
///////////////////////////////////////////////////////////////////////
// Copy the passed in bitmap and set it to the view
//---------------------------------------------------------------------
BOOL CFsxUserView::SetViewBitmap(BITMAP* pBitmap)
{
	if(!pBitmap) return FALSE;

	const int c_SizeBits = pBitmap->bmHeight*pBitmap->bmWidthBytes;
	
	BYTE* pBits = (BYTE*)m_structBM.bmBits;
	if(pBits == NULL || c_SizeBits != m_structBM.bmHeight*m_structBM.bmWidthBytes)
	{
		delete [] m_structBM.bmBits;
		pBits = new BYTE[c_SizeBits];
	}

	CopyMemory(&m_structBM, pBitmap, sizeof(m_structBM) - sizeof(m_structBM.bmBits));
	CopyMemory(pBits, pBitmap->bmBits, c_SizeBits);
	m_structBM.bmBits = pBits;

	Invalidate();
	return TRUE;
}
//----------------------------------------------------------------------------
// Draw the text part of the passed in data including the unit and pixel size
void CFsxUserView::prvDrawView(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	if(!GetFsxUserApp()->m_bShowBitmap)
	{
		//Two lines for the length and pressure units
		CString strOut = "Length Unit: " + GetFsxUserApp()->m_strUnitLength + "\n";
		strOut += "Pressure Unit: " + GetFsxUserApp()->m_strUnitPressure;
		int iLineH = pDC->DrawText(strOut, rect, DT_LEFT | DT_WORDBREAK );

		//Two lines for sensor pixel sizes
		rect.top += iLineH;
		strOut.Format("Pixel X size: %g inch \nPixel Y size: %g inch", GetFsxUserApp()->m_fPixelX, GetFsxUserApp()->m_fPixelY);
		iLineH = pDC->DrawText(strOut, rect, DT_LEFT | DT_WORDBREAK );

		if(!GetFsxUserApp()->IsDataCalibrated())
		{
			BYTE* pData = GetFsxUserApp()->m_pData;
			if(!pData)
				return;

			char szTemp[10000] = "";
			int nPixValue;
			for(int iRow = 0; iRow < GetFsxUserApp()->m_iRow; ++iRow)
			{
				rect.top += iLineH;
				ZeroMemory(szTemp, sizeof(szTemp));
				for(int iCol = 0; iCol < GetFsxUserApp()->m_iCol; ++iCol)
				{
					nPixValue = *(pData + iRow*GetFsxUserApp()->m_iCol + iCol);
					
					if(nPixValue == 1)
						nPixValue = -1;	

					sprintf(szTemp + strlen(szTemp), "%d,", nPixValue);
				}
				iLineH = pDC->DrawText(szTemp, rect, DT_LEFT | DT_WORDBREAK );
			}
		}
		else
		{
			float* pfCalData = GetFsxUserApp()->m_pfCalData;
			if(!pfCalData)
				return;

			char szTemp[10000] = "";
			float fTemp;
			for(int iRow = 0; iRow < GetFsxUserApp()->m_iRow; ++iRow)
			{
				rect.top += iLineH;
				ZeroMemory(szTemp, sizeof(szTemp));
				for(int iCol = 0; iCol < GetFsxUserApp()->m_iCol; ++iCol)
				{
					fTemp = (float)(*(pfCalData + iRow*GetFsxUserApp()->m_iCol + iCol));
					
					if(fTemp < 0.0f)
						fTemp = -1.0f;

					sprintf(szTemp + strlen(szTemp), "%g,", fTemp );
				}
				
				iLineH = pDC->DrawText(szTemp, rect, DT_LEFT | DT_WORDBREAK );
			}			
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CFsxUserView printing

BOOL CFsxUserView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFsxUserView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFsxUserView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFsxUserView diagnostics

#ifdef _DEBUG
void CFsxUserView::AssertValid() const
{
	CView::AssertValid();
}

void CFsxUserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFsxUserDoc* CFsxUserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFsxUserDoc)));
	return (CFsxUserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFsxUserView message handlers

// Clean up the screen with the white background.  Currently only used when 
// drawing the mage
void CFsxUserView::CleanUp()
{
    CClientDC dc (this);

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	
	dc.SetBkColor(RGB(255,255,255));
	dc.FillRect(rect, &brush);
	dc.SetBkMode(TRANSPARENT);
}
//-----------------------------------------------------------
BOOL CFsxUserView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;	
//	return CView::OnEraseBkgnd(pDC);
}
//---------------------------------------------------------------------
void CFsxUserView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(GetFsxUserApp()->m_bShowBitmap)
		CleanUp();
}
