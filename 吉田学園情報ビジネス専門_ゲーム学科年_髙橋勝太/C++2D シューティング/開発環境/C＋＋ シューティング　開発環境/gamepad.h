//==============================================================================
//
// ���͏����i�Q�[���p�b�h�j�kgamepad.h�l
// AUTHOR : takahashi shouta
//
//==============================================================================
#pragma once
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

//==============================================================================
// �L�[����
//==============================================================================
// �f�o�C�X�̗�
typedef enum
{
	DIDEVTYPE_MOUSE = 0,	// �}�E�X
	DIDEVTYPE_KEYBOARD,		// �L�[�{�[�h
	DIDEVTYPE_JOYSTICK,		// �W���C�X�e�B�b�N
	DIDEVTYPE_DEVICE,		// ���̑�
	DIDEVTYPE_MAX
} DIDEVTYPE;

typedef enum
{
	ButtonStateNone = 0,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
} ButtonState;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
// �R���g���[���[�̐����擾
class CGamepad : public CInput
{
public:
	CGamepad();								//�R���X�g���N�^
	virtual~CGamepad();						//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void	Uninit(void);							//�I������
	virtual void	Update(void);							//�X�V����
															
	static void ButtonSet(DIJOYSTATE pad_data, int nCnt);	//�X�e�B�b�N���{�^������
	static bool IsButtonPush(KEYINFO button);				//�v���X
	static bool IsButtonUp(KEYINFO button);					//�����[�X
	static bool IsButtonDown(KEYINFO button);				//�g���K�[
	bool BuPu(KEYINFO button, int nCnt);					//�v���X	����
	bool BuUp(KEYINFO button, int nCnt);					//�����[�X	����
	bool BuDo(KEYINFO button, int nCnt);					//�g���K�[	����
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// �R�[���o�b�N�֐�
	int GetNumControl(void);
};

#endif