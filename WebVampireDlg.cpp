// WebVampireDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebVampire.h"
#include "WebVampireDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebVampireDlg dialog

CWebVampireDlg::CWebVampireDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebVampireDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebVampireDlg)
	m_go_url = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebVampireDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebVampireDlg)
	DDX_Control(pDX, IDC_EDIT_url, m_bt_url);
	DDX_Control(pDX, IDC_BUTTON_gogo, m_bt_gogo);
	DDX_Control(pDX, IDC_TREE_list, m_tree_ctrl);
	DDX_Text(pDX, IDC_EDIT_url, m_go_url);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWebVampireDlg, CDialog)
	//{{AFX_MSG_MAP(CWebVampireDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_bt_dirtree, Onbtdirtree)
	ON_BN_CLICKED(IDC_btdiropen, Onbtdiropen)
	ON_COMMAND(ID_M_ADD, OnMAdd)
	ON_COMMAND(ID_M_CP, OnMCp)
	ON_COMMAND(ID_M_CUT, OnMCut)
	ON_COMMAND(ID_M_DEL, OnMDel)
	ON_COMMAND(ID_M_EDIT, OnMEdit)
	ON_COMMAND(ID_M_P, OnMP)
	ON_COMMAND(ID_M_RNAME, OnMRname)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_list, OnSelchangedTREElist)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_list, OnRclickTREElist)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE_list, OnEndlabeleditTREElist)
	ON_COMMAND(ID_M_ADDG, OnMAddg)
	ON_BN_CLICKED(IDC_BUTTON_back, OnBUTTONback)
	ON_BN_CLICKED(IDC_BUTTON_Forward, OnBUTTONForward)
	ON_BN_CLICKED(IDC_BUTTON_gogo, OnBUTTONgogo)
	ON_BN_CLICKED(IDC_BUTTON_Home, OnBUTTONHome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebVampireDlg message handlers

BOOL CWebVampireDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//--------------------------------------------------------------------
	VERIFY(m_page.CreateFromStatic(IDC_STATIC_web, this));
//-----------------------------------------------------------------------
//AfxMessageBox("init");
//-------------------------------------------------------

	b_lbtdown=FALSE;
	b_spliter=FALSE;
	pstatic=GetDlgItem(IDC_STATIC_web);

	GetClientRect(rect_maindlg);
	m_tree_ctrl.GetClientRect(&rect_treelist);   //取得控件的全屏坐标
	pstatic->GetClientRect(rect_static_web);

	rect_treelist.left=0;
	rect_treelist.top=5;
	rect_treelist.right=200;
	rect_static_web.top=30;
	rect_treelist.bottom=rect_maindlg.bottom-0;
	rect_static_web.bottom=rect_maindlg.bottom-0;
	rect_static_web.right=rect_maindlg.right-0;
	rect_static_web.left=rect_treelist.right+6;
	
	m_tree_ctrl.MoveWindow(rect_treelist);
	
	(*pstatic).MoveWindow(rect_static_web);


	CRect buttonrect;
	GetDlgItem(IDC_BUTTON_back)->GetClientRect(&buttonrect);
	buttonrect.left=rect_treelist.right+6;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_back)->MoveWindow(buttonrect);
	buttonrect.left=rect_treelist.right+50;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_Forward)->MoveWindow(buttonrect);
	buttonrect.left=rect_treelist.right+94;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_Home)->MoveWindow(buttonrect);
	buttonrect.left=rect_maindlg.right-96;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
	buttonrect.left=rect_treelist.right+138;
	buttonrect.right=rect_maindlg.right-100;
	buttonrect.top=5;
	buttonrect.bottom=25;
	GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
//----------------------------------------------------------------
	
Onbtdirtree() ;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWebVampireDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebVampireDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebVampireDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWebVampireDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default

//-------------------------------------------------------
	lpMMI-> ptMinTrackSize.x   =   400   ; //设置窗口最小值
	lpMMI-> ptMinTrackSize.y   =   400   ; 
	
