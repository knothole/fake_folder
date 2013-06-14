#if !defined(AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_)
#define AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingPage.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSettingPage ダイアログ

class CSettingPage : public CDialog
{
// コンストラクション
public:
	virtual void Load();
	CSettingPage(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSettingPage)
	enum { IDD = IDD_SettingDlg };
	CButton	m_cnPassword;
	CButton	m_cnCompatible;
	BOOL	m_bCompatible;
	BOOL	m_bPassword;
	BOOL	m_bOpenFolder;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSettingPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual BOOL CheckPass(void);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSettingPage)
	afx_msg void OnCompatibleCheck();
	afx_msg void OnPasswordCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_)
