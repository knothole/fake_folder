// FileApi.h: CFileApi �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEAPI_H__971B44A8_8D4C_4BED_9A22_CBEE082C633A__INCLUDED_)
#define AFX_FILEAPI_H__971B44A8_8D4C_4BED_9A22_CBEE082C633A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*----------------------------------------------------------------------------*/
//  �T�v        �F  �t�@�C���֌W��API���W�߂��N���X
//  �֘A�t�H�[���F  void
//  ���l        �F  �֐��N���X
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
