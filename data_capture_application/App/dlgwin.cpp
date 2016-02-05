/*
 * $Header:   G:/CORE/MSVC/FSXUSER/dlgwin.cpv   1.1   Mar 27 2001 13:21:50   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/dlgwin.cpv  $
 * 
 *    Rev 1.1   Mar 27 2001 13:21:50   FCHEN
 * If only one real time window, do not open the dialog.
 * 
 *    Rev 1.0   Jan 09 2001 11:50:18   FCHEN
 * Initial revision.
*/

// DlgWin.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RETURN_NEWLINE "\r\n"

/////////////////////////////////////////////////////////////////////////////
// CGetWindowsList dialog


CGetWindowsList::CGetWindowsList(LPSTR lpWindowsNames, CWnd* pParent /*=NULL*/)
	: CDialog(CGetWindowsList::IDD, pParent)
	,m_lpWindowsNames(lpWindowsNames)
{
	//{{AFX_DATA_INIT(CGetWindowsList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CGetWindowsList, CDialog)
	//{{AFX_MSG_MAP(CGetWindowsList)
	ON_CBN_SELCHANGE(IDC_COM_WIN_LIST, OnSelchangeComWinList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGetWindowsList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetWindowsList)
	DDX_Control(pDX, IDC_COM_WIN_LIST, m_lstWinows);
	//}}AFX_DATA_MAP
}
//--------------------------------------------------------------------------
BOOL CGetWindowsList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char szName[100] = "";
	char *pszBeginPos = m_lpWindowsNames;
	char *pszEndPos = NULL;
	
	int iLength = 0;
	while((pszEndPos = strpbrk( pszBeginPos, RETURN_NEWLINE)) != NULL)
	{
		iLength = pszEndPos - pszBeginPos;
		if(iLength > 0)
		{
			strncpy(szName, pszBeginPos, iLength);
			m_lstWinows.AddString(szName);
			ZeroMemory(szName, sizeof(szName));
		}
		
		pszBeginPos = pszEndPos + 2;

		if(pszBeginPos > m_lpWindowsNames + strlen(m_lpWindowsNames))
			break;
	}

	if(m_lstWinows.GetCount() > 0)
	{
		m_lstWinows.SetCurSel(0);
		m_lstWinows.GetLBText(m_lstWinows.GetCurSel(), m_szCurWindow);

		if(m_lstWinows.GetCount() == 1)
		{
			EndDialog(IDOK);
			return FALSE;
		}
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CGetWindowsList message handlers
CString CGetWindowsList::GetCurrentWindowName()
{
	return m_szCurWindow;
}
//-------------------------------------------------------------------
void CGetWindowsList::OnSelchangeComWinList() 
{
	CString strName = "";
	m_lstWinows.GetLBText(m_lstWinows.GetCurSel(), m_szCurWindow);
}
