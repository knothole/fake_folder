// Folder.h: CFolder クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDER_H__4215122C_5BCD_47EC_A898_10A2F5862266__INCLUDED_)
#define AFX_FOLDER_H__4215122C_5BCD_47EC_A898_10A2F5862266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "map"
#include "Encode.h"	// ClassView によって追加されました。
#include "Fake.h"
using namespace std;

class CFolder  
{
public:
	int Fake(LPCTSTR lpPath,CString &r_cNewPath , int nType , int nMode);
	virtual int Release(LPCTSTR lpPath ,CString &r_cBuf , int nMode);
	virtual LPCTSTR GetID(int nIndex);
	virtual int Load();
	CFolder();
	virtual ~CFolder();

private:
	CEncode *m_pEncode;
	map<int,CString> m_mSpecialFolder;
protected:
	virtual CString Release(LPCTSTR lpPath);
	virtual CString Fake(LPCTSTR lpPath , int nType);
};

#endif // !defined(AFX_FOLDER_H__4215122C_5BCD_47EC_A898_10A2F5862266__INCLUDED_)
