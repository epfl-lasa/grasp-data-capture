/*
 * $Header:   G:/CORE/MSVC/FSXUSER/Stdafx.h_v   1.0   Jan 09 2001 11:53:46   FCHEN  $
 *
 * $Log:   G:/CORE/MSVC/FSXUSER/Stdafx.h_v  $
 * 
 *    Rev 1.0   Jan 09 2001 11:53:46   FCHEN
 * Initial revision.
 * 
*/

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__05194D8A_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
#define AFX_STDAFX_H__05194D8A_CA91_11D4_B729_00A0CC56138A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_DCOM
	#define _WIN32_DCOM
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__05194D8A_CA91_11D4_B729_00A0CC56138A__INCLUDED_)
#include <afxcontrolbars.h>
