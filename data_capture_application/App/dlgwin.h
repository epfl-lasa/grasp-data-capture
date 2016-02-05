/*
 * $Header:   G:/CORE/MSVC/FSXUSER/DlgWin.h_v   1.0   Jan 09 2001 11:50:18   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/DlgWin.h_v  $
 * 
 *    Rev 1.0   Jan 09 2001 11:50:18   FCHEN
 * Initial revision.
*/

#if !defined(AFX_DLGWIN_H__ECA3FB04_D595_11D4_B729_00A0CC56138A__INCLUDED_)
#define AFX_DLGWIN_H__ECA3FB04_D595_11D4_B729_00A0CC56138A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetWindowsList dialog

class CGetWindowsList : public CDialog
{
// Construction
public:
	CGetWindowsList(LPSTR lpWindowsNames, CWnd* pParent = NULL);   // standard constructor
	
	CString GetCurrentWindowName();

// Dialog Data
	//{{AFX_DATA(CGetWindowsList)
	enum { IDD = IDD_DIA_WIN_LIST };
	CComboBox	m_lstWinows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetWindowsList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetWindowsList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComWinList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LPSTR m_lpWindowsNames;
	char m_szCurWindow[200];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIN_H__ECA3FB04_D595_11D4_B729_00A0CC56138A__INCLUDED_)
