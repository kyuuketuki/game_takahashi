//=============================================================================
//
// メイン処理 [game.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include "polygon.h"
#include "life.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "item.h"
#include "fade.h"
#include "logo.h"

//マクロ定義
#define WAVE_1		(100)		
#define WAVE_2		(21)	
#define WAVE_3		(00)	

//時間
int nTimeGame = 0;
int nTimeCounter = 0;

//敵を倒した回数
int g_nDaed = 0;
bool g_bDead = false;

bool g_bDaed[2] = {};

//画面遷移用
bool g_bMigrate = false;		

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame()
{
	//初期化
	nTimeGame = 0;
	nTimeCounter = 0;

	g_bMigrate = false;		//画面遷移用
}

//==============================================================================
// デストラクタ
//==============================================================================
CGame::~CGame()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンドBGM
	pSound->Play(CSound::SOUND_LABEL_BGM003);

	// フォントオブジェクトの生成
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//現在のステージをManaagerに記憶させる
	CManager::SetGameStage(1);

	//クリア条件初期化
	CManager::SetEnemyDead(0);

	//特殊攻撃をオフにする
	CEnemy::NextAttack(0);

	//プレイヤーの生成
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MAX_LIFE, PLAYER_SIZE, PLAYER_SIZE);

	//背景を表示
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//HPバー
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CLife::Create(D3DXVECTOR3(40.0f + (80.0f * nCnt), 100.0f, 0.0f), 30.0f, 30.0f);
	}

	//スコア
	CScore::Create(D3DXVECTOR3(1800.0f, 50.0f, 0.0f), 100.0f, 100.0f);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CGame::Uninit(void)
{
	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド設置
	pSound->Stop(CSound::SOUND_LABEL_BGM003);

	// オブジェクト破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CGame::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//カウント
	nTimeCounter++;

	//カウンターが60以上になったら
	if (nTimeCounter >= 60)
	{
		nTimeGame++;

		//カウンターを戻す
		nTimeCounter = 0;
	}

	//敵の出現＆攻撃に関する
	Attack2();

	//中ボスを1体倒した場合
	if (CManager::GetEnemyDead() == 11)		//条件を満たしている場合
	{
		//画面遷移条件
		if (g_bMigrate == false)
		{
			g_bMigrate = true;
			nTimeGame = 100;
			nTimeCounter = 0;
		}
	}

	//敵を倒してから2秒経過後に画面遷移
	if (g_bMigrate == true)
	{
		if (nTimeGame == 103 && nTimeCounter == 0)
		{
			//画面遷移
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));	// シーン遷移
		}
	}

	//敵を倒し切った場合にタイムスキップ
	if (g_bDead == false)
	{
		if (CManager::GetEnemyDead() == 2)		//条件を満たしている場合
		{
			if (nTimeGame < 20)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = 20;		//タイムスキップ
			}
		}

		if (CManager::GetEnemyDead() == 10)		//条件を満たしている場合
		{
			if (nTimeGame < 42)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = 42;		//タイムスキップ
			}
		}
	}

	//値が変化した場合に条件を解除
	if (g_nDaed != CManager::GetEnemyDead())
	{
		g_bDead = false;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CGame::Draw(void)
{
#ifdef _DEBUG
	// ローカル変数宣言
	RECT rect = { -1500,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//画面に表示させる
	sprintf(&aStr[0], "GAME画面の経過時間 : %d\n", CManager::GetEnemyDead());

	// テキストの描画
	m_pTimeFontGame->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//==============================================================================
//敵の移動管理
//==============================================================================
void CGame::Attack(void)
{
	if (nTimeGame == 1 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(800.0f, -300.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(800.0f, -400.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 4);
	}

	if (nTimeGame == 4 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 10.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 3 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 800.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 3 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 700.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 3 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 3 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 5 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(1800.0f, 400.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 5 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(1700.0f, 300.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 5 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(1600.0f, 200.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 5 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(1500.0f, 100.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 5 && nTimeCounter == 4)
	{
		//CEnemy::MoveClear();
	}

	if (nTimeGame == 9 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 18, ENEMY_01, 4);
	}

	if (nTimeGame == 10 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 10.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 14, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 13 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 400.0f, 0.0f), 15.0f, 1);
	}

	if (nTimeGame == 13 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 300.0f, 0.0f), 15.0f, 2);
	}

	if (nTimeGame == 13 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 400.0f, 0.0f), 15.0f, 3);
	}

	if (nTimeGame == 13 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 300.0f, 0.0f), 15.0f, 4);
	}

	if (nTimeGame == 13 && nTimeCounter == 4)
	{
		//CEnemy::MoveClear();
	}

	if (nTimeGame == 15 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 19, ENEMY_01, 5);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(500.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 19, ENEMY_01, 6);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 7);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 8);
	}

	if (nTimeGame == 16 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 20 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 1);
		CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 26, ENEMY_01, 4);
	}

	if (nTimeGame == 22 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 800.0f, 0.0f), 5.0f, 1);
	}

	if (nTimeGame == 22 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 900.0f, 0.0f), 5.0f, 2);
	}

	if (nTimeGame == 22 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 800.0f, 0.0f), 5.0f, 3);
	}

	if (nTimeGame == 22 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 900.0f, 0.0f), 5.0f, 4);
	}

	if (nTimeGame == 25 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 400.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 25 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 500.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 25 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 400.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 25 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 500.0f, 0.0f), 10.0f, 4);
		
		CEnemy::MoveClear();
	}

	if (nTimeGame == 27 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(800.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_02, 1);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(800.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_03, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 400.0f, 0.0f),200, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_02, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_03, 4);
	}

	if (nTimeGame == 28 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 28 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 100.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 28 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 28 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 30 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 300.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 30 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 300.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 30 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 30 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 100.0f, 300.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 32 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 32 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 32 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 600.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 32 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(700.0f, 600.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 35 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 35 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 35 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(500.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 35 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(700.0f, 200.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 30 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 35 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 38 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 42, ENEMY_01, 0);
		}

		CEnemy::MoveClear();
	}

	if (nTimeGame == 42 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(300.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(1000.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(1100.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 300.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, 400.0f, 0.0f), 200, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 1100.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 50, ENEMY_03, 0);
	}

	if (nTimeGame == 50 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 57, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 58 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 68, ENEMY_02, 0);
		}
	}

	if (nTimeGame == 62 && nTimeCounter == 0)
	{
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			int nRnadXPos = rand() % SCREEN_WIDTH;
			int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
			int nRnadYOjective = rand() % 400;
			CEnemy::Create(D3DXVECTOR3(nRnadXPos, -100.0f, 0.0f), 3.0f, D3DXVECTOR3(nRnadXOjective + 100.0f, nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 68, ENEMY_01, 0);
		}
	}

	if (nTimeGame == 70 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 1);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 300.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 2);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 3);
		CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 100.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 4);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 5);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 6);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 7);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 90, ENEMY_04, 8);
	}

	//特殊攻撃に変更
	if (nTimeGame == 73 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(2);
	}

	if (nTimeGame == 74 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 74 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 74 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 74 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 74 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 1000.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 74 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 900.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 74 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 800.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 74 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 700.0f, 0.0f), 10.0f, 8);
	}

	//移動
	if (nTimeGame == 78 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 78 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 78 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 78 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 78 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 78 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 78 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 78 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 10.0f, 8);
	}

	//特殊攻撃に変更
	if (nTimeGame == 81 && nTimeCounter == 50)
	{
		CEnemy::NextAttack(3);
	}

	//移動
	if (nTimeGame == 82 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 82 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 1000.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 82 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 1000.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 82 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 1000.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 82 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 82 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(600.0f, 100.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 82 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 82 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 8);
	}

	//特殊攻撃に変更
	if (nTimeGame == 85 && nTimeCounter == 50)
	{
		CEnemy::NextAttack(4);
	}

	//移動
	if (nTimeGame == 86 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 86 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 400.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 86 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 200.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 86 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 86 && nTimeCounter == 4)
	{
		CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 5);
	}

	if (nTimeGame == 86 && nTimeCounter == 5)
	{
		CEnemy::NextMove(D3DXVECTOR3(400.0f, 400.0f, 0.0f), 10.0f, 6);
	}

	if (nTimeGame == 86 && nTimeCounter == 6)
	{
		CEnemy::NextMove(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 10.0f, 7);
	}

	if (nTimeGame == 86 && nTimeCounter == 7)
	{
		CEnemy::NextMove(D3DXVECTOR3(800.0f, 800.0f, 0.0f), 10.0f, 8);
	}

	//特殊攻撃に変更
	if (nTimeGame == 90 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(0);
	}

	//隕石
	if (nTimeGame >= 90 && nTimeGame <= 150)
	{
		int nRand = rand() % 50;
		int nRandX = rand() % SCREEN_WIDTH - 300.0f;

		if (nRand == 1)
		{
			//敵生成
			CEnemy::Create(D3DXVECTOR3(nRandX + 150.0f, -50.0f, 0.0f), 2.0f, D3DXVECTOR3(nRandX + 150.0f, 2000.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 1, ENEMY_99, 0);
		}
	}

	if (nTimeGame == 94 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 1);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 2);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 3);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 4);
	}

	//移動
	if (nTimeGame == 96 && nTimeCounter == 0)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200.0f, 600.0f, 0.0f), 10.0f, 1);
	}

	if (nTimeGame == 96 && nTimeCounter == 1)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, 600.0f, 0.0f), 10.0f, 2);
	}

	if (nTimeGame == 96 && nTimeCounter == 2)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 600.0f, 0.0f), 10.0f, 3);
	}

	if (nTimeGame == 96 && nTimeCounter == 3)
	{
		CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f, 600.0f, 0.0f), 10.0f, 4);
	}

	if (nTimeGame == 98 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 900.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 900.0f, 200.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
	}

	if (nTimeGame == 102 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 800.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 900.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 800.0f, 800.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 900.0f, 1000.0f, 0.0f), 1000, ENEMY_SIZE, ENEMY_SIZE, 120, ENEMY_04, 0);
	}

	//特殊攻撃に変更
	if (nTimeGame == 105 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(4);
	}

	//特殊攻撃に変更
	if (nTimeGame == 122 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(0);
	}

	if (nTimeGame == 123 && nTimeCounter == 0)
	{
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 - 500.0f, 300.0f, 0.0f), 3000, ENEMY_SIZE + 100, ENEMY_SIZE + 100, 120, ENEMY_05, 0);
		CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 600.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 300.0f, 0.0f), 3000, ENEMY_SIZE + 100, ENEMY_SIZE + 100, 120, ENEMY_05, 0);
	}

	//特殊攻撃に変更
	if (nTimeGame == 125 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(5);
	}

	//特殊攻撃に変更
	if (nTimeGame == 130 && nTimeCounter == 0)
	{
		CEnemy::NextAttack(6);
	}

	if (nTimeGame == 131 && nTimeCounter == 0)
	{
		//モード設定
		CManager::SetMode(CManager::MODE_GAME2);
	}
}

