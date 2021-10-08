//=============================================================================
//
// メイン処理 [enemy.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "player.h"
#include "scene2D.h"

//マクロ定義
#define ENEMY_SIZE (70)

//=============================================================================
// 敵クラスの定義
//=============================================================================
//継承先描画クラス
class CEnemy : public CScene2D
{
public:
	CEnemy(int nPriority = 1);				//コンストラクタ
	virtual ~CEnemy();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fmove, D3DXVECTOR3 objective, int nLife, float fSizeX, float fSizeY, int nTime, int nType, int nMoveType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Collision(void);

	//敵の生成
	static CEnemy *Create(D3DXVECTOR3 pos, float fmove, D3DXVECTOR3 objective, int nLife, float fSizeX, float fSizeY, int nTime, int nType, int nMoveType);
	static void NextObjective(D3DXVECTOR3 pos, float fMove, int nType);
	static void NextObjectiveAttack(D3DXVECTOR3 pos, float fMove, int nType);

	static void NextAttack(int NextAttack);
	static void NextAttack2(int NextAttack);
	static void NextAttack3(int NextAttack);

	static void NextMove(D3DXVECTOR3 pos, float fMove, int nType);
	static void MoveClear(void);

	//テクスチャ関連
	static HRESULT Load(void);
	static void Unload(void);

private:
	//静的メンバ変数
	static CPlayer				*m_pPlayer;				//プレイヤーへのポインタ	ホーミング時に使用
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMY_MAX];	//テクスチャへのポインタ
	static int					m_nLife;				//ライフ

	static D3DXVECTOR3			m_objective2;			//ゴール地点
	static D3DXVECTOR3			m_objective3;			//ゴール地点 攻撃時
	static D3DXVECTOR3			m_objective4;			//ゴール地点 攻撃時

	static int					m_nType2;				//敵の種類をタイプで管理
	static int					m_nType3;				//敵の種類をタイプで管理
	static int					m_nType4;				//敵の種類をタイプで管理
	static int					m_nAttackType;			//敵の種類をタイプで管理
	static int					m_nNextAttack;
	static int					m_nNextAttack2;
	static int					m_nNextAttack3;

	static float				m_fMove2;				//行動を管理する時間
	static float				m_fMove3;				//行動を管理する時間
	static float				m_fMove4;				//行動を管理する時間

	static bool					m_bUse;					//
	static bool					m_bUse2;				//
	static bool					m_bUse3;				//
	static bool					m_bAttack;				//
														
	//メンバ変数
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR3					m_objective;			//ゴール地点
	D3DXCOLOR					m_col;
	int							m_nAttack;				//
	int							m_nTime;				//行動を管理する時間
	int							m_nType;				//敵の種類をタイプで管理
	int							m_nMoveType;			//動きを統一させるタイプ
	float						m_fMove;				//移動スピード
	float						m_fSizeX;				//
	float						m_fSizeY;				//
	float m_fMoveEnemy;

	int							m_nAttackCnt;			//攻撃するタイミング
	int							m_nAttackCnt2;			//攻撃するタイミング
	int							m_nAttackCnt3;			//攻撃するタイミング

	float						m_fAngleEnemyBullet = 0.0f;
	float						m_fAngleEnemyBullet2 = 0.0f;
	float						m_fAngleEnemyBullet3 = 0.0f;

	bool						m_bAttackPattern;		//
	bool						m_bMovEnemy;
	bool						m_bAngleEnemy = false;

	//敵の無敵時間
	int							m_nHitTime;
	bool						m_bInvincibility = false;
};

#endif