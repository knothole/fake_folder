// FileApi.cpp: CFileApi �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CFileApi::CFileApi()
{

}

CFileApi::~CFileApi()
{

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ��Ɨp�̃t�@�C�������擾����
//  ��  ���F  void
//  �߂�l�F  �t�@�C���̃t���p�X
//  ��  �l�F  GetTempPath() + GetTempFileName()
/*----------------------------------------------------------------------------*/
CString CFileApi::GetTempPath()
{
	TCHAR tchPath[MAX_PATH + 1];
	if(::GetTempPath(MAX_PATH , tchPath) != 0)
	{
		// �t�@�C�����̎擾
		TCHAR tchFileName[MAX_PATH +1 ];
		GetTempFileName(tchPath , "AIR",0,tchFileName);
		return tchFileName;
	}else{
		return "";
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_���ǂ������`�F�b�N����
//  ��  ���F  �t���p�X
//  �߂�l�F  �t�H���_ / �t�@�C�� == TRUE / FALSE
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
BOOL CFileApi::CheckDirectory(LPCTSTR lpPath)
{
	DWORD dwType = ::GetFileAttributes(lpPath);

	if(dwType & FILE_ATTRIBUTE_DIRECTORY && dwType != 0xFFFFFFFF)
	{
		// ���݂��āA�t�H���_�̏ꍇ
		return TRUE;
	}else{
		return FALSE;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_���ċN�I�ɍ폜����
//  ��  ���F  �t�H���_�̃p�X
//  �߂�l�F  ���� == TRUE
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
BOOL CFileApi::DeleteDirectory(LPCTSTR lpPathName)
{
	CFileFind fnd;
    CString strPathName = lpPathName;
    strPathName.TrimRight('\\');
    strPathName += _T("\\*.*");
    if(fnd.FindFile(strPathName, 0))
    {
        int i = 1;
        while(i)
        {
            i = fnd.FindNextFile();

            // �t�@�C������"."��".."�̏ꍇ�͎�������
            if(fnd.IsDots())
                continue;

            // �폜����t�@�C�����擾
            // GetFilePath()�ɂ̓o�O�����萳�m�Ɏ擾�ł��Ȃ��ꍇ������̂Ŏg��Ȃ�
            CString strDeleteFile = lpPathName;
            strDeleteFile.TrimRight('\\');
            strDeleteFile += _T("\\") + fnd.GetFileName();

            // �t�H���_�������ꍇ�A�ċA�Ăяo���ł��̃t�H���_���폜
            if(fnd.IsDirectory())
                DeleteDirectory(strDeleteFile);

            // �t�@�C���̍폜
            else
                ::DeleteFile(strDeleteFile);
        }
        fnd.Close();

        // �t�H���_�̍폜
		CString cPath;
		cPath = lpPathName;
		cPath.TrimRight('\\');
        return ::RemoveDirectory(cPath);
    }

	return FALSE;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_�ł��t�@�C���ł��폜����
//  ��  ���F  �t���p�X
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CFileApi::Delete(LPCTSTR lpPath)
{
	if(CheckDirectory(lpPath))
	{
		return DeleteDirectory(lpPath);
	}else{
		return ::DeleteFile(lpPath);
	}
}
