// Folder.cpp: CFolder �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "Folder.h"

#include "SpecialFolder.h"
#include "FileString.h"
#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CFolder::CFolder()
{
	m_pEncode = new CEncode;
	m_pEncode ->Load();
}

CFolder::~CFolder()
{
	delete m_pEncode;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �N���X�����̏�����
//  ��  ���F  void
//  �߂�l�F  ���� -- 0
//  ��  �l�F  ���̂Ƃ���A�萔��map�̂�
/*----------------------------------------------------------------------------*/
int CFolder::Load()
{
	LPCTSTR lpID;

	for(int i = 0 ; i < LAST ; i++)
	{

		switch(i)
		{
		case CONTROL:
			lpID = ID_CONTROL;
			break;
		case PRINTER:
			lpID =  ID_PRINTER;
			break;
		case TRASH:
			lpID =  ID_TRASH;
			break;
		case NETWORK:
			lpID =  ID_NETWORK;
			break;
		case DIAL_UP:
			lpID =  ID_DIAL_UP;
			break;
		case MY_COMPUTER:
			lpID =  ID_MY_COMPUTER;
			break;
		case FAVORITE:
			lpID =  ID_FAVORITE;
			break;
		case MY_DOCUMENT:
			lpID =  ID_MY_DOCUMENT;
			break;
		case CACHE:
			lpID =  ID_CACHE;
			break;
		case IE:
			lpID =  ID_IE;
			break;
		case ACTIVE_X:
			lpID =  ID_ACTIVE_X;
			break;
		case TASK:
			lpID = ID_TASK;
			break;
		case SUBSCRIPT:
			lpID = ID_SUBSCRIPT;
			break;
		case HISTORY:
			lpID = ID_HISTORY;
			break;
		
		default:
			return -1;
		}
		m_mSpecialFolder[i] = lpID;
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �N���XID���擾����
//  ��  ���F  �萔
//  �߂�l�F  �N���XID
//  ��  �l�F  �Ȃ�ׂ��A���̊֐����g��
/*----------------------------------------------------------------------------*/
LPCTSTR CFolder::GetID(int nIndex)
{
	return m_mSpecialFolder[nIndex];
}


/*----------------------------------------------------------------------------*/
//  �T  �v�F  �t�H���_���U������
//  ��  ���F  �t�H���_�̃p�X , ���
//  �߂�l�F  �V�����t�H���_�̖��O
//  ��  �l�F  ���̊֐��͓����݂̂ŌĂ΂��
/*----------------------------------------------------------------------------*/
CString CFolder::Fake(LPCTSTR lpPath, int nType)
{
	CString cNewPath;

	cNewPath = lpPath;
	cNewPath += "." + m_mSpecialFolder[nType];

	if(rename(lpPath , cNewPath) != 0)
	{
		// ���s
		::AfxMessageBox(_T("���l�[���Ɏ��s���܂����B"));
	}
	return (LPCTSTR)cNewPath;
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �U������������
//  ��  ���F  �t�H���_�̃p�X , ���[�h
//  �߂�l�F  ���� --- 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CFolder::Release(LPCTSTR lpPath,CString &r_cBuf, int nMode)
{
	CFileApi cFileApi;
	if(cFileApi.CheckDirectory(lpPath) == FALSE){ return F_FILE;}

	if(nMode == F_NORMAL || nMode == F_PASSWORD)
	{
		// �ʏ���@�ł̋U������
		if(m_pEncode ->IsDecode(lpPath) == TRUE)
		{
			// �Í�������Ă���
			m_pEncode ->SetPath(lpPath);
			
			if(m_pEncode ->Decode() == 0)
			{
				r_cBuf = Release(lpPath);
			}else{
				return F_CANCEL;
			}
		}else{
			// �Í�������Ă��Ȃ�
			r_cBuf = Release(lpPath);
		}
	}
	// FakeFolder 0.2x�݊����[�h
	else if(nMode == F_COMPATIBLE)
	{
		r_cBuf = Release(lpPath);
	}

	// �U�����ꂽ���`�F�b�N
	if(strcmp(lpPath , r_cBuf) == 0)
	{
		return F_SAMENAME;
	}
	else if(r_cBuf == "")
	{
		return F_ERROR;
	}else{
		return F_SUCUESS;
	}

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �U������������
//  ��  ���F  �t�H���_�̃p�X
//  �߂�l�F  �V�����t�H���_�̃p�X
//  ��  �l�F  �����݂̂��s��
/*----------------------------------------------------------------------------*/
CString CFolder::Release(LPCTSTR lpPath)
{
	// �g���q����菜�����t�@�C�������擾����
	CString cNewPath;
	CFileString cFStr;
	
	cNewPath = cFStr.CutExt(lpPath);

	if(rename(lpPath , cNewPath) == 0)
	{
		return cNewPath;
	}else{
		AfxMessageBox("���l�[���Ɏ��s���܂����B");
		return "";
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �Í������s����U��
//  ��  ���F  �t�H���_�̃p�X , �U��������
//  �߂�l�F  ���� == 0
//  ��  �l�F  �֐��������̂��߂�ǂ������̂ŁA���d��`�B(�r�o!C++
/*----------------------------------------------------------------------------*/
int CFolder::Fake(LPCTSTR lpPath, CString &r_cNewPath, int nType, int nMode)
{
	// �t�H���_���ǂ����̃`�F�b�N
	CFileApi cFileApi;
	BOOL bRes = cFileApi.CheckDirectory(lpPath);

	// �t�@�C���Ȃ�A�G���[
	if(bRes == FALSE){ return F_FILE;}

	/* �U�����s�� */
	CString cBuf;

	/*if(nMode = F_NORMAL || nMode == F_COMPATIBLE)
	{
		cBuf = Fake(lpPath , nType);
		r_cNewPath = cBuf;
	}*/
	 
	if(nMode == F_PASSWORD)
	{
		// �Í���
		m_pEncode ->SetPath(lpPath);
		
		if(m_pEncode ->Encode() != 0)
		{
			return F_CANCEL;
		}
	}

	// ���ʂɋU������
	cBuf = Fake(lpPath , nType);
	r_cNewPath = cBuf;
	

	return F_SUCUESS;
}
