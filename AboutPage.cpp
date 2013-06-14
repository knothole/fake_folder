// AboutPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Fox.h"
#include "AboutPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutPage ダイアログ


CAboutPage::CAboutPage(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutPage)
	m_cInfo = _T("");
	//}}AFX_DATA_INIT
	m_cInfo = "hilo-m@mb.nma.ne.jp\r\nhttp://www.mb.nma.ne.jp/~hilo-m/";
}


void CAboutPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPage)
	DDX_Control(pDX, IDC_DllInfoEdit, m_cnDllInfo);
	DDX_Control(pDX, IDC_VersionList, m_cnList);
	DDX_Text(pDX, IDC_InfoEdit, m_cInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutPage, CDialog)
	//{{AFX_MSG_MAP(CAboutPage)
	ON_NOTIFY(NM_CLICK, IDC_VersionList, OnClickVersionList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutPage メッセージ ハンドラ

/*----------------------------------------------------------------------------*/
//  概  要：  ロード時に呼ぶ
//  引  数：  void
//  戻り値：  void
//  備  考：  必ず、呼んでください。
/*----------------------------------------------------------------------------*/
void CAboutPage::Load()
{
	/* リストビューの初期化 */
	// 一行選択にする
	m_cnList.SetExtendedStyle(LVS_EX_FULLROWSELECT);	

	// 行の追加
	int i = 0;
	m_cnList.InsertColumn( i++ , "Name", LVCFMT_LEFT , 100 , -1);
	m_cnList.InsertColumn( i++ , "Ver", LVCFMT_LEFT , 50 , -1);

	// 各DLLのバージョンを追加
	SetVersion("UNZIP32.DLL",UnzipGetVersion());
	SetVersion("ZIP32J.DLL",ZipGetVersion());
	IsDll("ZIP32.DLL");
}

/*----------------------------------------------------------------------------*/
//  概  要：  Unzip32.dllのバージョンを取得する
//  引  数：  なし
//  戻り値：  バージョン * 100
//  備  考：  void
/*----------------------------------------------------------------------------*/
WORD CAboutPage::UnzipGetVersion()
{
	HINSTANCE hLib = ::LoadLibrary("Unzip32.dll");
	typedef WORD (GetVersion)(VOID);

	if(hLib == NULL){return -1;}
	GetVersion *pGetVersion = (GetVersion*)::GetProcAddress(hLib ,"UnZipGetVersion");

	int nVersion = 0;
	nVersion = pGetVersion();
	::FreeLibrary(hLib);

	return nVersion;
}

/*----------------------------------------------------------------------------*/
//  概  要：  DLL等のバージョンを表示する
//  引  数：  DLLの名前 , バージョン*100
//  戻り値：  成功:0
//  備  考：  voif
/*----------------------------------------------------------------------------*/
int CAboutPage::SetVersion(LPCTSTR lpName, int nVersion)
{
	CString cVersion;

	cVersion.Format("v.%.2f",(double)nVersion / 100);

	int nIndex = m_cnList.InsertItem(0,lpName,NULL);
	m_cnList.SetItem(nIndex , 1 , LVIF_TEXT , cVersion , 0 ,0 , 0 ,0);
	return 0;
}

/*----------------------------------------------------------------------------*/
//  概  要：  Zip32j.dllのバージョンを取得する
//  引  数：  なし
//  戻り値：  バージョン * 100
//  備  考：  void
/*----------------------------------------------------------------------------*/
WORD CAboutPage::ZipGetVersion()
{
	HINSTANCE hLib = ::LoadLibrary("Zip32j.dll");
	typedef WORD (GetVersion)(VOID);

	if(hLib == NULL){return -1;}
	GetVersion *pGetVersion = (GetVersion*)::GetProcAddress(hLib ,"ZipGetVersion");

	int nVersion = 0;
	nVersion = pGetVersion();
	::FreeLibrary(hLib);

	return nVersion;
}

/*----------------------------------------------------------------------------*/
//  概  要：  DLLが導入されているか調べる
//  引  数：  DLLの名前
//  戻り値：  常に0
//  備  考：  なし
/*----------------------------------------------------------------------------*/
int CAboutPage::IsDll(LPCTSTR lpDll)
{
	HINSTANCE hLib = ::LoadLibrary(lpDll);

	LPCTSTR lpState;

	if(hLib != NULL)
	{
		lpState = "導入済";
	}else{
		lpState = "未導入";
	}

	// リストビューに追加
	int nIndex = m_cnList.InsertItem(0,lpDll,NULL);
	m_cnList.SetItem(nIndex , 1 , LVIF_TEXT , lpState , 0 ,0 , 0 ,0);

	::FreeLibrary(hLib);
	return 0;
}


/*----------------------------------------------------------------------------*/
//  概  要：  選択されたDLLの情報を表示する
//  引  数：  
//  戻り値：  void
//  備  考： ハンドラ関数
/*----------------------------------------------------------------------------*/
void CAboutPage::OnClickVersionList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString cName;
	int nIndex;
	
	nIndex = m_cnList.GetSelectionMark();
	cName = m_cnList.GetItemText(nIndex , 0);
	
	// DLLごとの情報
	/*
	「作者」
	「用途」
	「ホームページ」
	「メールアドレス」
	*/
	CString cInfo;
	if(cName == "UNZIP32.DLL")
	{
		// UNZIP32.dllの場合
		cInfo = "(c)shoda T.\r\n"
				"ZIP書庫の解凍\r\n"
				"http://www.csdinc.co.jp/archiver/\r\n"
				"shoda@csdinc.co.jp";
	}
	else if(cName == "ZIP32J.DLL")
	{
		cInfo = "(c)吉岡 恒夫\r\n"
				"ZIP書庫の圧縮\r\n"
				"http://openlab.ring.gr.jp/tsuneo/zip32j/\r\n"
				"tsuneo@rr.iij4u.or.jp";
	}
	else if(cName == "ZIP32.DLL")
	{
		cInfo = "(c)Info-ZIP\r\n"
				"ZIP書庫の圧縮\r\n"
				"http://www.info-zip.org/pub/infozip/";
	}

					

	// 情報を表示
	m_cnDllInfo.SetWindowText(cInfo);
	*pResult = 0;
}
