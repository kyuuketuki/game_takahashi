//=============================================================================
//
// メイン処理 [pause.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "pause.h"
#include "logo.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "animation.h"
#include "fade.h"

int nTimeGamePause = 0;
int nTimeCounterPause = 0;
int g_nPointerPauseX = 0;
bool g_bButtonDownPause = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause(int nPriority, int nType) : CScene(nPriority, nType)
{
	//初期化
	g_nPointerPauseX = 0;
	g_bButtonDownPause = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//背景
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 31);

	//フレーム
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, 9);

	//ロゴ
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, 28);

	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, 29);

	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, 30);//背景を表示

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//画面遷移が始まってない場合
	if (g_bButtonDownPause == false)
	{
		//S＆↓を押した場合
		if (pInputKeyboard->GetTrigger(DIK_S) == true || CGamepad::IsButtonDown(DOWN))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 9);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//W＆↑を押した場合
		if (pInputKeyboard->GetTrigger(DIK_W) == true || CGamepad::IsButtonDown(UP))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 9);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 9);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//画面遷移
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || CGamepad::IsButtonDown(A) || CGamepad::IsButtonDown(B) == true)
		{
			if (g_nPointerPauseX == 0)
			{
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
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// シーン遷移
				}
			}

			if (g_nPointerPauseX == 1)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// シーン遷移
			}

			if (g_nPointerPauseX == 2)
			{
				//モード設定
				//CManager::SetMode(CManager::MODE_TITLE);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// シーン遷移
			}

			//画面遷移が始まった
			g_bButtonDownPause = true;

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CPause *pPause;
	pPause = new CPause;

	// NULLチェック
	if (pPause != NULL)
	{
		pPause->Init(pos, fSizeX, fSizeY);
	}

	return pPause;
}
