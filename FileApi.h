// FileApi.h: CFileApi クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEAPI_H__971B44A8_8D4C_4BED_9A22_CBEE082C633A__INCLUDED_)
#define AFX_FILEAPI_H__971B44A8_8D4C_4BED_9A22_CBEE082C633A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*----------------------------------------------------------------------------*/
//  概要        ：  ファイル関係のAPIを集めたクラス
//  関連フォーム：  void
//  備考        ：  関数クラス
/*----------------------------------------------------------------------------*/
class CFileApi  
{
public:
	virtual int Delete(LPCTSTR lpPath);
	virtual BOOL DeleteDirectory(LPCTSTR);
	virtual BOOL CheckDirectory(LPCTSTR lpPath);
	virtual CString GetTempPath();
	CFileApi();
	virtual ~CFileApi();

};

#endif // !defined(AFX_FILEAPI_H__971B44A8_8D4C_4BED_9A22_CBEE082C633A__INCLUDED_)
