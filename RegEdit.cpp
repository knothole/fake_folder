// RegEdit.cpp: CRegEdit �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "RegEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CRegEdit::CRegEdit()
{

}

CRegEdit::~CRegEdit()
{

}

// ���W�X�g�����J��
int CRegEdit::Open(HKEY hKey, LPCTSTR lpSubKey,int nFlag)
{
	if(nFlag == 0)
	{
		return ::RegOpenKeyEx(hKey,lpSubKey,0,KEY_ALL_ACCESS,&m_hKey);
	}else{
		DWORD dw_Res;
		return ::RegCreateKeyEx(hKey,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
			NULL,&m_hKey,&dw_Res);
	}
}

// ���W�X�g�������
int CRegEdit::Close()
{
	return ::RegCloseKey(m_hKey);
}

// ���W�X�g����ǂ݂Ƃ�B(�������p)
CString CRegEdit::Read(LPCTSTR lpEntry)
{
	DWORD dw_Type,dw_Size;
	BYTE  *p_Data;

	::RegQueryValueEx(m_hKey,lpEntry,0,
		&dw_Type,NULL,&dw_Size);
	
	p_Data = new BYTE[dw_Size];
	::RegQueryValueEx(m_hKey,lpEntry,0,
		&dw_Type,p_Data,&dw_Size);

	CString cBuffer;
	cBuffer = p_Data;
	delete p_Data;
	return cBuffer;
}

int CRegEdit::Write(LPCTSTR lpEntry, LPCTSTR lpValue)
{
	return ::RegSetValueEx(m_hKey,lpEntry,0,REG_SZ,
		(CONST BYTE*)lpValue,strlen(lpValue));
}
