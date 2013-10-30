// WebVampire.h : main header file for the WEBVAMPIRE application
//

#if !defined(AFX_WEBVAMPIRE_H__6BEBE0A1_58BE_4EFD_BBC4_E437DF54E4B2__INCLUDED_)
#define AFX_WEBVAMPIRE_H__6BEBE0A1_58BE_4EFD_BBC4_E437DF54E4B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebVampireApp:
// See WebVampire.cpp for the implementation of this class
//

class CWebVampireApp : public CWinApp
{
public:
	CWebVampireApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebVampireApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWebVampireApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBVAMPIRE_H__6BEBE0A1_58BE_4EFD_BBC4_E437DF54E4B2__INCLUDED_)
