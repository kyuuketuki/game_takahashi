//=============================================================================
//
// メイン処理 [polygon.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CPolygon : public CScene2D
{
public:
	CPolygon();								//コンストラクタ
	virtual ~CPolygon();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Create関数
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType , int nTypeNumber);
	static void PlayerBullet(int nDamage);
	static void UninitBullet(void);

private:
	static bool	m_bUsePolygon;				//敵の種類をタイプで管理

	D3DXVECTOR3 m_move;							//移動量
	D3DXCOLOR   m_col;
	int			m_nLife;						//ライフ
	int			m_nType;
	int			m_nTypeNumber;					//タイプ
	int			m_CirclePattern;
	int			m_nMaxSize;
	int			m_nMinSize;
	float		m_fmove;						//移動量
	float		m_fRot;							//回転角度
	float		m_fSizeX;						//Xの大きさ
	float		m_fSizeY;						//Yの大きさ
	float		m_fRotMove;
	bool m_bUse;

	static int m_nDamage;
};

#endif