//	lpMMI-> ptMaxTrackSize.x   =   500   ; //设置窗口最大值
//	lpMMI-> ptMaxTrackSize.y   =   500   ; 
//----------------------------------------------------------------------

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CWebVampireDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
//----------------------------------------------------
	CRect rect(pRect);
	m_tree_ctrl.GetWindowRect(&rect_treelist);   //取得控件的全屏坐标
	pstatic->GetWindowRect(rect_static_web);
	rect_static_web.right=rect.right-5;
	rect_static_web.bottom=rect.bottom-5;
	rect_treelist.bottom=rect.bottom-5;
	this->ScreenToClient(&rect_treelist); 
	m_tree_ctrl.MoveWindow(rect_treelist);
	
	
	this->ScreenToClient(&rect_static_web); 
	(*pstatic).MoveWindow(rect_static_web);
	

	CRect buttonrect;
	GetDlgItem(IDC_BUTTON_back)->GetClientRect(&buttonrect);
	buttonrect.left=rect_treelist.right+6;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_back)->MoveWindow(buttonrect);
	buttonrect.left=rect_treelist.right+50;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_Forward)->MoveWindow(buttonrect);
	buttonrect.left=rect_treelist.right+94;
	buttonrect.right=buttonrect.left+40;
	GetDlgItem(IDC_BUTTON_Home)->MoveWindow(buttonrect);
	GetClientRect(rect_maindlg);
	if(rect_static_web.Width()>382)
	{
		buttonrect.left=rect_maindlg.right-96;
		buttonrect.right=buttonrect.left+40;
		
		GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+138;
		buttonrect.right=rect_maindlg.right-100;
		buttonrect.top=5;
		buttonrect.bottom=25;
		
		GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
	}
	else
	{
		buttonrect.left=rect_treelist.right+292;
		buttonrect.right=buttonrect.left+40;
		GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+138;
		buttonrect.right=buttonrect.left+150;
		buttonrect.top=5;
		buttonrect.bottom=25;
		GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
	}
//	Invalidate();
//	m_page.MoveWindow(rect_static_web);
	
//	CString str,str2;
//	str.Format("x1:%d,y1:%d,x2:%d,y2:%d",rect.top,rect.left,rect.right,rect.bottom);
//	str2.Format("x1:%d,y1:%d,x2:%d,y2:%d",rect_treelist.top,rect_treelist.left,rect_treelist.right,rect_treelist.bottom);
//m_go_url=str;
//UpdateData(false);
	//	AfxMessageBox(str);
//	SetDlgItemText(IDC_STATIC_web,str+"\n"+str2);
//-----------------------------------------------------	
}

void CWebVampireDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//--------------------------------------------
	POINT   pt;   
	GetCursorPos(&pt);//取得当前鼠标坐标。
	
	//ClientToScreen(&pt);
	//ScreenToClient(&pt);//换算到窗口坐标。
	
	m_tree_ctrl.GetWindowRect(&rect_treelist);   //取得控件的全屏坐标。
	
	pstatic->GetWindowRect(rect_static_web);
	//this->ScreenToClient(&rect_treelist); 
	//m_tree_ctrl.GetClientRect(rect_treelist);	
	
	if((pt.x > rect_treelist.right) && (pt.x < rect_treelist.right+6))//当鼠标处于IDC_STATIC_web和IDC_TREE_list中间时。
	{
		SetCursor(LoadCursor(NULL,IDC_SIZEWE));//设置鼠标样式，左右箭头样式IDC_SIZEWE。
		b_spliter=TRUE;	//鼠标在分界线上，可以拖动，也就是可以调节分界线位置。
	}
	else
	{
		b_spliter=FALSE;//鼠标不在分界线上，不可以拖动。
	}
	
	if(b_lbtdown&&(pt.x > rect_treelist.left+10)&&(pt.x < rect_static_web.right-10 ))//当鼠标左键按下时调节分割条，并且不能超出树跟静态框的边界。
	{
		rect_treelist.right=pt.x-3;//调节树控件IDC_TREE_list的最右边保持鼠标坐标-3的位置。
		this->ScreenToClient(&rect_treelist); //换算到屏幕坐标。
		m_tree_ctrl.MoveWindow(rect_treelist);//
		
		rect_static_web.left=pt.x+3;
		this->ScreenToClient(&rect_static_web); 
		(*pstatic).MoveWindow(rect_static_web);
		
		CRect buttonrect;
		GetDlgItem(IDC_BUTTON_back)->GetClientRect(&buttonrect);
		buttonrect.left=rect_treelist.right+6;
		buttonrect.right=buttonrect.left+40;
		GetDlgItem(IDC_BUTTON_back)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+50;
		buttonrect.right=buttonrect.left+40;
		GetDlgItem(IDC_BUTTON_Forward)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+94;
		buttonrect.right=buttonrect.left+40;
		GetDlgItem(IDC_BUTTON_Home)->MoveWindow(buttonrect);
		GetClientRect(rect_maindlg);
		if(rect_static_web.Width()>382)
		{
			buttonrect.left=rect_maindlg.right-96;
			buttonrect.right=buttonrect.left+40;
			
			GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
			buttonrect.left=rect_treelist.right+138;
			buttonrect.right=rect_maindlg.right-100;
			buttonrect.top=5;
			buttonrect.bottom=25;
			
			GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
		}
		else
		{
			buttonrect.left=rect_treelist.right+292;
			buttonrect.right=buttonrect.left+40;
			GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
			buttonrect.left=rect_treelist.right+138;
			buttonrect.right=buttonrect.left+150;
			buttonrect.top=5;
			buttonrect.bottom=25;
			GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
		}
		Invalidate(FALSE);
	}
	
	
//-------------------------------------------
	CDialog::OnMouseMove(nFlags, point);
}

void CWebVampireDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//---------------------------------------
	if(b_spliter) b_lbtdown=TRUE;//当鼠标处于分割条位置时点击鼠标左键。
	SetCapture();//捕获鼠标。
//---------------------------------------

	
	CDialog::OnLButtonDown(nFlags, point);
}

void CWebVampireDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//----------------------------------------------------------
	b_lbtdown=FALSE;	
	ReleaseCapture();//释放鼠标。
//----------------------------------------------------------
	
	CDialog::OnLButtonUp(nFlags, point);
}

//--------------------------------------
CImageList m_iImageList; 
//-------------------------------------

//-----------------------------------------------------------------
void CWebVampireDlg::BrowseDir(CString strDir,HTREEITEM parent)
{
	CFileFind ff;
	CString szDir = strDir;
	HTREEITEM hSubItem;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);
	while( res )
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			CString strPath = ff.GetFilePath();
			CString strTitle = ff.GetFileTitle();

			if(strTitle!="image"&&strTitle!="file") //不处理资源目录"image"和"file"
			{
				hSubItem = m_tree_ctrl.InsertItem(strTitle, parent);
				m_tree_ctrl.SetItemImage(hSubItem,2,3);
				BrowseDir( strPath, hSubItem );
			}
			else
			{
				m_tree_ctrl.SetItemImage(parent,0,1);//底层目录显示为文件图标。
			}
		}
		/*不再处理文件
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			CString strTitle = ff.GetFileName();//GetFileTitle();

			hSubItem =m_tree_ctrl.InsertItem( strTitle, parent );
			m_tree_ctrl.SetItemImage(hSubItem,0,1);   
		}
		*/
	}
	ff.Close();
}
//----------------------------------------------------------------------------------


