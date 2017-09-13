// FoxIni.cpp: CFoxIni �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "FoxIni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CFoxIni::CFoxIni()
{

}

CFoxIni::~CFoxIni()
{

}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  FakeFolder 0.2x�݊�
//  ��  ���F  On / Off == TRUE / FALSE
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CFoxIni::SetCompatible(BOOL bStates)
{
	if(bStates == TRUE)
	{
		return WriteIni("Setting" , "Compatible" , "Enable");
	}else{
		return WriteIni("Setting" , "Compatible" , "Disable");
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �p�X���[�h���g�p����
//  ��  ���F  On / Off == TRUE / FALSE
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CFoxIni::SetPassword(BOOL bStates)
{
	if(bStates == TRUE)
	{
		return WriteIni("Setting" , "Password" , "Enable");
	}else{
		return WriteIni("Setting" , "Password" , "Disable");
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  FakeFolder 0.2x�݊�
//  ��  ���F  void
//  �߂�l�F  On / Off == TRUE / FALSE
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
BOOL CFoxIni::GetCompatible()
{
	CString cBuf = ReadIni("Setting" , "Compatible");

	if(cBuf == "Enable")
	{
		return TRUE;
	}else{
		return FALSE;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �p�X���[�h���g�p����
//  ��  ���F  void
//  �߂�l�F  On / Off == TRUE / FALSE
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
BOOL CFoxIni::GetPassword()
{
	CString cBuf = ReadIni("Setting" , "Password");

	if(cBuf == "Enable")
	{
		return TRUE;
	}else{
		return FALSE;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �u������t�H���_���J���v
//  ��  ���F  void
//  �߂�l�F  On / Off == TRUE / FALSE
//  ��  �l�F  �擾
/*----------------------------------------------------------------------------*/
BOOL CFoxIni::GetOpenFolder()
{
	CString cBuf = ReadIni(_T("Setting"),_T("OpenFolder"));

	if(cBuf == _T("Enable"))
	{
		return TRUE;
	}else{
		return FALSE;
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  �u������t�H���_���J���v
//  ��  ���F  On / Off == TRUE / FALSE
//  �߂�l�F  ���� == 0
//  ��  �l�F  void
/*----------------------------------------------------------------------------*/
int CFoxIni::SetOpenFolder(BOOL bStates)
{
	if(bStates == TRUE)
	{
		return WriteIni(_T("Setting") , _T("OpenFolder") , _T("Enable"));
	}else{
		return WriteIni(_T("Setting") , _T("OpenFolder") , _T("Disable"));
	}
}

/*----------------------------------------------------------------------------*/
//  �T  �v�F  ������ۑ�����֐�
//  ��  ���F  nIndex = �C���f�b�N�X , lpPath = �p�X
//  �߂�l�F  0 = ����
//  ��  �l�F  
/*----------------------------------------------------------------------------*/
int CFoxIni::SaveHistory(int nIndex, LPCTSTR lpPath)
{
	// �����𕶎���ɕϊ�
	char chIndex[100];
	_itoa(nIndex,chIndex,16);	// ���Ӗ���16�i��

	return WriteIni(_T("history"),chIndex,lpPath);
}

CString CFoxIni::GetHistory(int nIndex)
{
	// �����𕶎���ɕϊ�
	char chIndex[100];
	_itoa(nIndex,chIndex,16);	// ���Ӗ���16�i��

	return ReadIni(_T("history"),chIndex);
}
