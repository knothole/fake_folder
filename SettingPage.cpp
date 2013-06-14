// SettingPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Fox.h"
#include "SettingPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingPage ダイアログ


CSettingPage::CSettingPage(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingPage)
	m_bCompatible = FALSE;
	m_bPassword = FALSE;
	m_bOpenFolder = FALSE;
	//}}AFX_DATA_INIT
}


void CSettingPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingPage)
	DDX_Control(pDX, IDC_PasswordCheck, m_cnPassword);
	DDX_Control(pDX, IDC_CompatibleCheck, m_cnCompatible);
	DDX_Check(pDX, IDC_CompatibleCheck, m_bCompatible);
	DDX_Check(pDX, IDC_PasswordCheck, m_bPassword);
	DDX_Check(pDX, IDC_OpenFolder, m_bOpenFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingPage, CDialog)
	//{{AFX_MSG_MAP(CSettingPage)
	ON_BN_CLICKED(IDC_CompatibleCheck, OnCompatibleCheck)
	ON_BN_CLICKED(IDC_PasswordCheck, OnPasswordCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingPage メッセージ ハンドラ

void CSettingPage::OnCompatibleCheck() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();
	
	if(m_bCompatible == TRUE)
	{
		m_cnPassword.EnableWindow(FALSE);
	}else{
		m_cnPassword.EnableWindow(TRUE);
	}
}

void CSettingPage::OnPasswordCheck() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData();

	if(m_bPassword == TRUE)
	{
		m_cnCompatible.EnableWindow(FALSE);
	}else{
		m_cnCompatible.EnableWindow(TRUE);
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  パスワードを使用するが使えるかのチェック
//  引  数：  void
//  戻り値：  使える == TRUE
//  備  考：  
/*----------------------------------------------------------------------------*/
BOOL CSettingPage::CheckPass()
{
	// UNZIP32.DLL・ZIP32.DLL・ZIP32J.ZLLがあるか確認する
	HINSTANCE hLib[3];
	BOOL bRes = TRUE;

	hLib[0] = ::LoadLibrary("Unzip32.dll");
	hLib[1] = ::LoadLibrary("Zip32.dll");
	hLib[2] = ::LoadLibrary("Zip32j.dll");

	for(int i= 0 ; i < 3 ; i++)
	{
		if(hLib[i] == NULL)
		{
			bRes = FALSE;
		}
	}	
		
	::FreeLibrary(hLib[0]);
	::FreeLibrary(hLib[1]);
	::FreeLibrary(hLib[2]);

	return bRes;
}

/*----------------------------------------------------------------------------*/
//  概  要：  いろんな設定をする
//  引  数：  void
//  戻り値：  void
//  備  考：  実体化したときに呼ぶこと
/*----------------------------------------------------------------------------*/
void CSettingPage::Load()
{
	UpdateData();
	// 制限
	if(CheckPass() == TRUE)
	{
		m_cnPassword.EnableWindow(FALSE);
	}else{
		m_cnPassword.EnableWindow(TRUE);
	}

	// チェック状態によるボタンの有効・無効
	if(m_bCompatible == TRUE)
	{
		m_cnPassword.EnableWindow(FALSE);
	}else{
		m_cnPassword.EnableWindow(TRUE);
	}

	if(m_bPassword == TRUE)
	{
		m_cnCompatible.EnableWindow(FALSE);
	}else{
		m_cnCompatible.EnableWindow(TRUE);
	}
}