void CWebVampireDlg::Onbtdirtree() 
{
	// TODO: Add your control notification handler code here

//-----------------------------------------------------------------------------------------
	  	m_iImageList.Create(20, 20, TRUE|ILC_COLOR32,1, 0);
		HICON hIconfile = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_file), IMAGE_ICON, 24, 24, 0);
		HICON hIconfileopen = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_fileopen), IMAGE_ICON, 24, 24, 0);
		HICON hIcondir = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_dir), IMAGE_ICON, 24, 24, 0);
		HICON hIcondiropen = (HICON)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_diropen), IMAGE_ICON, 24, 24, 0);
		m_iImageList.Add(hIconfile);
		m_iImageList.Add(hIconfileopen);
		m_iImageList.Add(hIcondir);
		m_iImageList.Add(hIcondiropen);
		m_tree_ctrl.SetImageList (&m_iImageList,TVSIL_NORMAL );
		
		m_tree_ctrl.DeleteAllItems();
		m_tree_ctrl.InsertItem("数据库",0,0,NULL );
		
		CFont cfont; 
		cfont.CreateFont(16,        //这个数字就是字体大小了
			0,0,0,FW_NORMAL,   
			FALSE,FALSE,   
			0,   
			GB2312_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS, "楷体"); 
		
		GetDlgItem(IDC_TREE_list)->SetFont(&cfont); 
		cfont.Detach();
		
		m_tree_ctrl.SetTextColor(RGB(235,115,0)); 
		
		m_tree_ctrl.SetItemImage(m_tree_ctrl.GetRootItem(),2,3); 
		//参数：节点、没选中时图标标号、选中时图标标号
		BrowseDir("数据库", m_tree_ctrl.GetRootItem());
		m_tree_ctrl.Expand(m_tree_ctrl.GetRootItem(),TVE_EXPAND);
//--------------------------------------------------------------------------------------------------

	
}

//-----------------------------------------------------------------------------
void CWebVampireDlg::Onbtdiropen() 
{
	WinExec("explorer.exe "+GetFullname(), SW_SHOWNORMAL); //速度快
}
//-------------------------------------------------------------------------------

void CWebVampireDlg::OnRclickTREElist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//-------------------------------------------------------------------------------
	CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象
	menu.LoadMenu(IDC_TREEMENU);//装载自定义的右键菜单
	pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
	CPoint oPoint;//定义一个用于确定光标位置的位置
	GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
//---------------------------------------------------------------------------------------------------
	
	*pResult = 0;
}

//----------------------------------------------------------------------------------------------
void CWebVampireDlg::OnMAdd() 
{
	// TODO: Add your command handler code here
	CString path;
	GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH));
	path.ReleaseBuffer();
	path+="\\"+GetFullname()+"\\";
//	AfxMessageBox(path);
	CanlinHtmlEditDlg adddlg;
	adddlg.savehtmlfilepath=path;
	adddlg.m_edit_lockfile="file";
	adddlg.isedit=false;
	adddlg.DoModal();

	
	HTREEITEM hItemsel=m_tree_ctrl.GetSelectedItem();
	CString hItemseltext = m_tree_ctrl.GetItemText(hItemsel);
	CString hItemfullname=GetFullname();
	HTREEITEM hItemselparent=m_tree_ctrl.GetParentItem(hItemsel);
	m_tree_ctrl.DeleteItem(hItemsel);
	HTREEITEM hItemselparent22=m_tree_ctrl.InsertItem(hItemseltext,hItemselparent);
	m_tree_ctrl.SetItemImage(hItemselparent22,2,3); 
	BrowseDir(hItemfullname, hItemselparent22);//只刷新修改部分，提高效率
	
	m_tree_ctrl.Expand(hItemselparent22,TVE_EXPAND);
}
#include <direct.h>
void CWebVampireDlg::OnMAddg() 
{
	// TODO: Add your command handler code here
	CString path;
	GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH));
	path.ReleaseBuffer();
	path+="\\"+GetFullname()+"\\";
	HTREEITEM hItemnew=m_tree_ctrl.InsertItem("新加分类", m_tree_ctrl.GetSelectedItem());
	mkdir(path+"新加分类");//0成功，-1已存在
	CFile mFile2(_T(path+"新加分类\\新加分类.htm"), CFile::modeCreate); 
	mFile2.Close(); 
	m_tree_ctrl.Expand(m_tree_ctrl.GetSelectedItem(),TVE_EXPAND);
	m_tree_ctrl.SetItemImage(hItemnew,2,3);
	m_tree_ctrl.SelectItem(hItemnew);
	m_tree_ctrl.EditLabel(hItemnew);
}

