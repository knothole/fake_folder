#if !defined(AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_)
#define AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAboutPage �_�C�A���O

class CAboutPage : public CDialog
{
// �R���X�g���N�V����
public:
	virtual int IsDll(LPCTSTR lpDll);
	virtual WORD ZipGetVersion(void);
	virtual WORD UnzipGetVersion(void);
	virtual void Load(void);
	CAboutPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutPage)
	enum { IDD = IDD_AboutDlg };
	CEdit	m_cnDllInfo;
	CListCtrl	m_cnList;
	CString	m_cInfo;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual int SetVersion(LPCTSTR lpName , int nVersion);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAboutPage)
	afx_msg void OnClickVersionList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ABOUTPAGE_H__ABF0B7B2_E34B_4A94_AD36_9F495DB12451__INCLUDED_)
