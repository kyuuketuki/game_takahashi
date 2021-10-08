//=============================================================================
//
// メイン処理 [menu.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// タイトルクラスの定義
//=============================================================================
//継承先描画クラス
class CMenu : public CScene
{
public:
	CMenu();								//コンストラクタ
	~CMenu();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMenu *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	
};
#endif
