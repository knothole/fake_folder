// RegEdit.h: CRegEdit クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEDIT_H__F988C3E1_1331_4D75_BB20_E0C142E11D6A__INCLUDED_)
#define AFX_REGEDIT_H__F988C3E1_1331_4D75_BB20_E0C142E11D6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegEdit  
{
public:
	virtual int Write(LPCTSTR lpEntry,LPCTSTR lpValue);
	virtual CString Read(LPCTSTR lpEntry);
	virtual int Close();
	virtual int Open(HKEY hKey,LPCTSTR lpSubKey, int nFlag = 0);
	CRegEdit();
	virtual ~CRegEdit();

private:
	HKEY m_hKey;
};

#endif // !defined(AFX_REGEDIT_H__F988C3E1_1331_4D75_BB20_E0C142E11D6A__INCLUDED_)
