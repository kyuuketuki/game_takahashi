//=============================================================================
//
// メイン処理 [title.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// タイトルクラスの定義
//=============================================================================
//継承先描画クラス
class CTitle : public CScene
{
public:
	CTitle();								//コンストラクタ
	~CTitle();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitle *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	//CScene2D *m_pScene2D;					// シーン2Dへのポインタ
};
#endif
