/*
 * $Header:   G:/CORE/MSVC/FsxUser/dlginfo.cpv   1.0   Jan 25 2002 17:10:10   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FsxUser/dlginfo.cpv  $
   
      Rev 1.0   Jan 25 2002 17:10:10   FCHEN
   Initial revision.
*/

// DlgInfo.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInforDialog dialog


CInforDialog::CInforDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInforDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInforDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInforDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInforDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInforDialog, CDialog)
	//{{AFX_MSG_MAP(CInforDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInforDialog message handlers
void CInforDialog::SetInfoText(CString strMessage)
{
	GetDlgItem(IDC_MESSAGE)->SetWindowText(strMessage);
}

void CInforDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
