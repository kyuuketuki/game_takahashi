//=============================================================================
//
// メイン処理 [input.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "input.h"
#include "main.h"

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
//　コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CInput::~CInput()
{

}

//=============================================================================
//　初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_pInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return hr;
}

//=============================================================================
//　終了処理
//=============================================================================
void CInput::Uninit(void)
{
	//データフォーマットの開放
	if (m_pDevice != NULL)
	{
		//アクセス権の破棄
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
//　キーボード処理 継承先input
//=============================================================================

//=============================================================================
//　コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//m_aKeyState[256] = 0;
	//m_aKeyStateTrigger[256] = 0;
	//m_aKeyStateRelease[256] = 0;
	//m_aKeyStateRepeat[256] = 0;

	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateRepeat[0], 0, sizeof(m_aKeyStateRepeat));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
//　デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
//　初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//アクセス権の取得
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
//　終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
//　更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			//押したとき
			m_aKeyStateTrigger[nKey] = (~m_aKeyState[nKey]) & aKeyState[nKey];

			//離したとき
			m_aKeyStateRelease[nKey] = m_aKeyState[nKey] & (~aKeyState[nKey]);

			//押し続けたとき
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}

	else
	{
		//アクセス権の取得
		m_pDevice->Acquire();
	}
}

//=============================================================================
//　プレス
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
//　トリガー
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//　リリース
//=============================================================================
bool CInputKeyboard::GetReleace(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
