// MainPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Fox.h"
#include "MainPage.h"
#include "RegEdit.h"
#include "SpecialFolder.h"
#include "ShellControl.h"
#include "Folder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainPage ダイアログ


CMainPage::CMainPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMainPage::IDD, pParent),m_nMode(0)
{
	//{{AFX_DATA_INIT(CMainPage)
	m_cFolder = _T("");
	m_cPath = _T("");
	//}}AFX_DATA_INIT
	m_pFolder = new CFolder;
	m_pFolder ->Load();
}


void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainPage)
	DDX_Control(pDX, IDC_PathCombo, m_cPathCombo);
	DDX_Control(pDX, IDC_Fake, m_cnFake);
	DDX_Control(pDX, IDC_TrashIcon, m_cnTrashIcon);
	DDX_Control(pDX, IDC_TaskIcon, m_cnTaskIcon);
	DDX_Control(pDX, IDC_SubscriptIcon, m_cnSubscriptIcon);
	DDX_Control(pDX, IDC_PrinterIcon, m_cnPrinterIcon);
	DDX_Control(pDX, IDC_NetworkIcon, m_cnNetworkIcon);
	DDX_Control(pDX, IDC_MyDocumentIcon, m_cnMyDocumentIcon);
	DDX_Control(pDX, IDC_MyConputerIcon, m_cnMyComputerIcon);
	DDX_Control(pDX, IDC_IEIcon, m_cnIeIcon);
	DDX_Control(pDX, IDC_HistoryIcon, m_cnHistoryIcon);
	DDX_Control(pDX, IDC_FavoriteIcon, m_cnFavoriteIcon);
	DDX_Control(pDX, IDC_ActiveXIcon, m_cnActiveXIcon);
	DDX_Control(pDX, IDC_DialIcon, m_cnDialIcon);
	DDX_Control(pDX, IDC_CacheIcon, m_cnChasheIcon);
	DDX_Control(pDX, IDC_ControlIcon, m_cnControlIcon);
	DDX_Control(pDX, IDC_FolderCombo, m_cnFolder);
	DDX_Control(pDX, IDC_Icon, m_cnIcon);
	DDX_CBString(pDX, IDC_FolderCombo, m_cFolder);
	DDX_CBString(pDX, IDC_PathCombo, m_cPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainPage, CDialog)
	//{{AFX_MSG_MAP(CMainPage)
	ON_CBN_SELCHANGE(IDC_FolderCombo, OnSelchangeFolderCombo)
	ON_BN_CLICKED(IDC_ControlIcon, OnControlIcon)
	ON_BN_CLICKED(IDC_PrinterIcon, OnPrinterIcon)
	ON_BN_CLICKED(IDC_TrashIcon, OnTrashIcon)
	ON_BN_CLICKED(IDC_NetworkIcon, OnNetworkIcon)
	ON_BN_CLICKED(IDC_DialIcon, OnDialIcon)
	ON_BN_CLICKED(IDC_MyConputerIcon, OnMyConputerIcon)
	ON_BN_CLICKED(IDC_FavoriteIcon, OnFavoriteIcon)
	ON_BN_CLICKED(IDC_MyDocumentIcon, OnMyDocumentIcon)
	ON_BN_CLICKED(IDC_CacheIcon, OnCacheIcon)
	ON_BN_CLICKED(IDC_IEIcon, OnIEIcon)
	ON_BN_CLICKED(IDC_ActiveXIcon, OnActiveXIcon)
	ON_BN_CLICKED(IDC_TaskIcon, OnTaskIcon)
	ON_BN_CLICKED(IDC_SubscriptIcon, OnSubscriptIcon)
	ON_BN_CLICKED(IDC_HistoryIcon, OnHistoryIcon)
	ON_BN_CLICKED(IDC_PathBrowse, OnPathBrowse)
	ON_BN_CLICKED(IDC_Fake, OnFake)
	ON_BN_CLICKED(IDC_Release, OnRelease)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainPage メッセージ ハンドラ

