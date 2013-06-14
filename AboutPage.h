#if !defined(AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_)
#define AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutPage.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAboutPage ダイアログ

class CAboutPage : public CDialog
{
// コンストラクション
public:
	virtual int IsDll(LPCTSTR lpDll);
	virtual WORD ZipGetVersion(void);
	virtual WORD UnzipGetVersion(void);
	virtual void Load(void);
	CAboutPage(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAboutPage)
	enum { IDD = IDD_AboutDlg };
	CEdit	m_cnDllInfo;
	CListCtrl	m_cnList;
	CString	m_cInfo;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual int SetVersion(LPCTSTR lpName , int nVersion);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAboutPage)
	afx_msg void OnClickVersionList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_)
