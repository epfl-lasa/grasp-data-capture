/*
 * $Header:   G:/CORE/MSVC/FsxUser/dlginfo.h_v   1.0   Jan 25 2002 17:10:12   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FsxUser/dlginfo.h_v  $
 * 
 *    Rev 1.0   Jan 25 2002 17:10:12   FCHEN
 * Initial revision.
*/

#if !defined(_DLGINFO_H_)
#define _DLGINFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInforDialog dialog

class CInforDialog : public CDialog
{
// Construction
public:
	CInforDialog(CWnd* pParent = NULL);   // standard constructor
	void SetInfoText(CString strMessage);
// Dialog Data
	//{{AFX_DATA(CInforDialog)
	enum { IDD = IDD_INFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInforDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInforDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DLGINFO_H_)
