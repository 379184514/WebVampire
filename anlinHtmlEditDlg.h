#if !defined(AFX_ANLINHTMLEDITDLG_H__2CDCE8F4_6625_44FB_B2DE_1FBFF702F877__INCLUDED_)
#define AFX_ANLINHTMLEDITDLG_H__2CDCE8F4_6625_44FB_B2DE_1FBFF702F877__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// anlinHtmlEditDlg.h : header file
//
//**********************8
#include "HtmlCtrl.h"
//***********************

/////////////////////////////////////////////////////////////////////////////
// CanlinHtmlEditDlg dialog

class CanlinHtmlEditDlg : public CDialog
{
// Construction
public:
	CanlinHtmlEditDlg(CWnd* pParent = NULL);   // standard constructor
//-------------------------------------------------------------------------------------------
	struct tagVARIANT * runjs(LPOLESTR func,struct tagVARIANT * avarParams,int nn);
//--------------------------------------------------------------------------------------------
bool downloadimg(CString imgurl);	
bool isedit;

	CString savehtmlfilepath;
// Dialog Data
	//{{AFX_DATA(CanlinHtmlEditDlg)
	enum { IDD = IDD_ANLINHTMLEDIT_DIALOG };
	CString	m_edit_lockfile;
	CString	m_edit_saveformURL;
	CString	m_edit_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CanlinHtmlEditDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
//****************************
	CHtmlCtrl m_anlinedithtmlpage;
//******************************

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CanlinHtmlEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void Ontitle();
	afx_msg void OnsavefromURL();
	afx_msg void Onlockfile();
	afx_msg void OnKillfocusEDITtitle();
	afx_msg void OnChangeEDITsaveformURL();
	afx_msg void OnChangeEDITlockfile();
	afx_msg void OnBUTTONlockfile();
	afx_msg void Onsave();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANLINHTMLEDITDLG_H__2CDCE8F4_6625_44FB_B2DE_1FBFF702F877__INCLUDED_)
