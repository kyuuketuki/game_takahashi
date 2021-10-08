//=============================================================================
//
// メイン処理 [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
//継承先描画クラス
class CGame : public CScene
{
public:
	CGame();									//コンストラクタ
	~CGame();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attack(void);
	void Attack2(void);

	static int GetTime(void);

	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	LPD3DXFONT	m_pTimeFontGame;					// 表示用フォント
};

#endif