BOOL DocumentManagement(LPCTSTR lpszFromPath,LPCTSTR lpszToPath,INT method);

CString cpcutdir;
BOOL iscut=FALSE;
	
void CWebVampireDlg::OnMCp() 
{
	// TODO: Add your command handler code here
	cpcutdir=GetFullname();
//	AfxMessageBox("复制:"+GetFullname());
	
}

void CWebVampireDlg::OnMCut() 
{
	// TODO: Add your command handler code here
	cpcutdir=GetFullname();
	iscut=TRUE;
//	AfxMessageBox("剪切:"+GetFullname());
}

void CWebVampireDlg::OnMDel() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("删除："+GetFullname());
	/*
	WinExec("cmd.exe /c rd /s /q \""+GetFullname()+"\"",SW_SHOWNORMAL);
	WinExec("cmd.exe /c del /q \""+GetFullname()+"\"",SW_SHOWNORMAL);
	*/
	if(IDYES == MessageBox("确认删除？","确认删除？",MB_YESNO))   
	{   
		// AfxMessageBox("111");  
		DocumentManagement(GetFullname(),"",FO_DELETE);
		HTREEITEM hItem=m_tree_ctrl.GetSelectedItem();
		m_tree_ctrl.DeleteItem(hItem);
		m_tree_ctrl.Expand(hItem,TVE_EXPAND);
	}
}
CString savehtmlPath;
//CString 
void CWebVampireDlg::OnMEdit() 
{
	// TODO: Add your command handler code here
	CString path;
	GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH));
	path.ReleaseBuffer();
	CString fullname=GetFullname();
	int intpoint = fullname.ReverseFind('\\');
	path+="\\"+fullname.Left(intpoint)+"\\";

//	AfxMessageBox(path);
	CanlinHtmlEditDlg adddlg;
	adddlg.savehtmlfilepath=path;
	adddlg.m_edit_lockfile="file";
	adddlg.isedit=TRUE;
	adddlg.m_edit_title=m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem());
	adddlg.DoModal();
	
	GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH));
	path.ReleaseBuffer();
	path+="\\"+GetFullname()+"\\"+m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem())+".htm";
	//	AfxMessageBox(path);
	m_page.Navigate2(path);	
}
void CWebVampireDlg::OnMRname() 
{
	// TODO: Add your command handler code here
	m_tree_ctrl.EditLabel(m_tree_ctrl.GetSelectedItem());
}
void CWebVampireDlg::OnMP() 
{
	// TODO: Add your command handler code here
	//system("cmd.exe xcopy /e d:\\addfile c:\\");
	
	//WinExec("cmd.exe /c xcopy \/e d:\\addfile c:\\", SW_SHOWNORMAL);//必须加参数/c
	int nPos = cpcutdir.ReverseFind('\\'); 
	CString cpcutname=cpcutdir.Mid(nPos+1,cpcutdir.GetLength()-nPos);
//	AfxMessageBox("节点名："+cpcutname);

	/*调用dos没法等待其结束，剪切时没剪切完就删掉了
	WinExec("xcopy /e/y/i \""+cpcutdir+"\" \""+GetFullname()+"\\"+cpcutname+"\"",SW_SHOWNORMAL);//SW_HIDE);
	if(iscut)
	{
		WinExec("cmd.exe /c rd /s /q \""+cpcutdir+"\"",SW_SHOWNORMAL);
		WinExec("cmd.exe /c del /q \""+cpcutdir+"\"",SW_SHOWNORMAL);
		iscut=FALSE;
	}
	*/
	 if(iscut)
	 {
		 DocumentManagement(cpcutdir,GetFullname(),FO_MOVE);
		 iscut=FALSE;
	 }
	 else
	 {
		 DocumentManagement(cpcutdir,GetFullname(),FO_COPY);
	 }
	HTREEITEM hItemsel=m_tree_ctrl.GetSelectedItem();
	
	CString hItemseltext = m_tree_ctrl.GetItemText(hItemsel);
	CString hItemfullname=GetFullname();
	HTREEITEM hItemselparent=m_tree_ctrl.GetParentItem(hItemsel);
	m_tree_ctrl.DeleteItem(hItemsel);
	HTREEITEM hItemselparent22=m_tree_ctrl.InsertItem(hItemseltext,hItemselparent);
	m_tree_ctrl.SetItemImage(hItemselparent22,2,3); 
	BrowseDir(hItemfullname, hItemselparent22);//只刷新修改部分，提高效率
	
	m_tree_ctrl.Expand(hItemselparent22,TVE_EXPAND);
}

