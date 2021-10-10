//=============================================================================
//
// メイン処理 [game2.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "game2.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include "polygon.h"
#include "life.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "bullet.h"
#include "animation.h"
#include "result.h"
#include "item.h"
#include "logo.h"
#include "fade.h"

int nTimeGameResult = 0;
int nTimeCounterResult = 0;
int g_nPointerResultX = 0;
bool g_bButtonDownResult = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	//初期化
	g_nPointerResultX = 0;
	g_bButtonDownResult = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// フォントオブジェクトの生成
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//背景を表示
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	int nDeatCnt = CManager::GetEnemyDead();
	
	//Stage2でリザルト画面に遷移したとき
	if (CManager::GetGameStage() == 2)
	{
		//クリア条件
		if (CManager::GetGameClear() == true)
		{

			//ゲームオーバー時
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 400.0f, 150.0f, 32);
		}

		else
		{
			//ゲームオーバー時
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 27);
		}
	}

	if (CManager::GetGameStage() == 1)
	{
		//ゲームオーバー時
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 27);
	}
	
	//フレーム
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, 9);

	//ロゴ
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, 28);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, 29);

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, 30);	//背景を表示

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//画面遷移が始まってない場合
	if (g_bButtonDownResult == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_S) == true || CGamepad::IsButtonDown(DOWN))
		{
			if (g_nPointerResultX == 0)
			{
				g_nPointerResultX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			else if (g_nPointerResultX == 1)
			{
				g_nPointerResultX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerResultX == 2)
			{
				g_nPointerResultX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 9);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		if (pInputKeyboard->GetTrigger(DIK_W) == true || CGamepad::IsButtonDown(UP))
		{
			if (g_nPointerResultX == 0)
			{
				g_nPointerResultX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerResultX == 1)
			{
				g_nPointerResultX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 9);
			}

			else if (g_nPointerResultX == 2)
			{
				g_nPointerResultX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//画面遷移
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || CGamepad::IsButtonDown(A) || CGamepad::IsButtonDown(B) == true)
		{
			if (g_nPointerResultX == 0)
			{
				//モード設定
				//CManager::SetMode(CManager::MODE_SELECT);

				//Stage1でゲームオーバーになった場合
				if (CManager::GetGameStage() == 1)
				{
					//Stage1に遷移する
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// シーン遷移
				}

				//Stage1でゲームオーバーになった場合
				if (CManager::GetGameStage() == 2)
				{
					//Stage2に遷移する
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// シーン遷移
				}
			}

			if (g_nPointerResultX == 1)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
			}

			if (g_nPointerResultX == 2)
			{
				//モード設定
				//CManager::SetMode(CManager::MODE_TITLE);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
			}

			//画面遷移が始まった
			g_bButtonDownResult = true;

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CResult *pResult;
	pResult = new CResult;

	// NULLチェック
	if (pResult != NULL)
	{
		pResult->Init(pos, fSizeX, fSizeY);
	}

	return pResult;
}
