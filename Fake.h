// �萔�̐錾
#ifndef _FAKE_H_
#define _FAKE_H_

// �G���[�R�[�h
enum{
	F_SUCUESS = 0,	// ����
	F_CANCEL,
	F_FILE,
	F_ERROR,
	F_PASSERORR	,
	F_SAMENAME	// ���l�[������Ӗ����Ȃ�(==�U���ς� || �����ς�)
};

// �U�����[�h
enum{
	F_NORMAL = 0,
	F_COMPATIBLE,
	F_PASSWORD,
	F_OPENFOLDER
};

#endif // _FAKE_H_