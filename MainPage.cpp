// MainPage.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "Fox.h"
#include "MainPage.h"
#include "RegEdit.h"
#include "SpecialFolder.h"
#include "ShellControl.h"
#include "Folder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainPage �_�C�A���O


CMainPage::CMainPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMainPage::IDD, pParent),m_nMode(0)
{
	//{{AFX_DATA_INIT(CMainPage)
	m_cFolder = _T("");
	m_cPath = _T("");
	//}}AFX_DATA_INIT
	m_pFolder = new CFolder;
	m_pFolder ->Load();
}


void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainPage)
	DDX_Control(pDX, IDC_PathCombo, m_cPathCombo);
	DDX_Control(pDX, IDC_Fake, m_cnFake);
	DDX_Control(pDX, IDC_TrashIcon, m_cnTrashIcon);
	DDX_Control(pDX, IDC_TaskIcon, m_cnTaskIcon);
	DDX_Control(pDX, IDC_SubscriptIcon, m_cnSubscriptIcon);
	DDX_Control(pDX, IDC_PrinterIcon, m_cnPrinterIcon);
	DDX_Control(pDX, IDC_NetworkIcon, m_cnNetworkIcon);
	DDX_Control(pDX, IDC_MyDocumentIcon, m_cnMyDocumentIcon);
	DDX_Control(pDX, IDC_MyConputerIcon, m_cnMyComputerIcon);
	DDX_Control(pDX, IDC_IEIcon, m_cnIeIcon);
	DDX_Control(pDX, IDC_HistoryIcon, m_cnHistoryIcon);
	DDX_Control(pDX, IDC_FavoriteIcon, m_cnFavoriteIcon);
	DDX_Control(pDX, IDC_ActiveXIcon, m_cnActiveXIcon);
	DDX_Control(pDX, IDC_DialIcon, m_cnDialIcon);
	DDX_Control(pDX, IDC_CacheIcon, m_cnChasheIcon);
	DDX_Control(pDX, IDC_ControlIcon, m_cnControlIcon);
	DDX_Control(pDX, IDC_FolderCombo, m_cnFolder);
	DDX_Control(pDX, IDC_Icon, m_cnIcon);
	DDX_CBString(pDX, IDC_FolderCombo, m_cFolder);
	DDX_CBString(pDX, IDC_PathCombo, m_cPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainPage, CDialog)
	//{{AFX_MSG_MAP(CMainPage)
	ON_CBN_SELCHANGE(IDC_FolderCombo, OnSelchangeFolderCombo)
	ON_BN_CLICKED(IDC_ControlIcon, OnControlIcon)
	ON_BN_CLICKED(IDC_PrinterIcon, OnPrinterIcon)
	ON_BN_CLICKED(IDC_TrashIcon, OnTrashIcon)
	ON_BN_CLICKED(IDC_NetworkIcon, OnNetworkIcon)
	ON_BN_CLICKED(IDC_DialIcon, OnDialIcon)
	ON_BN_CLICKED(IDC_MyConputerIcon, OnMyConputerIcon)
	ON_BN_CLICKED(IDC_FavoriteIcon, OnFavoriteIcon)
	ON_BN_CLICKED(IDC_MyDocumentIcon, OnMyDocumentIcon)
	ON_BN_CLICKED(IDC_CacheIcon, OnCacheIcon)
	ON_BN_CLICKED(IDC_IEIcon, OnIEIcon)
	ON_BN_CLICKED(IDC_ActiveXIcon, OnActiveXIcon)
	ON_BN_CLICKED(IDC_TaskIcon, OnTaskIcon)
	ON_BN_CLICKED(IDC_SubscriptIcon, OnSubscriptIcon)
	ON_BN_CLICKED(IDC_HistoryIcon, OnHistoryIcon)
	ON_BN_CLICKED(IDC_PathBrowse, OnPathBrowse)
	ON_BN_CLICKED(IDC_Fake, OnFake)
	ON_BN_CLICKED(IDC_Release, OnRelease)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainPage ���b�Z�[�W �n���h��

void CMainPage::OnSelchangeFolderCombo() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	int nIndex = m_cnFolder.GetCurSel();

	// ����t�H���_�̃A�C�R�����擾����
	HICON hIcon = GetIcon(nIndex); 

	// �����A�A�C�R�������݂��Ȃ��̂Ȃ�A[�U��]�𖳌��ɂ���
	if(hIcon == NULL)
	{
		m_cnFake.EnableWindow(FALSE);
	}else{
		m_cnFake.EnableWindow(TRUE);
	}

	// �A�C�R����\������
	SetIcon(hIcon , &m_cnIcon);

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  CMainPage�̏�����
//  ��  ���F  �Ȃ�
//  �߂�l�F  �����
//  ��  �l�F  �r�o!MFC!
/*----------------------------------------------------------------------------*/
BOOL CMainPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	AddType();
	AddIcon();

	CString cBuf;
	for(int i = 0 ; i < 20;i++)
	{
		cBuf = m_pIni->GetHistory(i);

		if(cBuf == _T(""))
		{
			break;
		}
		m_cPathCombo.InsertString(i,cBuf);
	}
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �w�肳�ꂽ����t�H���_�̃A�C�R���n���h�����擾����
//  ��  ���F  ����t�H���_�̃C���f�b�N�X
//  �߂�l�F  �A�C�R�����n���h��
//  ��  �l�F  �Ȃ�
/*----------------------------------------------------------------------------*/
HICON CMainPage::GetIcon(int nIndex)
{
	CString cId;
	CRegEdit cEdit;

	cId = m_pFolder ->GetID(nIndex);
	// ���W�X�g������ǂ݂Ƃ�
	CString cIcon;
	if(cEdit.Open(HKEY_CLASSES_ROOT,_T("CLSID\\")+cId+_T("\\DefaultIcon")) != ERROR_SUCCESS )
	{
		return NULL;
	}
	
	cIcon = cEdit.Read(_T(""));

	if(cEdit.Close() != ERROR_SUCCESS ){ return NULL;}

	// �A�C�R�����t�@�C������擾����
	// ���W�X�g���ɂ�"c:\win.exe, 5"�Ƃ����`�ŕۑ�����Ă���̂ŁA�C���f�b�N�X�ƃt�@�C�����𕪂���
	CString cFile , cIndex;
	int i;

	i = cIcon.Find(_T(","));
	cFile = cIcon.Left(i);
	cIndex = cIcon.Right(cIcon.GetLength() - i -1);

	// �t�@�C������ǂ݂Ƃ�
	HICON hIcon;
	::ExtractIconEx(cFile , atoi(cIndex) , &hIcon , NULL , 1);


	return hIcon;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �R���{�{�b�N�X�ɓ���t�H���_����ǉ�����
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �֋X��̕���
/*----------------------------------------------------------------------------*/
void CMainPage::AddType()
{
	LPCTSTR lpFolder;

	for(int i = 0 ; i < LAST ; i++)
	{
		switch(i)
		{
		case CONTROL:
			lpFolder = _T("�R���g���[���p�l��");
			break;
		
		case PRINTER:
			lpFolder = _T("�v�����^");
			break;
		
		case TRASH:
			lpFolder = _T("���ݔ�");
			break;

		case NETWORK:
			lpFolder = _T("�l�b�g���[�N�R���s���[�^");
			break;

		case DIAL_UP:
			lpFolder = _T("�_�C�����A�b�v�l�b�g���[�N");
			break;
		
		case MY_COMPUTER:
			lpFolder = _T("�}�C�R���s���[�^");
			break;

		case FAVORITE:
			lpFolder = _T("���C�ɓ���");
			break;
	
		case MY_DOCUMENT:
			lpFolder = _T("�}�C�h�L�������g");
			break;
		case CACHE:
			lpFolder = _T("�C���^�[�l�b�g�L���b�V��");
			break;
		
		case IE:
			lpFolder = _T("�C���^�[�l�b�g�G�N�X�v���[��");
			break;
	
		case ACTIVE_X:
			lpFolder = _T("ActiveX�L���b�V���t�H���_");
			break;
		case TASK:
			lpFolder = _T("�^�X�N");
			break;

		case SUBSCRIPT:
			lpFolder = _T("�w��");
			break;

		case HISTORY:
			lpFolder = _T("����");
			break;
		
		}
		m_cnFolder.InsertString(i,lpFolder);
	}

	// �K���Ȃ̂�I��
	m_cnFolder.SetCurSel(0);
	m_cnIcon.SetIcon(GetIcon(0));
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ����t�H���_�̃A�C�R����\������
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
void CMainPage::AddIcon()
{
	HICON hIcon;

	for(int i = 0 ; i < LAST ; i++)
	{

		hIcon = GetIcon(i);

		switch(i)
		{
		case CONTROL:
			SetIcon(hIcon , &m_cnControlIcon);
			break;
		case PRINTER:
			SetIcon(hIcon , &m_cnPrinterIcon);
			break;
		
		case TRASH:
			SetIcon(hIcon , &m_cnTrashIcon);
			break;

		case NETWORK:
			SetIcon(hIcon , &m_cnNetworkIcon);
			break;

		case DIAL_UP:
			SetIcon(hIcon , &m_cnDialIcon);
			break;
		
		case MY_COMPUTER:
			SetIcon(hIcon , &m_cnMyComputerIcon);
			break;

		case FAVORITE:
			SetIcon(hIcon , &m_cnFavoriteIcon);
			break;
	
		case MY_DOCUMENT:
			SetIcon(hIcon , &m_cnMyDocumentIcon);
			break;

		case CACHE:
			SetIcon(hIcon , &m_cnChasheIcon);
			break;
		
		case IE:
			SetIcon(hIcon , &m_cnIeIcon);
			break;
	
		case ACTIVE_X:
			SetIcon(hIcon , &m_cnActiveXIcon);
			break;

		case TASK:
			SetIcon(hIcon , &m_cnTaskIcon);
			break;

		case SUBSCRIPT:
			SetIcon(hIcon , &m_cnSubscriptIcon);
			break;

		case HISTORY:
			SetIcon(hIcon , &m_cnHistoryIcon);
			break;
		}
	}
}

void CMainPage::OnControlIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(CONTROL);
	OnSelchangeFolderCombo();
}

void CMainPage::OnPrinterIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(PRINTER);
	OnSelchangeFolderCombo();
}

void CMainPage::OnTrashIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(TRASH);
	OnSelchangeFolderCombo();
}

void CMainPage::OnNetworkIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(NETWORK);
	OnSelchangeFolderCombo();
	
}

void CMainPage::OnDialIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(DIAL_UP);
	OnSelchangeFolderCombo();
}

