; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWebVampireDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WebVampire.h"

ClassCount=4
Class1=CWebVampireApp
Class2=CWebVampireDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_WEBVAMPIRE_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_ANLINHTMLEDIT_DIALOG
Class4=CanlinHtmlEditDlg
Resource5=IDC_TREEMENU

[CLS:CWebVampireApp]
Type=0
HeaderFile=WebVampire.h
ImplementationFile=WebVampire.cpp
Filter=N

[CLS:CWebVampireDlg]
Type=0
HeaderFile=WebVampireDlg.h
ImplementationFile=WebVampireDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_M_DEL

[CLS:CAboutDlg]
Type=0
HeaderFile=WebVampireDlg.h
ImplementationFile=WebVampireDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_WEBVAMPIRE_DIALOG]
Type=1
Class=CWebVampireDlg
ControlCount=13
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC_web,static,1342312448
Control4=IDC_TREE_list,SysTreeView32,1350631439
Control5=IDC_bt_dirtree,button,1073807360
Control6=IDC_btdiropen,button,1073807360
Control7=IDC_EDIT_add,edit,1082196096
Control8=IDC_BUTTON2,button,1073807360
Control9=IDC_BUTTON_back,button,1342242816
Control10=IDC_BUTTON_Forward,button,1342242816
Control11=IDC_BUTTON_Home,button,1342242816
Control12=IDC_EDIT_url,edit,1350631552
Control13=IDC_BUTTON_gogo,button,1342242816

[MNU:IDC_TREEMENU]
Type=1
Class=?
Command1=ID_M_ADD
Command2=ID_M_EDIT
Command3=ID_M_DEL
Command4=ID_M_ADDG
Command5=ID_M_CP
Command6=ID_M_CUT
Command7=ID_M_P
Command8=ID_M_RNAME
CommandCount=8

[DLG:IDD_ANLINHTMLEDIT_DIALOG]
Type=1
Class=CanlinHtmlEditDlg
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_title,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_saveformURL,edit,1350631552
Control7=IDC_HTMLVIEW,button,1342177287
Control8=IDC_EDIT_lockfile,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON_lockfile,button,1342242816
Control11=IDC_STATIC,static,1342312449
Control12=IDC_BUTTON2,button,1073807360
Control13=IDC_BUTTON3,button,1073807360
Control14=IDC_BUTTON4,button,1073807360
Control15=IDC_BUTTON5,button,1073807360
Control16=IDC_BUTTON6,button,1073807360
Control17=IDC_title,button,1073807360
Control18=IDC_savefromURL,button,1073807360
Control19=IDC_lockfile,button,1073807360
Control20=IDC_save,button,1073807360
Control21=IDC_BUTTON8,button,1073807360
Control22=IDC_BUTTON9,button,1073807360
Control23=IDC_BUTTON10,button,1073807360

[CLS:CanlinHtmlEditDlg]
Type=0
HeaderFile=anlinHtmlEditDlg.h
ImplementationFile=anlinHtmlEditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CanlinHtmlEditDlg
VirtualFilter=dWC

