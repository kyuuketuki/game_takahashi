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
	CGamepad();								//コンストラクタ
	virtual~CGamepad();						//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void	Uninit(void);							//終了処理
	virtual void	Update(void);							//更新処理
															
	static void ButtonSet(DIJOYSTATE pad_data, int nCnt);	//スティック＆ボタン処理
	static bool IsButtonPush(KEYINFO button);				//プレス
	static bool IsButtonUp(KEYINFO button);					//リリース
	static bool IsButtonDown(KEYINFO button);				//トリガー
	bool BuPu(KEYINFO button, int nCnt);					//プレス	複数
	bool BuUp(KEYINFO button, int nCnt);					//リリース	複数
	bool BuDo(KEYINFO button, int nCnt);					//トリガー	複数
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// コールバック関数
	int GetNumControl(void);
};

#endif