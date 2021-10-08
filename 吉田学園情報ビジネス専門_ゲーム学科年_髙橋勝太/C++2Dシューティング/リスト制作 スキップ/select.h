//=============================================================================
//
// メイン処理 [select.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// タイトルクラスの定義
//=============================================================================
//継承先描画クラス
class CSelect : public CScene
{
public:
	CSelect();								//コンストラクタ
	~CSelect();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSelect *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:

};
#endif
