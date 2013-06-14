// Encode.cpp: CEncode クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fox.h"
#include "Encode.h"

#include "FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_BUFFER 32767
#define ARCHIVE_FILE _T("_pass.zip")
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CEncode::CEncode()
{
	// イテレータの初期化
	m_itFile = m_liFile.begin();
}

CEncode::~CEncode()
{
	// 各DLLの解放
	::FreeLibrary(m_hZipLib);
	::FreeLibrary(m_hUnzipLib);
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダのパスを設定する
//  引  数：  フォルダのパス
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::SetPath(LPCTSTR lpPath)
{
	m_inMax = 0;
	// パスを"C:\windows\"という形にする。(最後が'\')
	CString cPath = lpPath;
	cPath.TrimRight("\\");
	cPath += "\\";
	
	m_cPath = cPath;
	// 次は、フォルダ内のファイルを取得する
	CFileFind cFind;

	if(cFind.FindFile(cPath + "*") != 0)
	{
		int i = 1;

		while(i)
		{
			i = cFind.FindNextFile();

			if(cFind.IsDots()){ continue; }

			// ファイル名をリストに追加する
			m_liFile.push_front(cFind.GetFileName());
			m_inMax++;
		}

		return 0;
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダのパスを取得する
//  引  数：  void
//  戻り値：  フォルダのパス
//  備  考：  void
/*----------------------------------------------------------------------------*/
CString CEncode::GetPath()
{
	return m_cPath;
}

/*----------------------------------------------------------------------------*/
//  概  要：  ファイルを暗号化する
//  引  数：  void
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::Encode()
{
	// Zio32j.dllで圧縮するために、レスポンスファイルに全ファイルを書き込む
	CString cResponse;
	if(WriteResponse(cResponse) != 0)
	{
		AfxMessageBox(_T("レスポンスファイルへの書き込みに失敗しました。"));
	}
	
	// コマンドラインを作る
	CString cCmdLine , cOption , cFilePath , cDirectory;
	cOption = "-r -e";
	cFilePath = m_cPath + ARCHIVE_FILE;
	
	cCmdLine = cOption + _T(" \"") + cFilePath + _T("\" \"") + m_cPath + _T("\" \"@") 
				+ cResponse+ _T("\"") ;

	// 圧縮を行う
	if(Zip(cCmdLine) != 0)
	{
		::AfxMessageBox(_T("ZIP圧縮に失敗しました。"));
		return -1;
	}else{

		// ファイルを削除する
		return FileDelete();
	}


}

/*----------------------------------------------------------------------------*/
//  概  要：  ファイルを圧縮する
//  引  数：  コマンド
//  戻り値：  正常終了 == 0
//  備  考：  Zip32j.dllをロードするだけ。
/*----------------------------------------------------------------------------*/
int CEncode::Zip(LPCTSTR lpCmdLine)
{
	if(m_hZipLib != NULL)
	{
		typedef  int(WINAPI ZIP)(const HWND , LPCTSTR , LPSTR , const DWORD);

		// 関数をロードする
		ZIP *pZip = (ZIP*)::GetProcAddress(m_hZipLib , "Zip");

		if(pZip == NULL){ return -1;}

		// 関数を呼ぶ
		char chBuffer[MAX_BUFFER + 1];
		return pZip(NULL , lpCmdLine , chBuffer , MAX_BUFFER);
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  いろいろな初期処理
//  引  数：  void
//  戻り値：  void
//  備  考：  必ず呼ぶこと
/*----------------------------------------------------------------------------*/
void CEncode::Load()
{
	// 各DLLをロードする
	m_hZipLib = ::LoadLibrary("Zip32j.dll");
	m_hUnzipLib = ::LoadLibrary("Unzip32.dll");
}

/*----------------------------------------------------------------------------*/
//  概  要：  レスポンスファイルにファイルのリストを書き込む
//  引  数：  void
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::WriteResponse(CString &r_cResponse)
{
	// 一時ファイルの取得
	CString cTempPath;
	CFileApi cFileApi;
	cTempPath = cFileApi.GetTempPath();

	// 一時ファイルに書き込む
	CStdioFile cFile;

	if(cFile.Open(cTempPath , CFile::modeWrite) != 0)
	{
		for(m_itFile = m_liFile.begin() ; m_itFile != m_liFile.end() ; m_itFile++)
		{
			cFile.WriteString(*m_itFile + "\n");
		}

		m_liFile.erase(m_liFile.begin() , m_liFile.end());

		cFile.Close();
		r_cResponse = cTempPath;
		return 0;
	}else{
		return 1;
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  圧縮したあと、ファイルを削除する
//  引  数：  void
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::FileDelete()
{
	CFileApi cFileApi;
	int nRes = 0;

	for(m_itFile = m_liFile.begin() ; m_itFile != m_liFile.end() ; m_itFile++)
	{
		nRes = cFileApi.Delete(m_cPath + *m_itFile);
	}

	return nRes;
}

/*----------------------------------------------------------------------------*/
//  概  要：  Unzip32.dll内のUnzip()呼び出し
//  引  数：  コマンドライン
//  戻り値：  0　--- 正常
//  備  考：  DLLの動的ロード
/*----------------------------------------------------------------------------*/
int CEncode::Unzip(LPCTSTR lpCmdLine)
{
	if(m_hUnzipLib != NULL)
	{
		typedef  int(WINAPI UNZIP)(const HWND , LPCTSTR , LPSTR , const DWORD);

		UNZIP* pUnzip = (UNZIP*)::GetProcAddress(m_hUnzipLib , _T("UnZip"));

		if(pUnzip == NULL){ AfxMessageBox(_T("API(Unzip)のロードに失敗しました。"));}

		// 関数を呼ぶ
		char chBuffer[MAX_BUFFER + 1];
		return pUnzip(NULL , lpCmdLine , chBuffer , MAX_BUFFER);
	}else{
		return -1;
	}
}

/*----------------------------------------------------------------------------*/
//  概  要：  フォルダを復号化する
//  引  数：  void
//  戻り値：  成功 == 0
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::Decode()
{
	CString cCmdLine , cOption , cDirectory , cArchive;

	cOption = _T("-x");
	cArchive = _T("\"") + m_cPath + ARCHIVE_FILE +_T("\"");
	cDirectory = _T("\"") + m_cPath + _T("\"");

	cCmdLine = cOption + _T(" ") + cArchive + _T(" ") + cDirectory;

	int nRes = Unzip(cCmdLine);

	// ファイルの削除
	if(::DeleteFile(m_cPath + ARCHIVE_FILE) == 0)
	{
		::AfxMessageBox(ARCHIVE_FILE _T("の削除に失敗しました。"));
		DWORD dw = ::GetLastError();
	}
	return nRes;
}

/*----------------------------------------------------------------------------*/
//  概  要：  暗号化されているかチェックする
//  引  数：  パス
//  戻り値：  true / false
//  備  考：  void
/*----------------------------------------------------------------------------*/
int CEncode::IsDecode(LPCTSTR lpPath)
{
	CString cPath = lpPath;
	cPath += "\\"ARCHIVE_FILE;

	if(::GetFileAttributes(cPath) != 0xFFFFFFFF)
	{
		return TRUE;
	}else{
		return FALSE;
	}
}
