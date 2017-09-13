#if !defined(AFX_MAINPAGE_H__30B8BABB_EB4E_4CDC_9CD4_D36593F715EF__INCLUDED_)
#define AFX_MAINPAGE_H__30B8BABB_EB4E_4CDC_9CD4_D36593F715EF__INCLUDED_

#include "Folder.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "FoxIni.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMainPage �_�C�A���O

class CMainPage : public CDialog
{
// �R���X�g���N�V����
public:
	CFoxIni *m_pIni;
	virtual int SetFolderOpen(BOOL bStates);
	virtual void SetMode(int nMode);
	~CMainPage();
	virtual int SetIcon(HICON hIcon , CStatic* p_cStatic);
	virtual void AddIcon(void);
	virtual HICON GetIcon(int nIndex);
	CMainPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_MainDlg };
	CComboBox	m_cPathCombo;
	CButton	m_cnFake;
	CStatic	m_cnTrashIcon;
	CStatic	m_cnTaskIcon;
	CStatic	m_cnSubscriptIcon;
	CStatic	m_cnPrinterIcon;
	CStatic	m_cnNetworkIcon;
	CStatic	m_cnMyDocumentIcon;
	CStatic	m_cnMyComputerIcon;
	CStatic	m_cnIeIcon;
	CStatic	m_cnHistoryIcon;
	CStatic	m_cnFavoriteIcon;
	CStatic	m_cnActiveXIcon;
	CStatic	m_cnDialIcon;
	CStatic	m_cnChasheIcon;
	CStatic	m_cnControlIcon;
	CComboBox	m_cnFolder;
	CStatic	m_cnIcon;
	CString	m_cFolder;
	CString	m_cPath;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMainPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual void AddType(void);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CMainPage)
	afx_msg void OnSelchangeFolderCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnControlIcon();
	afx_msg void OnPrinterIcon();
	afx_msg void OnTrashIcon();
	afx_msg void OnNetworkIcon();
	afx_msg void OnDialIcon();
	afx_msg void OnMyConputerIcon();
	afx_msg void OnFavoriteIcon();
	afx_msg void OnMyDocumentIcon();
	afx_msg void OnCacheIcon();
	afx_msg void OnIEIcon();
	afx_msg void OnActiveXIcon();
	afx_msg void OnTaskIcon();
	afx_msg void OnSubscriptIcon();
	afx_msg void OnHistoryIcon();
	afx_msg void OnPathBrowse();
	afx_msg void OnFake();
	afx_msg void OnRelease();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bFolderOpen;
	int m_nMode;
	CFolder *m_pFolder;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAINPAGE_H__30B8BABB_EB4E_4CDC_9CD4_D36593F715EF__INCLUDED_)
