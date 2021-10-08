//=============================================================================
//
// メイン処理 [game2.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME2_H_
#define _GAME2_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
//継承先描画クラス
class CGame2 : public CScene
{
public:
	CGame2();									//コンストラクタ
	~CGame2();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attack(void);
	void Attack2(void);
	void Attack3(void);

	static int GetTime(void);

	static CGame2 *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	static CPlayer				*m_pPlayer;			//プレイヤーへのポインタ	ホーミング時に使用
	LPD3DXFONT					m_pTimeFontGame;	// 表示用フォント
};

#endif