void CGame::Attack2(void)
{
	///ランダムにアイテムを生成
	int nRand = rand() % 1000;
	int nRandX = rand() % SCREEN_WIDTH;

	if (nRand == 1)
	{
		//アイテム生成
		CItem::Create(D3DXVECTOR3(nRandX, 0.0f, 0.0f), 2.0f, 50, 50, 0);
	}

	else if (nRand == 2 || nRand == 3)
	{
		//アイテム生成
		CItem::Create(D3DXVECTOR3(nRandX, 0.0f, 0.0f), 2.0f, 50, 50, 1);
	}

	//1
	{
		if (nTimeGame == 1 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_06, 0);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH - 700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, 20, ENEMY_07, 0);
		}

		//特殊攻撃に変更
		if (nTimeGame == 2 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(8);
		}
	}

	//2
	{
		if (nTimeGame == WAVE_2 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(0);		//特殊攻撃に変更
			CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 1);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 300.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 2);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 3);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 100.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 4);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 5);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 6);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 7);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, 40, ENEMY_04, 8);
		}

		//特殊攻撃に変更
		if (nTimeGame == WAVE_2 + 1 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 1000.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 900.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 800.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 700.0f, 0.0f), 10.0f, 8);
		}

		//移動
		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 10.0f, 8);
		}

		//特殊攻撃に変更
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(3);
		}

		//移動
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 1000.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 1000.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 100.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 8);
		}

		//特殊攻撃に変更
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(10);
		}

		//移動
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 600.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 400.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 400.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 8);
		}
	}

	//アイテム生成
	if (nTimeGame == 42 && nTimeCounter == 0)
	{
		CItem::Heart2(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f), 2.0f, 50, 50, 1, 0);
	}

	//3
	{
		if (nTimeGame == 45 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 5000, ENEMY_SIZE + 50, ENEMY_SIZE + 50, 999, ENEMY_05, 1);
		}

		//特殊攻撃に変更
		if (nTimeGame == 46 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(9);
		}

		//特殊攻撃に変更
		if (nTimeGame == 53 && nTimeCounter == 0)
		{
			CEnemy::NextAttack2(11);
		}
	}
}

//==============================================================================
// Get関数タイム
//==============================================================================
int CGame::GetTime(void)
{
	return nTimeGame;
}

//==============================================================================
// 生成処理
//==============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CGame *pGame;
	pGame = new CGame;

	// NULLチェック
	if (pGame != NULL)
	{
		pGame->Init(pos, fSizeX, fSizeY);
	}

	return pGame;
}
