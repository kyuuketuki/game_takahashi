//=============================================================================
//
// メイン処理 [pause.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
//継承先描画クラス
class CPause : public CScene
{
public:
	CPause(int nPriority = 0, int nType = 2);				//コンストラクタ;									//コンストラクタ
	~CPause();												//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
};

#endif