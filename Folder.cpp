// Folder.cpp: CFolder クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "Folder.h"

#include "SpecialFolder.h"
#include "FileString.h"
#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFolder::CFolder()
{
	m_pEncode = new CEncode;
	m_pEncode ->Load();
}

CFolder::~CFolder()
{
	delete m_pEncode;
}

/*----------------------------------------------------------------------------*/
//  概  要：  クラス内部の初期化
//  引  数：  void
//  戻り値：  成功 -- 0
//  備  考：  今のところ、定数→mapのみ
/*----------------------------------------------------------------------------*/
int CFolder::Load()
{
	LPCTSTR lpID;

	for(int i = 0 ; i < LAST ; i++)
	{

		switch(i)
		{
		case CONTROL:
			lpID = ID_CONTROL;
			break;
		case PRINTER:
			lpID =  ID_PRINTER;
			break;
		case TRASH:
			lpID =  ID_TRASH;
			break;
		case NETWORK:
			lpID =  ID_NETWORK;
			break;
		case DIAL_UP:
			lpID =  ID_DIAL_UP;
			break;
		case MY_COMPUTER:
			lpID =  ID_MY_COMPUTER;
			break;
		case FAVORITE:
			lpID =  ID_FAVORITE;
			break;
		case MY_DOCUMENT:
			lpID =  ID_MY_DOCUMENT;
			break;
		case CACHE:
			lpID =  ID_CACHE;
			break;
		case IE:
			lpID =  ID_IE;
			break;
		case ACTIVE_X:
			lpID =  ID_ACTIVE_X;
			break;
		case TASK:
			lpID = ID_TASK;
			break;
		case SUBSCRIPT:
			lpID = ID_SUBSCRIPT;
			break;
		case HISTORY:
			lpID = ID_HISTORY;
			break;
		
		default:
			return -1;
		}
		m_mSpecialFolder[i] = lpID;
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
//  概  要：  クラスIDを取得する
//  引  数：  定数
//  戻り値：  クラスID
//  備  考：  なるべく、この関数を使う
/*----------------------------------------------------------------------------*/
LPCTSTR CFolder::GetID(int nIndex)
{
	return m_mSpecialFolder[nIndex];
}


/*----------------------------------------------------------------------------*/
//  概  要：  フォルダを偽装する
//  引  数：  フォルダのパス , 種類
//  戻り値：  新しいフォルダの名前
//  備  考：  この関数は内部のみで呼ばれる
/*----------------------------------------------------------------------------*/
CString CFolder::Fake(LPCTSTR lpPath, int nType)
{
	CString cNewPath;

	cNewPath = lpPath;
	cNewPath += "." + m_mSpecialFolder[nType];

	if(rename(lpPath , cNewPath) != 0)
	{
		// 失敗
		::AfxMessageBox(_T("リネームに失敗しました。"));
	}
	return (LPCTSTR)cNewPath;
}

/*----------------------------------------------------------------------------*/
//  概  要：  偽装を解除する
//  引  数：  フォルダのパス , モード
//  戻り値：  成功 --- 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CFolder::Release(LPCTSTR lpPath,CString &r_cBuf, int nMode)
{
	CFileApi cFileApi;
	if(cFileApi.CheckDirectory(lpPath) == FALSE){ return F_FILE;}

	if(nMode == F_NORMAL || nMode == F_PASSWORD)
	{
		// 通常方法での偽装解除
		if(m_pEncode ->IsDecode(lpPath) == TRUE)
		{
			// 暗号化されている
			m_pEncode ->SetPath(lpPath);
			
			if(m_pEncode ->Decode() == 0)
			{
				r_cBuf = Release(lpPath);
			}else{
				return F_CANCEL;
			}
		}else{
			// 暗号化されていない
			r_cBuf = Release(lpPath);
		}
	}
	// FakeFolder 0.2x互換モード
	else if(nMode == F_COMPATIBLE)
	{
		r_cBuf = Release(lpPath);
	}

	// 偽装されたかチェック
	if(strcmp(lpPath , r_cBuf) == 0)
	{
		return F_SAMENAME;
	}
	else if(r_cBuf == "")
	{
		return F_ERROR;
	}else{
		return F_SUCUESS;
	}

}

/*----------------------------------------------------------------------------*/
//  概  要：  偽装を解除する
//  引  数：  フォルダのパス
//  戻り値：  新しいフォルダのパス
//  備  考：  解除のみを行う
/*----------------------------------------------------------------------------*/
CString CFolder::Release(LPCTSTR lpPath)
{
	// 拡張子を取り除いたファイル名を取得する
	CString cNewPath;
	CFileString cFStr;
	
	cNewPath = cFStr.CutExt(lpPath);

	if(rename(lpPath , cNewPath) == 0)
	{
		return cNewPath;
	}else{
		AfxMessageBox("リネームに失敗しました。");
		return "";
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  暗号化も行える偽装
//  引  数：  フォルダのパス , 偽装する種類
//  戻り値：  成功 == 0
//  備  考：  関数を消すのがめんどくさいので、多重定義。(ビバ!C++
/*----------------------------------------------------------------------------*/
int CFolder::Fake(LPCTSTR lpPath, CString &r_cNewPath, int nType, int nMode)
{
	// フォルダかどうかのチェック
	CFileApi cFileApi;
	BOOL bRes = cFileApi.CheckDirectory(lpPath);

	// ファイルなら、エラー
	if(bRes == FALSE){ return F_FILE;}

	/* 偽装を行う */
	CString cBuf;

	/*if(nMode = F_NORMAL || nMode == F_COMPATIBLE)
	{
		cBuf = Fake(lpPath , nType);
		r_cNewPath = cBuf;
	}*/
	 
	if(nMode == F_PASSWORD)
	{
		// 暗号化
		m_pEncode ->SetPath(lpPath);
		
		if(m_pEncode ->Encode() != 0)
		{
			return F_CANCEL;
		}
	}

	// 普通に偽装する
	cBuf = Fake(lpPath , nType);
	r_cNewPath = cBuf;
	

	return F_SUCUESS;
}
