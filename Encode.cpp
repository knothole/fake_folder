// Encode.cpp: CEncode �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "Encode.h"

#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUFFER 32767
#define ARCHIVE_FILE _T("_pass.zip")
//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CEncode::CEncode()
{
	// �C�e���[�^�̏�����
	m_itFile = m_liFile.begin();
}

CEncode::~CEncode()
{
	// �eDLL�̉��
	::FreeLibrary(m_hZipLib);
	::FreeLibrary(m_hUnzipLib);
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_�̃p�X��ݒ肷��
//  ��  ���F  �t�H���_�̃p�X
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::SetPath(LPCTSTR lpPath)
{
	m_inMax = 0;
	// �p�X��"C:\windows\"�Ƃ����`�ɂ���B(�Ōオ'\')
	CString cPath = lpPath;
	cPath.TrimRight("\\");
	cPath += "\\";
	
	m_cPath = cPath;
	// ���́A�t�H���_���̃t�@�C�����擾����
	CFileFind cFind;

	if(cFind.FindFile(cPath + "*") != 0)
	{
		int i = 1;

		while(i)
		{
			i = cFind.FindNextFile();

			if(cFind.IsDots()){ continue; }

			// �t�@�C���������X�g�ɒǉ�����
			m_liFile.push_front(cFind.GetFileName());
			m_inMax++;
		}

		return 0;
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_�̃p�X���擾����
//  ��  ���F  void
//  �߂�l�F  �t�H���_�̃p�X
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
CString CEncode::GetPath()
{
	return m_cPath;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�@�C�����Í�������
//  ��  ���F  void
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::Encode()
{
	// Zio32j.dll�ň��k���邽�߂ɁA���X�|���X�t�@�C���ɑS�t�@�C������������
	CString cResponse;
	if(WriteResponse(cResponse) != 0)
	{
		AfxMessageBox(_T("���X�|���X�t�@�C���ւ̏������݂Ɏ��s���܂����B"));
	}
	
	// �R�}���h���C�������
	CString cCmdLine , cOption , cFilePath , cDirectory;
	cOption = "-r -e";
	cFilePath = m_cPath + ARCHIVE_FILE;
	
	cCmdLine = cOption + _T(" \"") + cFilePath + _T("\" \"") + m_cPath + _T("\" \"@") 
				+ cResponse+ _T("\"") ;

	// ���k���s��
	if(Zip(cCmdLine) != 0)
	{
		::AfxMessageBox(_T("ZIP���k�Ɏ��s���܂����B"));
		return -1;
	}else{

		// �t�@�C�����폜����
		return FileDelete();
	}


}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�@�C�������k����
//  ��  ���F  �R�}���h
//  �߂�l�F  ����I�� == 0
//  ��  �l�F  Zip32j.dll�����[�h���邾���B
/*----------------------------------------------------------------------------*/
int CEncode::Zip(LPCTSTR lpCmdLine)
{
	if(m_hZipLib != NULL)
	{
		typedef  int(WINAPI ZIP)(const HWND , LPCTSTR , LPSTR , const DWORD);

		// �֐������[�h����
		ZIP *pZip = (ZIP*)::GetProcAddress(m_hZipLib , "Zip");

		if(pZip == NULL){ return -1;}

		// �֐����Ă�
		char chBuffer[MAX_BUFFER + 1];
		return pZip(NULL , lpCmdLine , chBuffer , MAX_BUFFER);
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ���낢��ȏ�������
//  ��  ���F  void
//  �߂�l�F  void
//  ��  �l�F  �K���ĂԂ���
/*----------------------------------------------------------------------------*/
void CEncode::Load()
{
	// �eDLL�����[�h����
	m_hZipLib = ::LoadLibrary("Zip32j.dll");
	m_hUnzipLib = ::LoadLibrary("Unzip32.dll");
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ���X�|���X�t�@�C���Ƀt�@�C���̃��X�g����������
//  ��  ���F  void
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::WriteResponse(CString &r_cResponse)
{
	// �ꎞ�t�@�C���̎擾
	CString cTempPath;
	CFileApi cFileApi;
	cTempPath = cFileApi.GetTempPath();

	// �ꎞ�t�@�C���ɏ�������
	CStdioFile cFile;

	if(cFile.Open(cTempPath , CFile::modeWrite) != 0)
	{
		for(m_itFile = m_liFile.begin() ; m_itFile != m_liFile.end() ; m_itFile++)
		{
			cFile.WriteString(*m_itFile + "\n");
		}

		m_liFile.erase(m_liFile.begin() , m_liFile.end());

		cFile.Close();
		r_cResponse = cTempPath;
		return 0;
	}else{
		return 1;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ���k�������ƁA�t�@�C�����폜����
//  ��  ���F  void
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::FileDelete()
{
	CFileApi cFileApi;
	int nRes = 0;

	for(m_itFile = m_liFile.begin() ; m_itFile != m_liFile.end() ; m_itFile++)
	{
		nRes = cFileApi.Delete(m_cPath + *m_itFile);
	}

	return nRes;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  Unzip32.dll����Unzip()�Ăяo��
//  ��  ���F  �R�}���h���C��
//  �߂�l�F  0�@--- ����
//  ��  �l�F  DLL�̓��I���[�h
/*----------------------------------------------------------------------------*/
int CEncode::Unzip(LPCTSTR lpCmdLine)
{
	if(m_hUnzipLib != NULL)
	{
		typedef  int(WINAPI UNZIP)(const HWND , LPCTSTR , LPSTR , const DWORD);

		UNZIP* pUnzip = (UNZIP*)::GetProcAddress(m_hUnzipLib , _T("UnZip"));

		if(pUnzip == NULL){ AfxMessageBox(_T("API(Unzip)�̃��[�h�Ɏ��s���܂����B"));}

		// �֐����Ă�
		char chBuffer[MAX_BUFFER + 1];
		return pUnzip(NULL , lpCmdLine , chBuffer , MAX_BUFFER);
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_�𕜍�������
//  ��  ���F  void
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::Decode()
{
	CString cCmdLine , cOption , cDirectory , cArchive;

	cOption = _T("-x");
	cArchive = _T("\"") + m_cPath + ARCHIVE_FILE +_T("\"");
	cDirectory = _T("\"") + m_cPath + _T("\"");

	cCmdLine = cOption + _T(" ") + cArchive + _T(" ") + cDirectory;

	int nRes = Unzip(cCmdLine);

	// �t�@�C���̍폜
	if(::DeleteFile(m_cPath + ARCHIVE_FILE) == 0)
	{
		::AfxMessageBox(ARCHIVE_FILE _T("�̍폜�Ɏ��s���܂����B"));
		DWORD dw = ::GetLastError();
	}
	return nRes;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �Í�������Ă��邩�`�F�b�N����
//  ��  ���F  �p�X
//  �߂�l�F  true / false
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CEncode::IsDecode(LPCTSTR lpPath)
{
	CString cPath = lpPath;
	cPath += "\\"ARCHIVE_FILE;

	if(::GetFileAttributes(cPath) != 0xFFFFFFFF)
	{
		return TRUE;
	}else{
		return FALSE;
	}
}
