//=============================================================================
//
// メイン処理 [player.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//マクロ定義
#define PLAYER_SIZE (50)

//=============================================================================
// プレイヤークラスの定義
//=============================================================================
//継承先描画クラス
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 2);								//コンストラクタ
	virtual ~CPlayer();										//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY);					//初期化処理
	void	Uninit(void);																	//終了処理
	void	Update(void);																	//更新処理
	void	Draw(void);																		//描画処理

	static CPlayer	*Create(D3DXVECTOR3 pos, int nLifefloat, float fSizeX, float fSizeY);	//生成処理
	static HRESULT	Load(void);																//テクスチャ読み込み
	static void		Unload(void);															//テクスチャ破棄

	static void BulletLevel(void);
	static void SetBulletLevel(int nData);

	static bool GetBumped(void);
	static void SetBumped(bool bBumped);

	static D3DXVECTOR3	GetPlayer(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[5];		//テクスチャポインター
	D3DXVECTOR3					m_pos;				//位置
	D3DXVECTOR3					m_move;				//移動量
	int							m_nType;			//タイプテクスチャ識別用
	int							m_nSpeed;			//移動量
	bool						m_nBulletLevelUP;	//弾のレベル
	bool						m_nBullet;			//弾のレベル用
	bool						m_nBullet2;			//弾のレベル用
	bool						m_nBullet3;			//弾のレベル用
};

#endif