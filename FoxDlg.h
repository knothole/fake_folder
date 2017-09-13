// FoxDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_)
#define AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_

#include "MainPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "AboutPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "SettingPage.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "FoxIni.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CFoxDlg �_�C�A���O

class CFoxDlg : public CDialog
{
// �\�z
public:
	virtual void LoadSetting();
	CFoxDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CFoxDlg)
	enum { IDD = IDD_FOX_DIALOG };
	CTabCtrl	m_cnTab;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual void SaveSetting();
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FOXDLG_H__99D5B89D_A91F_45EA_A74F_BBC1D3ADB7E8__INCLUDED_)
