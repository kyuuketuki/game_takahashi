//=============================================================================
//
// メイン処理 [bullet.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define BULLET_SIZE (10)

//=============================================================================
// 弾クラスの定義
//=============================================================================

//継承先描画クラス
class CBullet : public CScene2D
{
public:
	CBullet(int nPriority = 4);				//コンストラクタ
	virtual ~CBullet();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSpeed, int nLife, int nDamage, float fSizeX, float fSizeY, int nType, int nTypeMove);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, int nDamage, float fSizeX, float fSizeY, int nType);
	static CBullet *Create2(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSpeed, int nLife, int nDamage, float fSizeX, float fSizeY, int nType, int nTypeMove);
	static HRESULT Load(void);
	static void Unload(void);

	//Create関数
	static void InitAngleBullet(D3DXVECTOR3 pos, float fSpeed, D3DXCOLOR col, int nLife, int nDamage, float fSizeX, float fSizeY, float fAngle, int nType);
	static void InitAngleBullet2(D3DXVECTOR3 pos, float fSpeed, D3DXCOLOR col, int nLife, int nDamage, float fSizeX, float fSizeY, float fAngle, int nType, int nTypeMove);
	static void InitAimingBullet(D3DXVECTOR3 posBullet, D3DXCOLOR col, float speed, D3DXVECTOR3 posPlayer);
	static void InitAimingBullet2(D3DXVECTOR3 posBullet, D3DXCOLOR col, float speed, D3DXVECTOR3 posPlayer, int nTypeMove);
	static void InitDestinations(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSpeed, int nLife, int nDamage, float fSizeX, float fSizeY, int nType);
	static void InitDestinations2(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSpeed, int nLife, int nDamage, float fSizeX, float fSizeY, int nType, int nTypeMove);

	//
	static void NextMove(int nTypeMove,int nAction, D3DXVECTOR3 fSpeed);
	static void NextAimingBullet(int nTypeMove, int nAction, D3DXVECTOR3 posPlayer, float fSpeed);

	static void NextMove2(int nTypeMove, int nAction, D3DXVECTOR3 fSpeed);
	static void NextAimingBullet2(int nTypeMove, int nAction, D3DXVECTOR3 posPlayer, float fSpeed);

private:
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_oldpos;						//移動量
	D3DXVECTOR3 m_createpos;					//移動量
	D3DXCOLOR	m_col;
	int			m_nLife;						//ライフ
	int			m_nDamage;
	int			m_nType;
	int			m_TypeMove;
	float		m_fRot;
	float		m_fSizeX;
	float		m_fSizeY;
	float		m_fSpeedDestinations;
	bool		m_bUseAming = false;
	bool		m_bCreatepos = false;
	bool		m_bChangeSpeed = false;

	static LPDIRECT3DTEXTURE9	m_pTexture;							//テクスチャのポインタ
	static D3DXVECTOR3			m_nextpos;							//移動量
	static D3DXVECTOR3			m_nextmove;							//移動量
	static int					m_TypeAction;
};

#endif