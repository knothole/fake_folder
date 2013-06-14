// FoxIni.h: CFoxIni クラスのインターフェイス
//	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOXINI_H__61C5B895_07FC_4457_A27D_935FF040943F__INCLUDED_)
#define AFX_FOXINI_H__61C5B895_07FC_4457_A27D_935FF040943F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ini.h"

/*----------------------------------------------------------------------------*/
//  概要        ：  FOXに特化したCIni
//  関連フォーム：  void
//  備考        ：  直接、CIniのメンバを操作しないこと
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