void CMainPage::OnMyConputerIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(MY_COMPUTER);
	OnSelchangeFolderCombo();
}

void CMainPage::OnFavoriteIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(FAVORITE);
	OnSelchangeFolderCombo();
}

void CMainPage::OnMyDocumentIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(MY_DOCUMENT);
	OnSelchangeFolderCombo();
}

void CMainPage::OnCacheIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(CACHE);
	OnSelchangeFolderCombo();	
}

void CMainPage::OnIEIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(IE);
	OnSelchangeFolderCombo();
}

void CMainPage::OnActiveXIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(ACTIVE_X);
	OnSelchangeFolderCombo();
}

void CMainPage::OnTaskIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(TASK);
	OnSelchangeFolderCombo();
	
}

void CMainPage::OnSubscriptIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(SUBSCRIPT);
	OnSelchangeFolderCombo();
}

void CMainPage::OnHistoryIcon() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_cnFolder.SetCurSel(HISTORY);
	OnSelchangeFolderCombo();
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �A�C�R����\������
//  ��  ���F  �A�C�R���̃n���h�� , �\������R���g���[���̃|�C���^
//  �߂�l�F  ���� -- 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CMainPage::SetIcon(HICON hIcon, CStatic *p_cStatic)
{
	// �A�C�R�����Ȃ��Ȃ�A����̃A�C�R����\������
	if(hIcon == NULL)
	{
		// �A�C�R���̃��[�h
		hIcon = AfxGetApp() ->LoadIcon(IDI_NOTFOUND);
	
		// �R���g���[���𖳌��ɂ���
		p_cStatic ->EnableWindow(FALSE);
	}

	// �A�C�R����\��
	p_cStatic ->SetIcon(hIcon);
	return 0;

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_���Q�Ƃ���
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �n���h���֐�
/*----------------------------------------------------------------------------*/
void CMainPage::OnPathBrowse() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CShellControl cShell;

	// [�t�H���_�̎Q�ƃ_�C�A���O�̕\��]
	CString cPath;
	cPath = cShell.RefFolder(this->GetSafeHwnd());

	if(cPath != "")
	{
		// �L�����Z������Ă��Ȃ��ꍇ
		m_cPath = cPath;
		UpdateData(FALSE);
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �f�X�g���N�^
//  ��  ���F  
//  �߂�l�F  
//  ��  �l�F  
/*----------------------------------------------------------------------------*/
CMainPage::~CMainPage()
{
	delete m_pFolder;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �U�����s��
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �n���h���֐�
/*----------------------------------------------------------------------------*/
void CMainPage::OnFake() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();
	CString cBuf;
	int nRes = m_pFolder ->Fake(m_cPath ,cBuf, m_cnFolder.GetCurSel() , m_nMode);

	// �G���[����
	switch(nRes)
	{
	case F_FILE:
		AfxMessageBox(_T("�t�@�C���͏����ł��܂���B"));
		break;
	case F_SUCUESS:
		AfxMessageBox(_T("�����B"));

		m_cPath = cBuf;
		if(m_cPathCombo.FindStringExact(-1,m_cPath) == CB_ERR)
		{
			m_cPathCombo.InsertString(-1,m_cPath);
		}

		// �I��������
		int nIndex = m_cPathCombo.FindStringExact(-1,m_cPath);
		m_cPathCombo.SetCurSel(nIndex);
		
		break;
	}

	UpdateData(FALSE);
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �������s��
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �n���h���֐�
/*----------------------------------------------------------------------------*/
void CMainPage::OnRelease() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();

	// ����
	CString cBuf;
	int nRes = m_pFolder ->Release(m_cPath , cBuf , m_nMode);

	switch(nRes)
	{
	case F_FILE:
		AfxMessageBox(_T("�t�@�C���͏����ł��܂���B"));
		break;
	case F_PASSERORR:
		//AfxMessageBox(_T("�p�X���[�h���Ⴂ�܂��B"))
		break;
	case F_SAMENAME:
		AfxMessageBox(_T("���̃t�H���_�́A�U������Ă��܂���B"));
		break;
	case F_CANCEL:
		break;
	case F_ERROR:
		AfxMessageBox(_T("���m�̃G���[�ł��B"));
		break;
	case F_SUCUESS:
		AfxMessageBox(_T("�����B"));

		m_cPath = cBuf;
		int i=m_cPathCombo.FindStringExact(-1,m_cPath); 
		if(i == CB_ERR)
		{
			m_cPathCombo.InsertString(-1,m_cPath);
		}		
		
		// �I��������
		int nIndex = m_cPathCombo.FindStringExact(-1,m_cPath);
		m_cPathCombo.SetCurSel(nIndex);
		// �t�H���_���J���ݒ�Ȃ�A�J��
		if(m_bFolderOpen == TRUE)
		{
			::ShellExecute(NULL , "open" , cBuf , NULL , NULL , SW_SHOWNORMAL);
		}

		break;
	}
//	UpdateData(FALSE);
}

void CMainPage::SetMode(int nMode)
{
	m_nMode = nMode;

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ������t�H���_���J�����ǂ����̐ݒ�
//  ��  ���F  �J�� == TRUE
//  �߂�l�F  0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CMainPage::SetFolderOpen(BOOL bStates)
{
	m_bFolderOpen = bStates;
	return 0;
}

void CMainPage::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������

	CString cBuf;
	for(int i=0;i < m_cPathCombo.GetCount();i++)
	{
		if(i > 20)
		{
			break;
		}

		m_cPathCombo.GetLBText(i,cBuf);
		
		m_pIni->SaveHistory(i,cBuf);
	}
}