void CMainPage::OnSelchangeFolderCombo() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nIndex = m_cnFolder.GetCurSel();

	// 特殊フォルダのアイコンを取得する
	HICON hIcon = GetIcon(nIndex); 

	// もし、アイコンが存在しないのなら、[偽装]を無効にする
	if(hIcon == NULL)
	{
		m_cnFake.EnableWindow(FALSE);
	}else{
		m_cnFake.EnableWindow(TRUE);
	}

	// アイコンを表示する
	SetIcon(hIcon , &m_cnIcon);

}

/*----------------------------------------------------------------------------*/
//  概  要：  CMainPageの初期化
//  引  数：  なし
//  戻り値：  しらん
//  備  考：  ビバ!MFC!
/*----------------------------------------------------------------------------*/
BOOL CMainPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	AddType();
	AddIcon();

	CString cBuf;
	for(int i = 0 ; i < 20;i++)
	{
		cBuf = m_pIni->GetHistory(i);

		if(cBuf == _T(""))
		{
			break;
		}
		m_cPathCombo.InsertString(i,cBuf);
	}
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

/*----------------------------------------------------------------------------*/
//  概  要：  指定された特殊フォルダのアイコンハンドルを取得する
//  引  数：  特殊フォルダのインデックス
//  戻り値：  アイコンをハンドル
//  備  考：  なし
/*----------------------------------------------------------------------------*/
HICON CMainPage::GetIcon(int nIndex)
{
	CString cId;
	CRegEdit cEdit;

	cId = m_pFolder ->GetID(nIndex);
	// レジストリから読みとる
	CString cIcon;
	if(cEdit.Open(HKEY_CLASSES_ROOT,_T("CLSID\\")+cId+_T("\\DefaultIcon")) != ERROR_SUCCESS )
	{
		return NULL;
	}
	
	cIcon = cEdit.Read(_T(""));

	if(cEdit.Close() != ERROR_SUCCESS ){ return NULL;}

	// アイコンをファイルから取得する
	// レジストリには"c:\win.exe, 5"という形で保存されているので、インデックスとファイル名を分ける
	CString cFile , cIndex;
	int i;

	i = cIcon.Find(_T(","));
	cFile = cIcon.Left(i);
	cIndex = cIcon.Right(cIcon.GetLength() - i -1);

	// ファイルから読みとる
	HICON hIcon;
	::ExtractIconEx(cFile , atoi(cIndex) , &hIcon , NULL , 1);


	return hIcon;
}

/*----------------------------------------------------------------------------*/
//  概  要：  コンボボックスに特殊フォルダ名を追加する
//  引  数：  void
//  戻り値：  void
//  備  考：  便宜上の分割
/*----------------------------------------------------------------------------*/
void CMainPage::AddType()
{
	LPCTSTR lpFolder;

	for(int i = 0 ; i < LAST ; i++)
	{
		switch(i)
		{
		case CONTROL:
			lpFolder = _T("コントロールパネル");
			break;
		
		case PRINTER:
			lpFolder = _T("プリンタ");
			break;
		
		case TRASH:
			lpFolder = _T("ごみ箱");
			break;

		case NETWORK:
			lpFolder = _T("ネットワークコンピュータ");
			break;

		case DIAL_UP:
			lpFolder = _T("ダイヤルアップネットワーク");
			break;
		
		case MY_COMPUTER:
			lpFolder = _T("マイコンピュータ");
			break;

		case FAVORITE:
			lpFolder = _T("お気に入り");
			break;
	
		case MY_DOCUMENT:
			lpFolder = _T("マイドキュメント");
			break;
		case CACHE:
			lpFolder = _T("インターネットキャッシュ");
			break;
		
		case IE:
			lpFolder = _T("インターネットエクスプローラ");
			break;
	
		case ACTIVE_X:
			lpFolder = _T("ActiveXキャッシュフォルダ");
			break;
		case TASK:
			lpFolder = _T("タスク");
			break;

		case SUBSCRIPT:
			lpFolder = _T("購読");
			break;

		case HISTORY:
			lpFolder = _T("履歴");
			break;
		
		}
		m_cnFolder.InsertString(i,lpFolder);
	}

	// 適当なのを選択
	m_cnFolder.SetCurSel(0);
	m_cnIcon.SetIcon(GetIcon(0));
}

