; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CMainPage
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Fox.h"

ClassCount=6
Class1=CFoxApp
Class2=CFoxDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_AboutDlg
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CAboutPage
Resource4=IDD_FOX_DIALOG
Resource5=IDD_MainDlg
Class5=CSettingPage
Class6=CMainPage
Resource6=IDD_SettingDlg

[CLS:CFoxApp]
Type=0
HeaderFile=Fox.h
ImplementationFile=Fox.cpp
Filter=N

[CLS:CFoxDlg]
Type=0
HeaderFile=FoxDlg.h
ImplementationFile=FoxDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_MainTab

[CLS:CAboutDlg]
Type=0
HeaderFile=FoxDlg.h
ImplementationFile=FoxDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FOX_DIALOG]
Type=1
Class=CFoxDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MainTab,SysTabControl32,1342177280
Control4=IDC_ApplyButton,button,1342242816

[DLG:IDD_AboutDlg]
Type=1
Class=CAboutPage
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_InfoEdit,edit,1342249092
Control4=IDC_VersionList,SysListView32,1350647825
Control5=IDC_STATIC,button,1342177287
Control6=IDC_DllInfoEdit,edit,1350637700

[CLS:CAboutPage]
Type=0
HeaderFile=AboutPage.h
ImplementationFile=AboutPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DllInfoEdit

[DLG:IDD_MainDlg]
Type=1
Class=CMainPage
ControlCount=23
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PathBrowse,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_Icon,static,1342179331
Control5=IDC_FolderCombo,combobox,1344340227
Control6=IDC_Fake,button,1342242816
Control7=IDC_Release,button,1342242816
Control8=IDC_ControlIcon,static,1342177539
Control9=IDC_PrinterIcon,static,1342177539
Control10=IDC_TrashIcon,static,1342177539
Control11=IDC_NetworkIcon,static,1342177539
Control12=IDC_DialIcon,static,1342177539
Control13=IDC_MyConputerIcon,static,1342177539
Control14=IDC_FavoriteIcon,static,1342177539
Control15=IDC_MyDocumentIcon,static,1342177539
Control16=IDC_CacheIcon,static,1342177539
Control17=IDC_IEIcon,static,1342177539
Control18=IDC_ActiveXIcon,static,1342177539
Control19=IDC_TaskIcon,static,1342177539
Control20=IDC_SubscriptIcon,static,1342177539
Control21=IDC_HistoryIcon,static,1342177539
Control22=IDC_STATIC,button,1342177287
Control23=IDC_PathCombo,combobox,1344340226

[DLG:IDD_SettingDlg]
Type=1
Class=CSettingPage
ControlCount=5
Control1=IDC_CompatibleCheck,button,1342242819
Control2=IDC_PasswordCheck,button,1342242819
Control3=IDC_StartupPass,button,1476460547
Control4=IDC_DisEraseCheck,button,1476460547
Control5=IDC_OpenFolder,button,1342242819

[CLS:CSettingPage]
Type=0
HeaderFile=SettingPage.h
ImplementationFile=SettingPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSettingPage

[CLS:CMainPage]
Type=0
HeaderFile=MainPage.h
ImplementationFile=MainPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMainPage

