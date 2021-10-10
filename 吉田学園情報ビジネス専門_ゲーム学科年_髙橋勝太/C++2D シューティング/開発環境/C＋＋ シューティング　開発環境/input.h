//=============================================================================
//
// メイン処理 [input.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==============================================================================
// キー入力
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
// 入力クラスの定義
//=============================================================================
class CInput
{
public:
	CInput();								//コンストラクタ
	virtual~CInput();						//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void	Uninit(void);							//終了処理
	virtual void	Update(void) = 0;						//更新処理
															
protected:
	static LPDIRECTINPUT8	m_pInput;						
	LPDIRECTINPUTDEVICE8	m_pDevice = NULL;				//デバイスポインター
};															

//=============================================================================
// キーボードクラスの定義
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();						//コンストラクタ
	~CInputKeyboard();						//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	void	Uninit(void);							//終了処理
	void	Update(void);							//更新処理
	bool	GetPress(int nKey);						//プレス
	bool	GetTrigger(int nKey);					//トリガー
	bool	GetReleace(int nKey);					//リリース
													
protected:											
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
	BYTE m_aKeyStateRelease[256];
	BYTE m_aKeyStateRepeat[256];
};

#endif
