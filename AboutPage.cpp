// AboutPage.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "Fox.h"
#include "AboutPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutPage �_�C�A���O


CAboutPage::CAboutPage(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutPage)
	m_cInfo = _T("");
	//}}AFX_DATA_INIT
	m_cInfo = "hilo-m@mb.nma.ne.jp\r\nhttp://www.mb.nma.ne.jp/~hilo-m/";
}


void CAboutPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPage)
	DDX_Control(pDX, IDC_DllInfoEdit, m_cnDllInfo);
	DDX_Control(pDX, IDC_VersionList, m_cnList);
	DDX_Text(pDX, IDC_InfoEdit, m_cInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutPage, CDialog)
	//{{AFX_MSG_MAP(CAboutPage)
	ON_NOTIFY(NM_CLICK, IDC_VersionList, OnClickVersionList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutPage ���b�Z�[�W �n���h��

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ���[�h���ɌĂ�
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �K���A�Ă�ł��������B
/*----------------------------------------------------------------------------*/
void CAboutPage::Load()
{
	/* ���X�g�r���[�̏����� */
	// ��s�I���ɂ���
	m_cnList.SetExtendedStyle(LVS_EX_FULLROWSELECT);	

	// �s�̒ǉ�
	int i = 0;
	m_cnList.InsertColumn( i++ , "Name", LVCFMT_LEFT , 100 , -1);
	m_cnList.InsertColumn( i++ , "Ver", LVCFMT_LEFT , 50 , -1);

	// �eDLL�̃o�[�W������ǉ�
	SetVersion("UNZIP32.DLL",UnzipGetVersion());
	SetVersion("ZIP32J.DLL",ZipGetVersion());
	IsDll("ZIP32.DLL");
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  Unzip32.dll�̃o�[�W�������擾����
//  ��  ���F  �Ȃ�
//  �߂�l�F  �o�[�W���� * 100
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
WORD CAboutPage::UnzipGetVersion()
{
	HINSTANCE hLib = ::LoadLibrary("Unzip32.dll");
	typedef WORD (GetVersion)(VOID);

	if(hLib == NULL){return -1;}
	GetVersion *pGetVersion = (GetVersion*)::GetProcAddress(hLib ,"UnZipGetVersion");

	int nVersion = 0;
	nVersion = pGetVersion();
	::FreeLibrary(hLib);

	return nVersion;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  DLL���̃o�[�W������\������
//  ��  ���F  DLL�̖��O , �o�[�W����*100
//  �߂�l�F  ����:0
//  ��  �l�F  voif
/*----------------------------------------------------------------------------*/
int CAboutPage::SetVersion(LPCTSTR lpName, int nVersion)
{
	CString cVersion;

	cVersion.Format("v.%.2f",(double)nVersion / 100);

	int nIndex = m_cnList.InsertItem(0,lpName,NULL);
	m_cnList.SetItem(nIndex , 1 , LVIF_TEXT , cVersion , 0 ,0 , 0 ,0);
	return 0;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  Zip32j.dll�̃o�[�W�������擾����
//  ��  ���F  �Ȃ�
//  �߂�l�F  �o�[�W���� * 100
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
WORD CAboutPage::ZipGetVersion()
{
	HINSTANCE hLib = ::LoadLibrary("Zip32j.dll");
	typedef WORD (GetVersion)(VOID);

	if(hLib == NULL){return -1;}
	GetVersion *pGetVersion = (GetVersion*)::GetProcAddress(hLib ,"ZipGetVersion");

	int nVersion = 0;
	nVersion = pGetVersion();
	::FreeLibrary(hLib);

	return nVersion;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  DLL����������Ă��邩���ׂ�
//  ��  ���F  DLL�̖��O
//  �߂�l�F  ���0
//  ��  �l�F  �Ȃ�
/*----------------------------------------------------------------------------*/
int CAboutPage::IsDll(LPCTSTR lpDll)
{
	HINSTANCE hLib = ::LoadLibrary(lpDll);

	LPCTSTR lpState;

	if(hLib != NULL)
	{
		lpState = "������";
	}else{
		lpState = "������";
	}

	// ���X�g�r���[�ɒǉ�
	int nIndex = m_cnList.InsertItem(0,lpDll,NULL);
	m_cnList.SetItem(nIndex , 1 , LVIF_TEXT , lpState , 0 ,0 , 0 ,0);

	::FreeLibrary(hLib);
	return 0;
}


/*----------------------------------------------------------------------------*/
//  �T  �v�F  �I�����ꂽDLL�̏���\������
//  ��  ���F  
//  �߂�l�F  void
//  ��  �l�F �n���h���֐�
/*----------------------------------------------------------------------------*/
void CAboutPage::OnClickVersionList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString cName;
	int nIndex;
	
	nIndex = m_cnList.GetSelectionMark();
	cName = m_cnList.GetItemText(nIndex , 0);
	
	// DLL���Ƃ̏��
	/*
	�u��ҁv
	�u�p�r�v
	�u�z�[���y�[�W�v
	�u���[���A�h���X�v
	*/
	CString cInfo;
	if(cName == "UNZIP32.DLL")
	{
		// UNZIP32.dll�̏ꍇ
		cInfo = "(c)shoda T.\r\n"
				"ZIP���ɂ̉�\r\n"
				"http://www.csdinc.co.jp/archiver/\r\n"
				"shoda@csdinc.co.jp";
	}
	else if(cName == "ZIP32J.DLL")
	{
		cInfo = "(c)�g�� �P�v\r\n"
				"ZIP���ɂ̈��k\r\n"
				"http://openlab.ring.gr.jp/tsuneo/zip32j/\r\n"
				"tsuneo@rr.iij4u.or.jp";
	}
	else if(cName == "ZIP32.DLL")
	{
		cInfo = "(c)Info-ZIP\r\n"
				"ZIP���ɂ̈��k\r\n"
				"http://www.info-zip.org/pub/infozip/";
	}

					

	// ����\��
	m_cnDllInfo.SetWindowText(cInfo);
	*pResult = 0;
}
