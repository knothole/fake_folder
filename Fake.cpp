#ifndef _FAKE_H_
#define _FAKE_H_
// �萔�̐錾
enum{
	F_SUCUESS = 0,	// ����
	F_CANCEL,
	F_FILE,
	F_ERROR,
	F_PASSERORR	,
	F_SAMENAME	// ���l�[������Ӗ����Ȃ�(==�U���ς� || �����ς�)
};

enum{
	F_NORMAL = 0,
	F_COMPATIBLE,
	F_PASSWORD
};

#endif // _FAKE_H_