/*----------------------------------------------------------------------------*/
//  概  要：  特殊フォルダのアイコンを表示する
//  引  数：  void
//  戻り値：  void
//  備  考：  void
/*----------------------------------------------------------------------------*/
void CMainPage::AddIcon()
{
	HICON hIcon;

	for(int i = 0 ; i < LAST ; i++)
	{

		hIcon = GetIcon(i);

		switch(i)
		{
		case CONTROL:
			SetIcon(hIcon , &m_cnControlIcon);
			break;
		case PRINTER:
			SetIcon(hIcon , &m_cnPrinterIcon);
			break;
		
		case TRASH:
			SetIcon(hIcon , &m_cnTrashIcon);
			break;

		case NETWORK:
			SetIcon(hIcon , &m_cnNetworkIcon);
			break;

		case DIAL_UP:
			SetIcon(hIcon , &m_cnDialIcon);
			break;
		
		case MY_COMPUTER:
			SetIcon(hIcon , &m_cnMyComputerIcon);
			break;

		case FAVORITE:
			SetIcon(hIcon , &m_cnFavoriteIcon);
			break;
	
		case MY_DOCUMENT:
			SetIcon(hIcon , &m_cnMyDocumentIcon);
			break;

		case CACHE:
			SetIcon(hIcon , &m_cnChasheIcon);
			break;
		
		case IE:
			SetIcon(hIcon , &m_cnIeIcon);
			break;
	
		case ACTIVE_X:
			SetIcon(hIcon , &m_cnActiveXIcon);
			break;

		case TASK:
			SetIcon(hIcon , &m_cnTaskIcon);
			break;

		case SUBSCRIPT:
			SetIcon(hIcon , &m_cnSubscriptIcon);
			break;

		case HISTORY:
			SetIcon(hIcon , &m_cnHistoryIcon);
			break;
		}
	}
}

void CMainPage::OnControlIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(CONTROL);
	OnSelchangeFolderCombo();
}

void CMainPage::OnPrinterIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(PRINTER);
	OnSelchangeFolderCombo();
}

void CMainPage::OnTrashIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(TRASH);
	OnSelchangeFolderCombo();
}

void CMainPage::OnNetworkIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(NETWORK);
	OnSelchangeFolderCombo();
	
}

void CMainPage::OnDialIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(DIAL_UP);
	OnSelchangeFolderCombo();
}

void CMainPage::OnMyConputerIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(MY_COMPUTER);
	OnSelchangeFolderCombo();
}

void CMainPage::OnFavoriteIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(FAVORITE);
	OnSelchangeFolderCombo();
}

void CMainPage::OnMyDocumentIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(MY_DOCUMENT);
	OnSelchangeFolderCombo();
}

void CMainPage::OnCacheIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(CACHE);
	OnSelchangeFolderCombo();	
}

void CMainPage::OnIEIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(IE);
	OnSelchangeFolderCombo();
}

void CMainPage::OnActiveXIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(ACTIVE_X);
	OnSelchangeFolderCombo();
}

void CMainPage::OnTaskIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(TASK);
	OnSelchangeFolderCombo();
	
}

void CMainPage::OnSubscriptIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(SUBSCRIPT);
	OnSelchangeFolderCombo();
}

void CMainPage::OnHistoryIcon() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_cnFolder.SetCurSel(HISTORY);
	OnSelchangeFolderCombo();
}

