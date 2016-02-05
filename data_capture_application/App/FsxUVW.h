/*
 * $Header:   G:/CORE/MSVC/FSXUSER/fsxuvw.h_v   1.1   Mar 27 2001 13:24:04   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/fsxuvw.h_v  $
 * 
 *    Rev 1.1   Mar 27 2001 13:24:04   FCHEN
 * Added SetViewBitmap(), CleanUp(), prvDrawBitmap(), prvDrawView()
 * and OnSize().
 * 
 *    Rev 1.0   Jan 09 2001 11:52:10   FCHEN
 * Initial revision.
*/

// FsxUVw.h : interface of the CFsxUserView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSXUVW_H__05194D90_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
#define AFX_FSXUVW_H__05194D90_CA91_11D4_B729_00A0CC56138A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFsxUserView : public CView
{
protected: // create from serialization only
	CFsxUserView();
	DECLARE_DYNCREATE(CFsxUserView)

// Attributes
public:
	CFsxUserDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsxUserView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFsxUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOL SetViewBitmap(BITMAP* pBitmap);
	void CleanUp();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFsxUserView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void prvDrawBitmap(CDC* pDC);
	void prvDrawView(CDC* pDC);

private:
	BITMAP m_structBM;
};

#ifndef _DEBUG  // debug version in FsxUVw.cpp
inline CFsxUserDoc* CFsxUserView::GetDocument()
   { return (CFsxUserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSXUVW_H__05194D90_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
