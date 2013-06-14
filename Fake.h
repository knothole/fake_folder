// 定数の宣言
#ifndef _FAKE_H_
#define _FAKE_H_

// エラーコード
enum{
	F_SUCUESS = 0,	// 成功
	F_CANCEL,
	F_FILE,
	F_ERROR,
	F_PASSERORR	,
	F_SAMENAME	// リネームする意味がない(==偽装済み || 解除済み)
};

// 偽装モード
enum{
	F_NORMAL = 0,
	F_COMPATIBLE,
	F_PASSWORD,
	F_OPENFOLDER
};

#endif // _FAKE_H_