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
	CGamepad();
	virtual~CGamepad();						//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void	Uninit(void);
	virtual void	Update(void);

	static void ButtonSet(DIJOYSTATE pad_data, int nCnt);
	static bool IsButtonPush(KEYINFO button);
	static bool IsButtonUp(KEYINFO button);
	static bool IsButtonDown(KEYINFO button);
	bool BuPu(KEYINFO button, int nCnt);
	bool BuUp(KEYINFO button, int nCnt);
	bool BuDo(KEYINFO button, int nCnt);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// �R�[���o�b�N�֐�
	int GetNumControl(void);
};

#endif