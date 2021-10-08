//==============================================================================
//
// 入力処理（ゲームパッド）〔gamepad.h〕
// AUTHOR : takahashi shouta
//
//==============================================================================
#pragma once
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

//==============================================================================
// キー入力
//==============================================================================
// デバイスの列挙
typedef enum
{
	DIDEVTYPE_MOUSE = 0,	// マウス
	DIDEVTYPE_KEYBOARD,		// キーボード
	DIDEVTYPE_JOYSTICK,		// ジョイスティック
	DIDEVTYPE_DEVICE,		// その他
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
// プロトタイプ宣言
//==============================================================================
// コントローラーの数を取得
class CGamepad : public CInput
{
public:
	CGamepad();
	virtual~CGamepad();						//デストラクタ

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
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// コールバック関数
	int GetNumControl(void);
};

#endif