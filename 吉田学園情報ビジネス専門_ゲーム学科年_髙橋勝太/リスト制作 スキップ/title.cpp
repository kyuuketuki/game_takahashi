  //=============================================================================
//
// メイン処理 [title.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "title.h"
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "gamepad.h"
#include "fade.h"

int nTimeTitle = 0;
int nTimeCounterTitle = 0;
int nNexEnterCount = 0;
int nSaveTime = -1;
int nSaveTime2 = -1;
int nFlashing = 30;					//PressEnterの点滅させる速度
bool g_bPressEnter = false;
bool g_bNextEnter = false;
bool g_bButtonDownTitle = false;

//==============================================================================
// コンストラクタ
//==============================================================================
CTitle::CTitle()
{
	//初期化
	nTimeTitle = 0;
	nTimeCounterTitle = 0;
	nNexEnterCount = 0;
	nSaveTime = -1;
	nSaveTime2 = -1;
	nFlashing = 30;
	g_bPressEnter = false;
	g_bNextEnter = false;
	g_bButtonDownTitle = false;
}

//==============================================================================
// デストラクタ
//==============================================================================
CTitle::~CTitle()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//背景を表示
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//アニメーションを表示
	CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 4);

	//ロゴを表示
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 500, 200, 31);

	////モデルの表示
	//m_pSceneX = new CSceneX;
	//m_pSceneX->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);

	//アニメーションテクスチャの読み込み
	CAnimasion::Load();
	
	CSceneX::Create();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CTitle::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CTitle::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//タイトルロゴが表示された状態
	if (nTimeTitle >= 2 && nTimeCounterTitle >= 0)
	{
		if (g_bPressEnter == false)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 150, 50, 4);
			g_bPressEnter = true;
		}

		//点滅処理　NextEnter
		if (g_bPressEnter == true)
		{
			nNexEnterCount++;
			if (nNexEnterCount == nFlashing)
			{
				if (g_bNextEnter == true)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 4);
					g_bNextEnter = false;
				}

				else if (g_bNextEnter == false)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);
					g_bNextEnter = true;
				}

				nNexEnterCount = 0;
			}
		}

		//初めて押した場合のみ
		if (g_bButtonDownTitle == false)
		{
			//画面遷移
			if (CGamepad::IsButtonDown(A) == true || CGamepad::IsButtonDown(B) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				//アニメーション
				//CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 10);

				//サウンドSE
				pSound->Play(CSound::SOUND_LABEL_SE_METEOR);

				//画面遷移に関する変数
				nTimeCounterTitle = 0;

				//点滅に関する変数
				nFlashing = 10;
				nNexEnterCount = 0;

				//ボタンを押したタイムを保存
				nSaveTime = nTimeTitle;
				nSaveTime2 = 30;

				//連打防止
				g_bButtonDownTitle = true;
			}
		}

		//遷移条件アニメーションが終了後
		if ((nSaveTime + 1) == nTimeTitle && nSaveTime2 == nTimeCounterTitle)
		{
			//モード設定
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_MENU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
		}
	}

	//タイムを進める
	nTimeCounterTitle++;

	//カウンターが60以上になったら
	if (nTimeCounterTitle >= 60)
	{
		nTimeTitle++;

		//カウンターを戻す
		nTimeCounterTitle = 0;
	}

	//タイムに合わせて生成
	if (nTimeTitle == 1 && nTimeCounterTitle == 10)
	{
		CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 1);

		//サウンドSE
		pSound->Play(CSound::SOUND_LABEL_SE_STER);
	}

	if (nTimeTitle == 1 && nTimeCounterTitle == 20)
	{
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 500, 200, 0);
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CTitle::Draw(void)
{

}

//==============================================================================
// 生成処理
//==============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CTitle *pTitle;
	pTitle = new CTitle;

	// NULLチェック
	if (pTitle != NULL)
	{
		pTitle->Init(pos, fSizeX, fSizeY);
	}

	return pTitle;
}
