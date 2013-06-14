// Fox.h : FOX アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_FOX_H__1189414C_090F_476D_935C_B7EE5CAFBBFB__INCLUDED_)
#define AFX_FOX_H__1189414C_090F_476D_935C_B7EE5CAFBBFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CFoxApp:
// このクラスの動作の定義に関しては Fox.cpp ファイルを参照してください。
//

class CFoxApp : public CWinApp
{
public:
	CFoxApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CFoxApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FOX_H__1189414C_090F_476D_935C_B7EE5CAFBBFB__INCLUDED_)
