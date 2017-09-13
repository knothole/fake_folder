// Encode.h: CEncode �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCODE_H__32BF3EF2_DA08_4B9C_966A_C60000838662__INCLUDED_)
#define AFX_ENCODE_H__32BF3EF2_DA08_4B9C_966A_C60000838662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "list"
using namespace std;
/*----------------------------------------------------------------------------*/
//  �T�v        �F  �t�@�C�����Í����E���������s��
//  �֘A�t�H�[���F  void
//  ���l        �F  ���O���s�K�؂����Ǌ��ق��Ă��������B (^^ ;
/*----------------------------------------------------------------------------*/
class CEncode  
{
public:
	virtual int IsDecode(LPCTSTR lpPath);
	virtual int Decode();
	virtual void Load(void);
	virtual int Encode(void);
	virtual CString GetPath(void);
	virtual int SetPath(LPCTSTR lpPath);
	CEncode();
	virtual ~CEncode();

private:
	int m_inMax;
	HINSTANCE m_hZipLib;
	HINSTANCE m_hUnzipLib;
	CString m_cPath;
	list<CString> m_liFile;
	list<CString>::iterator m_itFile;
protected:
	virtual int Unzip(LPCTSTR lpCmdLine);
	virtual int FileDelete();
	virtual int WriteResponse(CString &r_cResponse);
	virtual int Zip(LPCTSTR lpCmdLine);
};

#endif // !defined(AFX_ENCODE_H__32BF3EF2_DA08_4B9C_966A_C60000838662__INCLUDED_)
