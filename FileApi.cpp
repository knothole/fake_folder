// FileApi.cpp: CFileApi クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFileApi::CFileApi()
{

}

CFileApi::~CFileApi()
{

}

/*----------------------------------------------------------------------------*/
//  概  要：  作業用のファイル名を取得する
//  引  数：  void
//  戻り値：  ファイルのフルパス
//  備  考：  GetTempPath() + GetTempFileName()
/*----------------------------------------------------------------------------*/
CString CFileApi::GetTempPath()
{
	TCHAR tchPath[MAX_PATH + 1];
	if(::GetTempPath(MAX_PATH , tchPath) != 0)
	{
		// ファイル名の取得
		TCHAR tchFileName[MAX_PATH +1 ];
		GetTempFileName(tchPath , "AIR",0,tchFileName);
		return tchFileName;
	}else{
		return "";
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダかどうかをチェックする
//  引  数：  フルパス
//  戻り値：  フォルダ / ファイル == TRUE / FALSE
//  備  考：  void
/*----------------------------------------------------------------------------*/
BOOL CFileApi::CheckDirectory(LPCTSTR lpPath)
{
	DWORD dwType = ::GetFileAttributes(lpPath);

	if(dwType & FILE_ATTRIBUTE_DIRECTORY && dwType != 0xFFFFFFFF)
	{
		// 存在して、フォルダの場合
		return TRUE;
	}else{
		return FALSE;
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダを再起的に削除する
//  引  数：  フォルダのパス
//  戻り値：  成功 == TRUE
//  備  考：  void
/*----------------------------------------------------------------------------*/
BOOL CFileApi::DeleteDirectory(LPCTSTR lpPathName)
{
	CFileFind fnd;
    CString strPathName = lpPathName;
    strPathName.TrimRight('\\');
    strPathName += _T("\\*.*");
    if(fnd.FindFile(strPathName, 0))
    {
        int i = 1;
        while(i)
        {
            i = fnd.FindNextFile();

            // ファイル名が"."か".."の場合は次を検索
            if(fnd.IsDots())
                continue;

            // 削除するファイル名取得
            // GetFilePath()にはバグがあり正確に取得できない場合があるので使わない
            CString strDeleteFile = lpPathName;
            strDeleteFile.TrimRight('\\');
            strDeleteFile += _T("\\") + fnd.GetFileName();

            // フォルダだった場合、再帰呼び出しでそのフォルダを削除
            if(fnd.IsDirectory())
                DeleteDirectory(strDeleteFile);

            // ファイルの削除
            else
                ::DeleteFile(strDeleteFile);
        }
        fnd.Close();

        // フォルダの削除
		CString cPath;
		cPath = lpPathName;
		cPath.TrimRight('\\');
        return ::RemoveDirectory(cPath);
    }

	return FALSE;
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダでもファイルでも削除する
//  引  数：  フルパス
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CFileApi::Delete(LPCTSTR lpPath)
{
	if(CheckDirectory(lpPath))
	{
		return DeleteDirectory(lpPath);
	}else{
		return ::DeleteFile(lpPath);
	}
}
