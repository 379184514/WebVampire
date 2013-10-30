// anlinHtmlEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebVampire.h"
#include "anlinHtmlEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CanlinHtmlEditDlg dialog


CanlinHtmlEditDlg::CanlinHtmlEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CanlinHtmlEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CanlinHtmlEditDlg)
	m_edit_lockfile = _T("");
	m_edit_saveformURL = _T("");
	m_edit_title = _T("");
	//}}AFX_DATA_INIT
}


void CanlinHtmlEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CanlinHtmlEditDlg)
	DDX_Text(pDX, IDC_EDIT_lockfile, m_edit_lockfile);
	DDX_Text(pDX, IDC_EDIT_saveformURL, m_edit_saveformURL);
	DDX_Text(pDX, IDC_EDIT_title, m_edit_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CanlinHtmlEditDlg, CDialog)
	//{{AFX_MSG_MAP(CanlinHtmlEditDlg)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_title, Ontitle)
	ON_BN_CLICKED(IDC_savefromURL, OnsavefromURL)
	ON_BN_CLICKED(IDC_lockfile, Onlockfile)
	ON_EN_KILLFOCUS(IDC_EDIT_title, OnKillfocusEDITtitle)
	ON_EN_CHANGE(IDC_EDIT_saveformURL, OnChangeEDITsaveformURL)
	ON_EN_CHANGE(IDC_EDIT_lockfile, OnChangeEDITlockfile)
	ON_BN_CLICKED(IDC_BUTTON_lockfile, OnBUTTONlockfile)
	ON_BN_CLICKED(IDC_save, Onsave)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CanlinHtmlEditDlg message handlers

BOOL CanlinHtmlEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//----------------------------------------------------------------------
	VERIFY(m_anlinedithtmlpage.CreateFromStatic(IDC_HTMLVIEW, this));
	m_anlinedithtmlpage.LoadFromResource(_T("ANLINHTMLEDIT.HTM"));
//-----------------------------------------------------------------
	if(isedit)SetTimer(1,100,NULL); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}












#include <atlbase.h>

CComModule _Module;		// 由于要使用 CComDispatchDriver ATL的智能指针，
						// 所以声明它是必须的

#include <mshtml.h>		// 所有 IHTMLxxxx 的接口声明
#include <atlcom.h>


void CanlinHtmlEditDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	IHTMLElement*   pDocElem=NULL; 
	/*
	//---------------方法1--------------------------------
	
	  IHTMLDocument2 *m_pHtmlDoc2=NULL;
	  LPDISPATCH lpDispatch;
	  lpDispatch=m_page.GetHtmlDocument(); 
	  ASSERT(lpDispatch);
	  //get html document from IDispatch
	  HRESULT hr=lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&m_pHtmlDoc2); 
	  
		if(m_pHtmlDoc2!=NULL) m_pHtmlDoc2->get_body(&pDocElem);
		else AfxMessageBox("m_pHtmlDoc2==NULL");
	*/	
	

	
	///*
	//-----------------------------方法2-----------------------------------------
	IHTMLDocument2 *pDoc=(IHTMLDocument2 *)(m_anlinedithtmlpage.GetHtmlDocument()); 
//	if(pDoc!=NULL) pDoc->get_body(&pDocElem);
//	else AfxMessageBox("pDoc==NULL");
	//------------------------------------------------------------------------
	//*/
	IHTMLFramesCollection2 *pFramesCollection=NULL; 
	pDoc->get_frames(&pFramesCollection);
	
	VARIANT varindex,varresult; 
	varresult.vt=VT_DISPATCH; 
	varindex.vt = VT_I4; 
	varindex.lVal=0;
	pFramesCollection->item(&varindex, &varresult);
	IHTMLDocument2 *pFrameDoc=NULL; 
	IHTMLWindow2 *pHTMLWnd=NULL;
	((LPDISPATCH)varresult.ppdispVal)->QueryInterface(IID_IHTMLWindow2, (LPVOID *)&pHTMLWnd);
	
	
	pHTMLWnd->get_document(&pFrameDoc);
	pFrameDoc->get_body(&pDocElem);
	if(pDocElem) 
	{ 
		// ASSERT(SUCCEEDED(hr)); 
		BSTR   bstrHTML; 
		pDocElem->get_outerHTML(&bstrHTML); 
		pDocElem->Release(); 
		
		USES_CONVERSION; 
		MessageBox(OLE2T(bstrHTML),_T("源文件")); 
		SysFreeString(bstrHTML); 
	}	
}

void CanlinHtmlEditDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
//--------------------------------------------------------------------------------------------
	IHTMLDocument2 *pDoc=(IHTMLDocument2 *)(m_anlinedithtmlpage.GetHtmlDocument()); 
	/*
	//----------------------第一种方法------------
	if (pDoc != NULL)
	{
		IDispatch *spDisp = NULL;
		HRESULT hr  = pDoc->get_Script(&spDisp);
		if (spDisp)
		{
            // Evaluate is the name of the script function.
            OLECHAR FAR* szMember = L"selectAll";
            DISPID dispid;
			
            HRESULT hr = spDisp->GetIDsOfNames(IID_NULL, &szMember, 1,
				LOCALE_SYSTEM_DEFAULT, &dispid);
			
            if (SUCCEEDED(hr))
            {
				COleVariant vtResult;
				static BYTE parms[] = VTS_BSTR;
				
				COleDispatchDriver dispDriver(spDisp, FALSE);
				
				dispDriver.InvokeHelper(dispid, DISPATCH_METHOD, VT_VARIANT,
					(void*)&vtResult, parms,
					"5+9");
				CString rest;
				rest.Format("%d",vtResult.lVal);
				AfxMessageBox(rest);
            }
		}
		
	}
	*/

//----------------------第2种方法------------
	if (pDoc != NULL)
	{
		IDispatch *pdis = NULL;
		HRESULT hr  = pDoc->get_Script(&pdis);
		CComVariant avarParams[5] = {"123","456","789","000"};
        DISPPARAMS dispParams = {avarParams, NULL, 2, 0};
		//-----------------------参数数组，  ，参数个数，

		UINT nArgErr = (UINT)-1;      // initialize to invalid arg
		CComVariant result;
		EXCEPINFO excepInfo;
		if(pdis)
		{
			DISPID tmpDispID = 0;
			LPOLESTR func = L"selectAll"; // javascript 函数名
			hr = pdis->GetIDsOfNames(GUID_NULL, &func, 1, LOCALE_SYSTEM_DEFAULT, &tmpDispID);
			if(S_OK == hr)
				hr = pdis->Invoke(tmpDispID, IID_NULL, LOCALE_USER_DEFAULT,
				DISPATCH_METHOD, &dispParams, &result, &excepInfo, &nArgErr);
			
			CString rest;
			//rest.Format("%d",result.lVal);
			rest=result.bstrVal;
			AfxMessageBox(rest);
		}
		
	}
//-------------------------------------------------------------------------------------------------
}

