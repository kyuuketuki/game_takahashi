//=============================================================================
//
// メイン処理 [light.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"
#include "manager.h"

#define MAX_LIGHT (3)

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CLight
{
public:
	CLight();								//コンストラクタ
	virtual ~CLight();						//デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DLIGHT9 m_light[3];		//ライト情報
};

#endif