CString CWebVampireDlg::GetFullname()
{
	CString dirfullnametmp=m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem());
	HTREEITEM tmp=m_tree_ctrl.GetSelectedItem();
	while(HTREEITEM tmp2=m_tree_ctrl.GetParentItem(tmp))
	{
		dirfullnametmp=m_tree_ctrl.GetItemText(tmp2)+"\\"+dirfullnametmp;
		tmp=tmp2;
	}
	//AfxMessageBox(dirfullnametmp);
	return dirfullnametmp;
}


BOOL DocumentManagement(LPCTSTR lpszFromPath,LPCTSTR lpszToPath,INT method)
{
int nLengthFrm = strlen(lpszFromPath);
char *NewPathFrm = new char[nLengthFrm+2];
strcpy(NewPathFrm,lpszFromPath);
NewPathFrm[nLengthFrm] = '\0';
NewPathFrm[nLengthFrm+1] = '\0';

    SHFILEOPSTRUCT FileOp; 
    ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));
    
    FileOp.fFlags = FOF_NOCONFIRMATION ; 
    FileOp.hNameMappings = NULL; 
    FileOp.hwnd = NULL; 
    FileOp.lpszProgressTitle = NULL; 
    FileOp.pFrom = NewPathFrm; 
    FileOp.pTo = lpszToPath; 
	FileOp.fFlags=FOF_ALLOWUNDO;//此标志使删除文件备份到Windows回收站
    FileOp.wFunc = method;//FO_COPY; FO_DELETE;FO_MOVE; FO_RENAME; 
    
    return SHFileOperation(&FileOp) == 0;
}

//-----------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------
void CWebVampireDlg::OnSelchangedTREElist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(!m_tree_ctrl.GetChildItem(m_tree_ctrl.GetSelectedItem()))
	{
	//WinExec("explorer.exe "+GetFullname()+"\\"+m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem())+".htm", SW_SHOWNORMAL); //速度快
	//m_page.Navigate2("\""+GetFullname()+"\\"+m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem())+".htm\"");
	//m_page.Navigate2("D:\\WebVampire(改目录结构,改文件操作函数)\\数据库\\vc++\\预览（成功）\\预览（成功）.htm");
	/*获得路径第一种方法。
		char buf[255];
		GetCurrentDirectory(sizeof(buf),buf);
		//path=path+"\\数据库\\vc++\\预览（成功）\\预览（成功）.htm";
		CString aaa=buf;
		
		aaa+="\\"+GetFullname()+"\\"+m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem())+".htm";
		AfxMessageBox(aaa);
		m_page.Navigate2(aaa);
		*/
		CString path;
		GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH));
		path.ReleaseBuffer();
		path+="\\"+GetFullname()+"\\"+m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem())+".htm";
	//	AfxMessageBox(path);
		m_page.Navigate2(path);
	}
	*pResult = 0;
}
//---------------------------------------------------------------------------------------------------



void CWebVampireDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(nType == SIZE_RESTORED)  //还原
	{  
		m_tree_ctrl.GetWindowRect(&rect_treelist);
		this->ScreenToClient(&rect_treelist);
		rect_treelist.bottom=cy;
		m_tree_ctrl.MoveWindow(rect_treelist);
		
		m_page.GetWindowRect(rect_static_web);
		this->ScreenToClient(&rect_static_web); 
		rect_static_web.right=cx;
		rect_static_web.bottom=cy;
		m_page.MoveWindow(rect_static_web); 
		
		rect_static_web.right=cx-56;
		rect_static_web.left=cx-96;
		
		rect_static_web.top=0;
		rect_static_web.bottom=28;
		m_bt_gogo.MoveWindow(rect_static_web);
		rect_static_web.left=rect_treelist.right+138;
		rect_static_web.right=cx-100;
		rect_static_web.top=5;
		rect_static_web.bottom=25;
		
		m_bt_url.MoveWindow(rect_static_web);

	} 
	if(nType == SIZE_MAXIMIZED)  //最大化
	{  
		m_tree_ctrl.GetWindowRect(&rect_treelist);
		pstatic->GetWindowRect(rect_static_web);
		this->ScreenToClient(&rect_treelist); 
		this->ScreenToClient(&rect_static_web); 
		rect_static_web.right=cx-5;
		rect_static_web.bottom=cy-5;
		rect_treelist.bottom=cy-5;
		
		m_tree_ctrl.MoveWindow(rect_treelist);
		(*pstatic).MoveWindow(rect_static_web);  

	CRect buttonrect;
	GetDlgItem(IDC_BUTTON_back)->GetClientRect(&buttonrect);

	GetClientRect(rect_maindlg);
	if(rect_static_web.Width()>382)
	{
		buttonrect.left=rect_maindlg.right-96;
		buttonrect.right=buttonrect.left+40;
		
		GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+138;
		buttonrect.right=rect_maindlg.right-100;
		buttonrect.top=5;
		buttonrect.bottom=25;
		
		GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
	}
	else
	{
		buttonrect.left=rect_treelist.right+292;
		buttonrect.right=buttonrect.left+40;
		GetDlgItem(IDC_BUTTON_gogo)->MoveWindow(buttonrect);
		buttonrect.left=rect_treelist.right+138;
		buttonrect.right=buttonrect.left+150;
		buttonrect.top=5;
		buttonrect.bottom=25;
		GetDlgItem(IDC_EDIT_url)->MoveWindow(buttonrect);
	}		
	} 


}
#include <direct.h>
void CWebVampireDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	int aa=mkdir("c:\\000000");//0成功，-1已存在
	CString rest;
rest.Format("%d",aa);

	AfxMessageBox(rest);

	
}




void CWebVampireDlg::OnEndlabeleditTREElist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
//m_page.Navigate2();
	m_page.Navigate2("");
	CString oldtreelabelname=m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem());
	CString olddir=GetFullname();
//	AfxMessageBox(olddir+"\\"+oldtreelabelname+".htm");
	m_tree_ctrl.SetItem(&pTVDispInfo->item);
	CString newtreelabelname=m_tree_ctrl.GetItemText(m_tree_ctrl.GetSelectedItem());
	CString newdir=GetFullname();
//	AfxMessageBox(newdir+"\\"+newtreelabelname+".htm");
	if(olddir!=newdir)
	{
		//	AfxMessageBox("重命名");
		DocumentManagement(olddir,newdir,FO_MOVE);	
		DocumentManagement(newdir+"\\"+oldtreelabelname+".htm",newdir+"\\"+newtreelabelname+".htm",FO_MOVE);
		m_page.Navigate2(newdir+"\\"+newtreelabelname+".htm");
	}
	else
	{
		m_page.Navigate2(olddir+"\\"+oldtreelabelname+".htm");
	}
	*pResult = 0;
}



void CWebVampireDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnBUTTONgogo() ;
	CDialog::OnOK();
}

void CWebVampireDlg::OnBUTTONback() 
{
	// TODO: Add your control notification handler code here
	m_page.GoBack();


}

void CWebVampireDlg::OnBUTTONForward() 
{
	// TODO: Add your control notification handler code here
	m_page.GoForward();

}

void CWebVampireDlg::OnBUTTONgogo() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString url=m_go_url;
	m_page.Navigate2(m_go_url);
}

void CWebVampireDlg::OnBUTTONHome() 
{
	// TODO: Add your control notification handler code here
	m_page.GoHome();
}