/*----------------------------------------------------------------------------*/
//  概  要：  アイコンを表示する
//  引  数：  アイコンのハンドル , 表示するコントロールのポインタ
//  戻り値：  成功 -- 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CMainPage::SetIcon(HICON hIcon, CStatic *p_cStatic)
{
	// アイコンがないなら、既定のアイコンを表示する
	if(hIcon == NULL)
	{
		// アイコンのロード
		hIcon = AfxGetApp() ->LoadIcon(IDI_NOTFOUND);
	
		// コントロールを無効にする
		p_cStatic ->EnableWindow(FALSE);
	}

	// アイコンを表示
	p_cStatic ->SetIcon(hIcon);
	return 0;

}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダを参照する
//  引  数：  void
//  戻り値：  void
//  備  考：  ハンドラ関数
/*----------------------------------------------------------------------------*/
void CMainPage::OnPathBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CShellControl cShell;

	// [フォルダの参照ダイアログの表示]
	CString cPath;
	cPath = cShell.RefFolder(this->GetSafeHwnd());

	if(cPath != "")
	{
		// キャンセルされていない場合
		m_cPath = cPath;
		UpdateData(FALSE);
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  デストラクタ
//  引  数：  
//  戻り値：  
//  備  考：  
/*----------------------------------------------------------------------------*/
CMainPage::~CMainPage()
{
	delete m_pFolder;
}

/*----------------------------------------------------------------------------*/
//  概  要：  偽装を行う
//  引  数：  void
//  戻り値：  void
//  備  考：  ハンドラ関数
/*----------------------------------------------------------------------------*/
void CMainPage::OnFake() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();
	CString cBuf;
	int nRes = m_pFolder ->Fake(m_cPath ,cBuf, m_cnFolder.GetCurSel() , m_nMode);

	// エラー処理
	switch(nRes)
	{
	case F_FILE:
		AfxMessageBox(_T("ファイルは処理できません。"));
		break;
	case F_SUCUESS:
		AfxMessageBox(_T("成功。"));

		m_cPath = cBuf;
		if(m_cPathCombo.FindStringExact(-1,m_cPath) == CB_ERR)
		{
			m_cPathCombo.InsertString(-1,m_cPath);
		}

		// 選択をする
		int nIndex = m_cPathCombo.FindStringExact(-1,m_cPath);
		m_cPathCombo.SetCurSel(nIndex);
		
		break;
	}

	UpdateData(FALSE);
}

/*----------------------------------------------------------------------------*/
//  概  要：  解除を行う
//  引  数：  void
//  戻り値：  void
//  備  考：  ハンドラ関数
/*----------------------------------------------------------------------------*/
void CMainPage::OnRelease() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();

	// 解除
	CString cBuf;
	int nRes = m_pFolder ->Release(m_cPath , cBuf , m_nMode);

	switch(nRes)
	{
	case F_FILE:
		AfxMessageBox(_T("ファイルは処理できません。"));
		break;
	case F_PASSERORR:
		//AfxMessageBox(_T("パスワードが違います。"))
		break;
	case F_SAMENAME:
		AfxMessageBox(_T("このフォルダは、偽装されていません。"));
		break;
	case F_CANCEL:
		break;
	case F_ERROR:
		AfxMessageBox(_T("未知のエラーです。"));
		break;
	case F_SUCUESS:
		AfxMessageBox(_T("成功。"));

		m_cPath = cBuf;
		int i=m_cPathCombo.FindStringExact(-1,m_cPath); 
		if(i == CB_ERR)
		{
			m_cPathCombo.InsertString(-1,m_cPath);
		}		
		
		// 選択をする
		int nIndex = m_cPathCombo.FindStringExact(-1,m_cPath);
		m_cPathCombo.SetCurSel(nIndex);
		// フォルダを開く設定なら、開く
		if(m_bFolderOpen == TRUE)
		{
			::ShellExecute(NULL , "open" , cBuf , NULL , NULL , SW_SHOWNORMAL);
		}

		break;
	}
//	UpdateData(FALSE);
}

void CMainPage::SetMode(int nMode)
{
	m_nMode = nMode;

}

/*----------------------------------------------------------------------------*/
//  概  要：  解除後フォルダを開くかどうかの設定
//  引  数：  開く == TRUE
//  戻り値：  0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CMainPage::SetFolderOpen(BOOL bStates)
{
	m_bFolderOpen = bStates;
	return 0;
}

void CMainPage::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください

	CString cBuf;
	for(int i=0;i < m_cPathCombo.GetCount();i++)
	{
		if(i > 20)
		{
			break;
		}

		m_cPathCombo.GetLBText(i,cBuf);
		
		m_pIni->SaveHistory(i,cBuf);
	}
}
