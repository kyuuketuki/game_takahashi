//=============================================================================
//
// ���C������ [input.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==============================================================================
// �L�[����
//==============================================================================
typedef enum
{
	RETURN,
	X,
	W,
	S,
	A,
	D,
	SPACE,
	BACKSPACE,
	F,
	T,
	B,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	P,
	KEYINFO_MAX
} KEYINFO;

//=============================================================================
// ���̓N���X�̒�`
//=============================================================================
class CInput
{
public:
	CInput();								//�R���X�g���N�^
	virtual~CInput();						//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void	Uninit(void);
	virtual void	Update(void) = 0;

protected:
	static LPDIRECTINPUT8	m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevice = NULL;
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();						//�R���X�g���N�^
	~CInputKeyboard();						//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Update(void);
	bool	GetPress(int nKey);
	bool	GetTrigger(int nKey);
	bool	GetReleace(int nKey);

protected:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
	BYTE m_aKeyStateRelease[256];
	BYTE m_aKeyStateRepeat[256];
};

#endif
