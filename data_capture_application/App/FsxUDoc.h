/*
 * $Header:   G:/CORE/MSVC/FSXUSER/FsxUDoc.h_v   1.0   Jan 09 2001 11:50:50   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/FsxUDoc.h_v  $
 * 
 *    Rev 1.0   Jan 09 2001 11:50:50   FCHEN
 * Initial revision.
*/

// FsxUDoc.h : interface of the CFsxUserDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSXUDOC_H__05194D8E_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
#define AFX_FSXUDOC_H__05194D8E_CA91_11D4_B729_00A0CC56138A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFsxUserDoc : public CDocument
{
protected: // create from serialization only
	CFsxUserDoc();
	DECLARE_DYNCREATE(CFsxUserDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsxUserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFsxUserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFsxUserDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSXUDOC_H__05194D8E_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
