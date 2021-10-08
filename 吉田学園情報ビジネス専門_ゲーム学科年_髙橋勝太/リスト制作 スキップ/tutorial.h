//=============================================================================
//
// メイン処理 [tutorial.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
//継承先描画クラス
class CTutorial : public CScene
{
public:
	CTutorial();									//コンストラクタ
	~CTutorial();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static int GetTime(void);

	static CTutorial *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	static CPlayer				*m_pPlayer;			//プレイヤーへのポインタ	ホーミング時に使用
	LPD3DXFONT					m_pTimeFontGame;	// 表示用フォント
};

#endif