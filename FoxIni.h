// FoxIni.h: CFoxIni �N���X�̃C���^�[�t�F�C�X
//	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOXINI_H__61C5B895_07FC_4457_A27D_935FF040943F__INCLUDED_)
#define AFX_FOXINI_H__61C5B895_07FC_4457_A27D_935FF040943F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ini.h"

/*----------------------------------------------------------------------------*/
//  �T�v        �F  FOX�ɓ�������CIni
//  �֘A�t�H�[���F  void
//  ���l        �F  ���ځACIni�̃����o�𑀍삵�Ȃ�����
/*----------------------------------------------------------------------------*/
class CFoxIni : public CIni  
{
public:
	virtual CString GetHistory(int nIndex);
	virtual int SaveHistory(int nIndex,LPCTSTR lpPath);
	virtual int SetOpenFolder(BOOL bStates);
	virtual BOOL GetOpenFolder(void);
	virtual BOOL GetPassword();
	virtual BOOL GetCompatible();
	virtual int SetPassword(BOOL bStates);
	virtual int SetCompatible(BOOL bStates);
	CFoxIni();
	virtual ~CFoxIni();

};

#endif // !defined(AFX_FOXINI_H__61C5B895_07FC_4457_A27D_935FF040943F__INCLUDED_)
