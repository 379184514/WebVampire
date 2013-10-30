// WebVampireDlg.h : header file
//

#if !defined(AFX_WEBVAMPIREDLG_H__CBD94D16_8BDB_4353_8F44_84043E617084__INCLUDED_)
#define AFX_WEBVAMPIREDLG_H__CBD94D16_8BDB_4353_8F44_84043E617084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWebVampireDlg dialog

//--------------------------------------------------------------------
//#include "HtmlCtrl.h"
#include "anlinHtmlEditDlg.h"
//--------------------------------------------------------------------

class CWebVampireDlg : public CDialog
{
// Construction
public:
	CWebVampireDlg(CWnd* pParent = NULL);	// standard constructor

//----------------------------
	BOOL b_lbtdown;//鼠标左键是否按下。
	BOOL b_spliter;//鼠标是否处于分界线上。
	CRect rect_treelist;//树控件矩形。
	CRect rect_static_web;//静态文本矩形（静态文本框供web控件用）。
	CWnd *pstatic;//静态文本指针。
	CRect rect_maindlg;//主窗口矩形

//----------------------------

//---------------------------------------------------
	void BrowseDir(CString strDir,HTREEITEM parent);//遍历文件显示到树里。
	CString GetFullname();
//----------------------------------------------------

// Dialog Data
	//{{AFX_DATA(CWebVampireDlg)
	enum { IDD = IDD_WEBVAMPIRE_DIALOG };
	CEdit	m_bt_url;
	CButton	m_bt_gogo;
	CTreeCtrl	m_tree_ctrl;
	CString	m_go_url;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebVampireDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
//--------------------------------------------------------------------
protected:
	CHtmlCtrl m_page;
//---------------------------------------------------------------

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWebVampireDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void Onbtdirtree();
	afx_msg void Onbtdiropen();
	afx_msg void OnMAdd();
	afx_msg void OnMCp();
	afx_msg void OnMCut();
	afx_msg void OnMDel();
	afx_msg void OnMEdit();
	afx_msg void OnMP();
	afx_msg void OnMRname();
	afx_msg void OnSelchangedTREElist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTREElist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton2();
	afx_msg void OnEndlabeleditTREElist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMAddg();
	virtual void OnOK();
	afx_msg void OnBUTTONback();
	afx_msg void OnBUTTONForward();
	afx_msg void OnBUTTONgogo();
	afx_msg void OnBUTTONHome();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBVAMPIREDLG_H__CBD94D16_8BDB_4353_8F44_84043E617084__INCLUDED_)
