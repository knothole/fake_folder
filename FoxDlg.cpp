// FoxDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Fox.h"
#include "FoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
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
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFoxDlg ダイアログ

CFoxDlg::CFoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFoxDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFoxDlg)
	DDX_Control(pDX, IDC_MainTab, m_cnTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFoxDlg, CDialog)
	//{{AFX_MSG_MAP(CFoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MainTab, OnSelchangeMainTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_MainTab, OnSelchangingMainTab)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ApplyButton, OnApplyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFoxDlg メッセージ ハンドラ

BOOL CFoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
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

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	// 初期化
	LoadSetting();

	TC_ITEM sItem;	// タブアイテム構造体

	// タブコントロールに項目の追加
	for(int i = 0 ; i < 3 ; i++)
	{
		sItem.mask = TCIF_TEXT;

		switch(i)
		{
		case 0:
			sItem.pszText = "Main";
			break;
		case 1:
			sItem.pszText = "設定";
			break;
		case 2:
			sItem.pszText = "About";
			break;
		}
		m_cnTab.InsertItem( i ,&sItem);
	}

	m_cMain.m_pIni = &m_cIni;
	// 各タブページを描画
	m_cMain.Create(IDD_MainDlg , &m_cnTab);
	m_cSetting.Create(IDD_SettingDlg   , &m_cnTab);
	m_cAbout.Create(IDD_AboutDlg , &m_cnTab);
	
	
	// 初期化
	m_cAbout.Load();

	// 初期表示状態の設定
	m_cMain.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_SHOWWINDOW);
	m_cSetting.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_HIDEWINDOW);
	m_cAbout.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_HIDEWINDOW);

	// 各ページの初期化
	m_cSetting.Load();

	// D&Dの受け取りを許可する
	DragAcceptFiles(TRUE);
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CFoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CFoxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CFoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFoxDlg::OnSelchangeMainTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int inIndex = m_cnTab.GetCurSel();	// 切り替え後のタブのインデックス

	// 選択されたタブのみ表示する
	switch(inIndex)
	{
	case 0:
		m_cMain.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_cSetting.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_cAbout.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CFoxDlg::OnSelchangingMainTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
		int inIndex = m_cnTab.GetCurSel();	// 切り替え後のタブのインデックス

	// 選択されたタブのみ表示する
	switch(inIndex)
	{
	case 0:
		m_cMain.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_cSetting.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_cAbout.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}

void CFoxDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	char chBuf[MAX_PATH + 1];

	// フォルダは、一個しか受け取らない
	::DragQueryFile(  hDropInfo, 0, chBuf, 1024);

	m_cMain.m_cPathCombo.SetWindowText(chBuf);
	CDialog::OnDropFiles(hDropInfo);
}

void CFoxDlg::OnApplyButton() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	SaveSetting();
	LoadSetting();
}

/*----------------------------------------------------------------------------*/
//  概  要：  設定をINIファイルに保存する
//  引  数：  void
//  戻り値：  void
//  備  考：  void
/*----------------------------------------------------------------------------*/
void CFoxDlg::SaveSetting()
{
	m_cSetting.UpdateData();
	m_cIni.SetCompatible(m_cSetting.m_bCompatible);
	m_cIni.SetPassword	(m_cSetting.m_bPassword);
	m_cIni.SetOpenFolder(m_cSetting.m_bOpenFolder);
}

/*----------------------------------------------------------------------------*/
//  概  要：  設定をINIファイルから読みとる
//  引  数：  void
//  戻り値：  void
//  備  考：  void
/*----------------------------------------------------------------------------*/
void CFoxDlg::LoadSetting()
{
	// FakeFolder 0.2x互換
	if(m_cIni.GetCompatible() == TRUE)
	{
		m_cSetting.m_bCompatible = TRUE;
		m_cMain.SetMode(F_COMPATIBLE);
	}else{
		m_cSetting.m_bCompatible = FALSE;
		m_cMain.SetMode(F_NORMAL);
	}
	
	// パスワードを使用する
	if(m_cIni.GetPassword() == TRUE)
	{
		m_cSetting.m_bPassword = TRUE;
		m_cMain.SetMode(F_PASSWORD);
	}else{
		m_cSetting.m_bPassword = FALSE;
		m_cMain.SetMode(F_NORMAL);
	}

	// 解除後フォルダを開く
	if(m_cIni.GetOpenFolder() == TRUE)
	{
		m_cSetting.m_bOpenFolder = TRUE;
		m_cMain.SetFolderOpen(TRUE);
	}else{
		m_cSetting.m_bOpenFolder = FALSE;
		m_cMain.SetFolderOpen(FALSE);
	}

}

void CFoxDlg::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	SaveSetting();
	CDialog::OnOK();
}