struct tagVARIANT * CanlinHtmlEditDlg::runjs(LPOLESTR func,struct tagVARIANT * avarParams,int nn)
{
	IHTMLDocument2 *pDoc=(IHTMLDocument2 *)(m_anlinedithtmlpage.GetHtmlDocument()); 
	/*
	//----------------------第一种方法------------
	if (pDoc != NULL)
	{
		IDispatch *spDisp = NULL;
		HRESULT hr  = pDoc->get_Script(&spDisp);
		if (spDisp)
		{
            // Evaluate is the name of the script function.
            OLECHAR FAR* szMember = L"selectAll";
            DISPID dispid;
			
            HRESULT hr = spDisp->GetIDsOfNames(IID_NULL, &szMember, 1,
				LOCALE_SYSTEM_DEFAULT, &dispid);
			
            if (SUCCEEDED(hr))
            {
				COleVariant vtResult;
				static BYTE parms[] = VTS_BSTR;
				
				COleDispatchDriver dispDriver(spDisp, FALSE);
				
				dispDriver.InvokeHelper(dispid, DISPATCH_METHOD, VT_VARIANT,
					(void*)&vtResult, parms,
					"5+9");
				CString rest;
				rest.Format("%d",vtResult.lVal);
				AfxMessageBox(rest);
            }
		}
		
	}
	*/
	CComVariant result;
	if (pDoc != NULL)
	{
		IDispatch *pdis = NULL;
		HRESULT hr  = pDoc->get_Script(&pdis);
        DISPPARAMS dispParams = {avarParams, NULL, nn, 0};
		//-----------------------参数数组，  ，参数个数，
		UINT nArgErr = (UINT)-1;      // initialize to invalid arg
		EXCEPINFO excepInfo;
		if(pdis)
		{
			DISPID tmpDispID = 0;
			//LPOLESTR func = L"selectAll"; // javascript 函数名
			hr = pdis->GetIDsOfNames(GUID_NULL, &func, 1, LOCALE_SYSTEM_DEFAULT, &tmpDispID);
			if(S_OK == hr)
				hr = pdis->Invoke(tmpDispID, IID_NULL, LOCALE_USER_DEFAULT,
				DISPATCH_METHOD, &dispParams, &result, &excepInfo, &nArgErr);
			
		//	CString rest;
			//rest.Format("%d",result.lVal);
		//	rest=result.bstrVal;
		//	AfxMessageBox(rest);
		}
		
	}
	return &result;
}

void CanlinHtmlEditDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"selectAll";
	CComVariant Params[5] = {"123","456","789","000"};
	CComVariant *result=(CComVariant *)runjs(func,Params,3);
	//参数逆序，即当个数为2时，"456"为第一参数，"123"为第二参数
	//当个数为3时，"789"为第一参数，"456"为第二参数，"123"为第三参数
	
	CString rest;
	//rest.Format("%d",result.lVal);
	rest=result->bstrVal;
	AfxMessageBox(rest);
}

void CanlinHtmlEditDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
		IHTMLDocument2 *pDoc=(IHTMLDocument2 *)(m_anlinedithtmlpage.GetHtmlDocument()); 
	IHTMLWindow2 *pHTMLWnd=NULL; 
	IHTMLDocument2 *pFrameDoc=NULL; 
	IHTMLFramesCollection2 *pFramesCollection=NULL; 
	LPDISPATCH lpDispatch; 
  
	long p; 
	VARIANT varindex,varresult; 
	varresult.vt=VT_DISPATCH; 
	varindex.vt = VT_I4; 
//	pDoc->
	if(pDoc!=NULL) 
	{ 
		HRESULT hr=pDoc->get_frames(&pFramesCollection); 
		if(SUCCEEDED(hr)&&pFramesCollection!=NULL) 
		{ 
			hr=pFramesCollection->get_length(&p); 
			if(SUCCEEDED(hr)) 
				for(int i=0; i<p; i++) 
				{ 
					varindex.lVal = i; 
					if(pFramesCollection->item(&varindex, &varresult) ==S_OK) 
					{ 
						lpDispatch=(LPDISPATCH)varresult.ppdispVal; 
						if (SUCCEEDED(lpDispatch->QueryInterface(IID_IHTMLWindow2, (LPVOID *)&pHTMLWnd))) 
						{ 
							if(SUCCEEDED(pHTMLWnd->get_document(&pFrameDoc))) 
							{ 
								//work with the pFrameDoc... 
								IHTMLElement*   pDocElem=NULL; 
								hr   =   pFrameDoc->get_body(&pDocElem); 
								
								
								if(pDocElem) 
								{ 
									
									// ASSERT(SUCCEEDED(hr)); 
									BSTR   bstrHTML; 
									pDocElem->get_outerHTML(&bstrHTML); 
									pDocElem->Release(); 
									USES_CONVERSION; 
									UpdateData();
									WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\"",SW_SHOWNORMAL);
									::Sleep(100);
									WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\\image\"",SW_SHOWNORMAL);
									::Sleep(100);
									WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\\file\"",SW_SHOWNORMAL);
									::Sleep(100);
									CFile mFile2(_T(savehtmlfilepath+m_edit_title+"\\"+m_edit_title+".htm"), CFile::modeWrite|CFile::modeCreate); 
									mFile2.Write(OLE2T(bstrHTML),lstrlenW(bstrHTML)); 
									
									mFile2.Flush(); 
									mFile2.Close(); 
									MessageBox("成功");
									MessageBox(OLE2T(bstrHTML),   _T("源文件")); 
									SysFreeString(bstrHTML); 
								} 
								pFrameDoc->Release(); 
								
							} 
							pHTMLWnd->Release(); 
							pHTMLWnd=NULL; 
						} 
					} 
				} 
				pFramesCollection->Release(); 
		} 
		pDoc->Release(); 
	} 
}

void CanlinHtmlEditDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	//document.getElementById("HtmlEditor").src=file2.value
	LPOLESTR func = L"openfile";
	CComVariant Params[5];
	CString dd=savehtmlfilepath+"\\"+m_edit_title+"\\"+m_edit_title+".htm";
	Params[0]=CComVariant(dd);
	CComVariant *result=(CComVariant *)runjs(func,Params,1);
}





void CanlinHtmlEditDlg::Ontitle() 
{
	// TODO: Add your control notification handler code here
LPOLESTR func = L"settitle";
	CComVariant Params[5];
	UpdateData();
	Params[0]=CComVariant(m_edit_title);
CComVariant *result=(CComVariant *)runjs(func,Params,1);

}

void CanlinHtmlEditDlg::OnsavefromURL() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"getalink";
	CComVariant Params[5];
	UpdateData();
	CString dd=m_edit_saveformURL;
	Params[0]=CComVariant(dd);
	CComVariant *result=(CComVariant *)runjs(func,Params,1);	
}

void CanlinHtmlEditDlg::Onlockfile() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"getfile";
	CComVariant Params[5];
	UpdateData();
	CString dd=m_edit_lockfile;
	Params[0]=CComVariant(dd);
	CComVariant *result=(CComVariant *)runjs(func,Params,1);	
}

void CanlinHtmlEditDlg::OnKillfocusEDITtitle() 
{
	// TODO: Add your control notification handler code here
	Ontitle();
}

void CanlinHtmlEditDlg::OnChangeEDITsaveformURL() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnsavefromURL();
}

void CanlinHtmlEditDlg::OnChangeEDITlockfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Onlockfile();
}

void CanlinHtmlEditDlg::OnBUTTONlockfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog FDlg(TRUE , "*.*" , NULL , OFN_HIDEREADONLY , "所有文件(*.*) |*.*||" );
	if(FDlg.DoModal() == IDOK)		
	{
		m_edit_lockfile = FDlg.GetPathName();
		UpdateData(false);
		Onlockfile();	
	}
}
#include <direct.h>
void CanlinHtmlEditDlg::Onsave() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"jseval";
	CComVariant Params[5];
	
	CString dd="window\.frames\[\"HtmlEditor\"\]\.document\.getElementsByTagName\(\"html\"\)\[0\].innerHTML\;";
	Params[0]=CComVariant(dd);
	CComVariant *result=(CComVariant *)runjs(func,Params,1);
	
	CString rest;
	//rest.Format("%d",result.lVal);
	rest=result->bstrVal;
//	AfxMessageBox(rest);
	
