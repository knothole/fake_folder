// SettingPage.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CSettingPage �_�C�A���O


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
// CSettingPage ���b�Z�[�W �n���h��

void CSettingPage::OnCompatibleCheck() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
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
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();

	if(m_bPassword == TRUE)
	{
		m_cnCompatible.EnableWindow(FALSE);
	}else{
		m_cnCompatible.EnableWindow(TRUE);
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �p�X���[�h���g�p���邪�g���邩�̃`�F�b�N
//  ��  ���F  void
//  �߂�l�F  �g���� == TRUE
//  ��  �l�F  
/*----------------------------------------------------------------------------*/
BOOL CSettingPage::CheckPass()
{
	// UNZIP32.DLL�EZIP32.DLL�EZIP32J.ZLL�����邩�m�F����
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
//  �T  �v�F  �����Ȑݒ������
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  ���̉������Ƃ��ɌĂԂ���
/*----------------------------------------------------------------------------*/
void CSettingPage::Load()
{
	UpdateData();
	// ����
	if(CheckPass() == TRUE)
	{
		m_cnPassword.EnableWindow(FALSE);
	}else{
		m_cnPassword.EnableWindow(TRUE);
	}

	// �`�F�b�N��Ԃɂ��{�^���̗L���E����
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
