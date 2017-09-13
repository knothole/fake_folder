#if !defined(AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_)
#define AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSettingPage �_�C�A���O

class CSettingPage : public CDialog
{
// �R���X�g���N�V����
public:
	virtual void Load();
	CSettingPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSettingPage)
	enum { IDD = IDD_SettingDlg };
	CButton	m_cnPassword;
	CButton	m_cnCompatible;
	BOOL	m_bCompatible;
	BOOL	m_bPassword;
	BOOL	m_bOpenFolder;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSettingPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual BOOL CheckPass(void);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSettingPage)
	afx_msg void OnCompatibleCheck();
	afx_msg void OnPasswordCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETTINGPAGE_H__71600FFA_6968_4ACD_930A_4E7F8A674260__INCLUDED_)