/*	
	UpdateData();
	WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\"",SW_SHOWNORMAL);
	::Sleep(100);
	WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\\image\"",SW_SHOWNORMAL);
	::Sleep(100);
	WinExec("cmd.exe /c md \""+savehtmlfilepath+m_edit_title+"\\file\"",SW_SHOWNORMAL);
	::Sleep(100);
*/
	mkdir(savehtmlfilepath+m_edit_title);//0成功，-1已存在
	mkdir(savehtmlfilepath+m_edit_title+"\\image");//0成功，-1已存在
	mkdir(savehtmlfilepath+m_edit_title+"\\file");//0成功，-1已存在
	CFile mFile2(_T(savehtmlfilepath+m_edit_title+"\\"+m_edit_title+".htm"), CFile::modeWrite|CFile::modeCreate); 
	mFile2.Write(rest,rest.GetLength()); 
	
	mFile2.Flush(); 
	mFile2.Close(); 
//	MessageBox("保存完成");	

}

void CanlinHtmlEditDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"imgsrc2";
	CComVariant Params[5];
	CComVariant *result=(CComVariant *)runjs(func,Params,0);	
}

void CanlinHtmlEditDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"getIframeImgURL";
	CComVariant Params[5];
	CComVariant *result=(CComVariant *)runjs(func,Params,0);
	

	CString rest,appname;
	rest=result->bstrVal;
	//AfxMessageBox(rest);
	mkdir(savehtmlfilepath+m_edit_title);//0成功，-1已存在
	mkdir(savehtmlfilepath+m_edit_title+"\\image");//0成功，-1已存在
	mkdir(savehtmlfilepath+m_edit_title+"\\file");//0成功，-1已存在
	for(int i=0;AfxExtractSubString(appname,rest,i,' ');i++)
	{
	//AfxExtractSubString(appname, fullstring, i, ' '); // 取出第i个子串
		if(appname!="")
			downloadimg(appname);
	}
}

#include <afxinet.h>
bool CanlinHtmlEditDlg::downloadimg(CString imgurl)
{
		CString szFile;
	//szFile="http://www.baidu.com/img/logo-yy.gif";
//	UpdateData(TRUE);
	szFile=imgurl;//m_fileurl;
	char				filebuf[512];
	CInternetSession	netSession;
	CStdioFile			*fTargFile;
	fTargFile = netSession.OpenURL(szFile,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
	// 在当前目录创建新的目标文件
	CFile fDestFile(savehtmlfilepath+m_edit_title+"\\image\\"+fTargFile->GetFileName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	int byteswrite;		// 写入文件的字节数
	while (byteswrite = fTargFile->Read(filebuf, 512))	// 读取文件
	{
		fDestFile.Write(filebuf, byteswrite);	// 将实际数据写入文件
	}
		
	fDestFile.Close();
//	AfxMessageBox("下载完成");
return true;
}

void CanlinHtmlEditDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	LPOLESTR func = L"jseval";
	CComVariant Params[5];
	
	CString dd="window\.frames\[\"HtmlEditor\"\]\.document\.getElementById\(\"原始链接\"\)\.href\;";
	//	CString dd="window\.frames\[\"HtmlEditor\"\]\.document\.getElementsByTagName\(\"html\"\)\[0\].innerHTML\;";
	Params[0]=CComVariant(dd);
	CComVariant *result=(CComVariant *)runjs(func,Params,1);
		CString rest;
	//rest.Format("%d",result.lVal);
	rest=result->bstrVal;
	m_edit_saveformURL=rest;
	UpdateData(false);
	
}

void CanlinHtmlEditDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		OnButton6();
		SetTimer(2,100,NULL);
		KillTimer(1); 
	}
	else
	{
		OnButton10();
		KillTimer(2); 
	}
	CDialog::OnTimer(nIDEvent);
}

void CanlinHtmlEditDlg::OnOK() //完成
{
	// TODO: Add extra validation here
	Ontitle();
	OnsavefromURL();
	Onlockfile();
	OnButton9() ;//保存图片
	OnButton8() ;//图片本地化
	Onsave() ;//保存
	CDialog::OnOK();
}
