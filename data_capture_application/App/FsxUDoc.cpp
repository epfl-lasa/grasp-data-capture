/*
 * $Header:   G:/CORE/MSVC/FSXUSER/FsxUDoc.cpv   1.0   Jan 09 2001 11:50:50   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/FsxUDoc.cpv  $
 * 
 *    Rev 1.0   Jan 09 2001 11:50:50   FCHEN
 * Initial revision.
 * 
*/

// FsxUDoc.cpp : implementation of the CFsxUserDoc class
//

#include "stdafx.h"
#include "fsx.h"
#include "FsxUser.h"

#include "FsxUDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFsxUserDoc

IMPLEMENT_DYNCREATE(CFsxUserDoc, CDocument)

BEGIN_MESSAGE_MAP(CFsxUserDoc, CDocument)
	//{{AFX_MSG_MAP(CFsxUserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsxUserDoc construction/destruction

CFsxUserDoc::CFsxUserDoc()
{
	// TODO: add one-time construction code here

}

CFsxUserDoc::~CFsxUserDoc()
{
}

BOOL CFsxUserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFsxUserDoc serialization

void CFsxUserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFsxUserDoc diagnostics

#ifdef _DEBUG
void CFsxUserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFsxUserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFsxUserDoc commands
