// FoxDlg.h : ヘッダー ファイル
//

#if !defined(AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_)
#define AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_

#include "MainPage.h"	// ClassView によって追加されました。
#include "AboutPage.h"	// ClassView によって追加されました。
#include "SettingPage.h"	// ClassView によって追加されました。
#include "FoxIni.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CFoxDlg ダイアログ

class CFoxDlg : public CDialog
{
// 構築
public:
	virtual void LoadSetting();
	CFoxDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
// ダイアログ データ
	//{{AFX_DATA(CFoxDlg)
	enum { IDD = IDD_FOX_DIALOG };
	CTabCtrl	m_cnTab;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual void SaveSetting();
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeMainTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingMainTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnApplyButton();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFoxIni m_cIni;
	CSettingPage m_cSetting;
	CMainPage m_cMain;
	CAboutPage m_cAbout;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_)
