// FoxDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "Fox.h"
#include "FoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFoxDlg �_�C�A���O

CFoxDlg::CFoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFoxDlg)
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFoxDlg)
	DDX_Control(pDX, IDC_MainTab, m_cnTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFoxDlg, CDialog)
	//{{AFX_MSG_MAP(CFoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MainTab, OnSelchangeMainTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_MainTab, OnSelchangingMainTab)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ApplyButton, OnApplyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFoxDlg ���b�Z�[�W �n���h��

BOOL CFoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	// ������
	LoadSetting();

	TC_ITEM sItem;	// �^�u�A�C�e���\����

	// �^�u�R���g���[���ɍ��ڂ̒ǉ�
	for(int i = 0 ; i < 3 ; i++)
	{
		sItem.mask = TCIF_TEXT;

		switch(i)
		{
		case 0:
			sItem.pszText = "Main";
			break;
		case 1:
			sItem.pszText = "�ݒ�";
			break;
		case 2:
			sItem.pszText = "About";
			break;
		}
		m_cnTab.InsertItem( i ,&sItem);
	}

	m_cMain.m_pIni = &m_cIni;
	// �e�^�u�y�[�W��`��
	m_cMain.Create(IDD_MainDlg , &m_cnTab);
	m_cSetting.Create(IDD_SettingDlg   , &m_cnTab);
	m_cAbout.Create(IDD_AboutDlg , &m_cnTab);
	
	
	// ������
	m_cAbout.Load();

	// �����\����Ԃ̐ݒ�
	m_cMain.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_SHOWWINDOW);
	m_cSetting.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_HIDEWINDOW);
	m_cAbout.SetWindowPos(&wndTop , 10 , 30 , 0 , 0 ,SWP_NOSIZE | SWP_HIDEWINDOW);

	// �e�y�[�W�̏�����
	m_cSetting.Load();

	// D&D�̎󂯎���������
	DragAcceptFiles(TRUE);
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CFoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CFoxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CFoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFoxDlg::OnSelchangeMainTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	int inIndex = m_cnTab.GetCurSel();	// �؂�ւ���̃^�u�̃C���f�b�N�X

	// �I�����ꂽ�^�u�̂ݕ\������
	switch(inIndex)
	{
	case 0:
		m_cMain.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_cSetting.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_cAbout.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CFoxDlg::OnSelchangingMainTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
		int inIndex = m_cnTab.GetCurSel();	// �؂�ւ���̃^�u�̃C���f�b�N�X

	// �I�����ꂽ�^�u�̂ݕ\������
	switch(inIndex)
	{
	case 0:
		m_cMain.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_cSetting.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_cAbout.ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}

void CFoxDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	char chBuf[MAX_PATH + 1];

	// �t�H���_�́A������󂯎��Ȃ�
	::DragQueryFile(  hDropInfo, 0, chBuf, 1024);

	m_cMain.m_cPathCombo.SetWindowText(chBuf);
	CDialog::OnDropFiles(hDropInfo);
}

void CFoxDlg::OnApplyButton() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	SaveSetting();
	LoadSetting();
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �ݒ��INI�t�@�C���ɕۑ�����
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
void CFoxDlg::SaveSetting()
{
	m_cSetting.UpdateData();
	m_cIni.SetCompatible(m_cSetting.m_bCompatible);
	m_cIni.SetPassword	(m_cSetting.m_bPassword);
	m_cIni.SetOpenFolder(m_cSetting.m_bOpenFolder);
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �ݒ��INI�t�@�C������ǂ݂Ƃ�
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
void CFoxDlg::LoadSetting()
{
	// FakeFolder 0.2x�݊�
	if(m_cIni.GetCompatible() == TRUE)
	{
		m_cSetting.m_bCompatible = TRUE;
		m_cMain.SetMode(F_COMPATIBLE);
	}else{
		m_cSetting.m_bCompatible = FALSE;
		m_cMain.SetMode(F_NORMAL);
	}
	
	// �p�X���[�h���g�p����
	if(m_cIni.GetPassword() == TRUE)
	{
		m_cSetting.m_bPassword = TRUE;
		m_cMain.SetMode(F_PASSWORD);
	}else{
		m_cSetting.m_bPassword = FALSE;
		m_cMain.SetMode(F_NORMAL);
	}

	// ������t�H���_���J��
	if(m_cIni.GetOpenFolder() == TRUE)
	{
		m_cSetting.m_bOpenFolder = TRUE;
		m_cMain.SetFolderOpen(TRUE);
	}else{
		m_cSetting.m_bOpenFolder = FALSE;
		m_cMain.SetFolderOpen(FALSE);
	}

}

void CFoxDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	SaveSetting();
	CDialog::OnOK();
}
