// FoxIni.cpp: CFoxIni クラスのインプリメンテーション
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
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFoxIni::CFoxIni()
{

}

CFoxIni::~CFoxIni()
{

}

/*----------------------------------------------------------------------------*/
//  概  要：  FakeFolder 0.2x互換
//  引  数：  On / Off == TRUE / FALSE
//  戻り値：  成功 == 0
//  備  考：  void
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
//  概  要：  パスワードを使用する
//  引  数：  On / Off == TRUE / FALSE
//  戻り値：  成功 == 0
//  備  考：  void
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
//  概  要：  FakeFolder 0.2x互換
//  引  数：  void
//  戻り値：  On / Off == TRUE / FALSE
//  備  考：  void
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
//  概  要：  パスワードを使用する
//  引  数：  void
//  戻り値：  On / Off == TRUE / FALSE
//  備  考：  void
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
//  概  要：  「解除後フォルダを開く」
//  引  数：  void
//  戻り値：  On / Off == TRUE / FALSE
//  備  考：  取得
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
//  概  要：  「解除後フォルダを開く」
//  引  数：  On / Off == TRUE / FALSE
//  戻り値：  成功 == 0
//  備  考：  void
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
//  概  要：  履歴を保存する関数
//  引  数：  nIndex = インデックス , lpPath = パス
//  戻り値：  0 = 成功
//  備  考：  
/*----------------------------------------------------------------------------*/
int CFoxIni::SaveHistory(int nIndex, LPCTSTR lpPath)
{
	// 数字を文字列に変換
	char chIndex[100];
	_itoa(nIndex,chIndex,16);	// 無意味に16進数

	return WriteIni(_T("history"),chIndex,lpPath);
}

CString CFoxIni::GetHistory(int nIndex)
{
	// 数字を文字列に変換
	char chIndex[100];
	_itoa(nIndex,chIndex,16);	// 無意味に16進数

	return ReadIni(_T("history"),chIndex);
}
