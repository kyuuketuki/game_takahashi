//=============================================================================
//
// メイン処理 [menu.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "menu.h"
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "fade.h"

int g_nPointerMenuX = 0;
bool g_bButtonDownMenu = false;

//==============================================================================
// コンストラクタ
//==============================================================================
CMenu::CMenu()
{
	g_nPointerMenuX = 0;
	g_bButtonDownMenu = false;
}

//==============================================================================
// 
//==============================================================================
CMenu::~CMenu()
{

}

//==============================================================================
// 
//==============================================================================
HRESULT CMenu::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//背景を表示
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 200, 50, 6);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 210, 60, 9);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 200, 50, 7);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, 8);

	//アニメーションオブジェクト
	CAnimasion::Create(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 300, 300, 10, 15);
	CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 200.0f, 0.0f), 300, 300, 10, 16);

	return S_OK;
}

//==============================================================================
// 
//==============================================================================
void CMenu::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//==============================================================================
// 
//==============================================================================
void CMenu::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_S) == true || CGamepad::IsButtonDown(DOWN))
	{
		if (g_nPointerMenuX == 0)
		{
			g_nPointerMenuX = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 9);
		}

		else if (g_nPointerMenuX == 1)
		{
			g_nPointerMenuX = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
		}

		else if (g_nPointerMenuX == 2)
		{
			g_nPointerMenuX = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 9);
		}

		//サウンドSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true || CGamepad::IsButtonDown(UP))
	{
		if (g_nPointerMenuX == 0)
		{
			g_nPointerMenuX = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
		}

		else if (g_nPointerMenuX == 1)
		{
			g_nPointerMenuX = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 9);
		}

		else if (g_nPointerMenuX == 2)
		{
			g_nPointerMenuX = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 9);
		}

		//サウンドSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	//初めて押した場合
	if (g_bButtonDownMenu == false)
	{
		//画面遷移
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || CGamepad::IsButtonDown(A) || CGamepad::IsButtonDown(B) == true)
		{
			if (g_nPointerMenuX == 0)
			{
				//モード設定
				//CManager::SetMode(CManager::MODE_SELECT);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// シーン遷移
			}

			if (g_nPointerMenuX == 1)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TUTORIAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
			}

			if (g_nPointerMenuX == 2)
			{
				//モード設定
				//CManager::SetMode(CManager::MODE_TITLE);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
			}

			//連打防止
			g_bButtonDownMenu = true;

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//==============================================================================
// 
//==============================================================================
void CMenu::Draw(void)
{

}

//==============================================================================
// 
//==============================================================================
CMenu * CMenu::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CMenu *pMenu;
	pMenu = new CMenu;

	// NULLチェック
	if (pMenu != NULL)
	{
		pMenu->Init(pos, fSizeX, fSizeY);
	}

	return pMenu;
}
