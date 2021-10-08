//=============================================================================
//
// メイン処理 [game2.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
//継承先描画クラス
class CResult : public CScene
{
public:
	CResult();									//コンストラクタ
	~CResult();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Attack(void);

	static int GetTime(void);

	static CResult *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	static CPlayer				*m_pPlayer;			//プレイヤーへのポインタ	ホーミング時に使用
	LPD3DXFONT					m_pTimeFontGame;	// 表示用フォント
};

#endif