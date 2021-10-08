//=============================================================================
//
// メイン処理 [scene.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//#include "enemy.h"

//=============================================================================
// 描画クラスの定義
//=============================================================================
class CScene
{
public:

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,				// プレイヤー
		OBJTYPE_ENEMY,				// 敵
		OBJTYPE_ENEMY2,				// 中ボス
		OBJTYPE_ENEMY3,				// ボス
		OBJTYPE_BULET_PLAYER,		// プレイヤーから発射された弾
		OBJTYPE_BULET_ENEMY,		// 敵から発射された弾
		OBJTYPE_BULET_ENEMY2,		// 敵から発射された弾
		OBJTYPE_BULET_ENEMY3,		// 敵から発射された弾
		OBJECT_MAX
	}OBJTYPE;

	typedef enum
	{
		ENEMY_01 = 0,
		ENEMY_02,
		ENEMY_03,
		ENEMY_04,
		ENEMY_05,
		ENEMY_06,
		ENEMY_07,
		ENEMY_99,
		ENEMY_BOSS_01,
		ENEMY_BOSS_02,
		ENEMY_BOSS_03,
		ENEMY_MAX
	}ENEMY_TYPE;

	typedef enum
	{
		BULLET_NORMAL = 0,
		BULLET_AIMING,				// 弾のホーミング
		BULLET_MAX
	}BULLET;

	CScene(int nPriority = 1, int nType = 0);				//コンストラクタ
	virtual ~CScene();										//デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	static CScene *GetScene(int nIdx, int nPriority);
	
	//ライフ管理
	void SetLife(int nLife);
	void Damage(int nDamage);
	int GetLife(void);

	//タイプ管理
	OBJTYPE GetObjType(void) { return m_objType; }
	void SetObjType(OBJTYPE objType) { m_objType = objType; }

	//サイズ
	float GetSizeX(void) { return m_fSizeX; }
	void SetSizeXScene(float nSize) { m_fSizeX = nSize; }
	float GetSizeY(void) { return m_fSizeY; }
	void SetSizeYScene(float nSize) { m_fSizeY = nSize; }

	D3DXCOLOR GetCollar(void) { return m_col; }
	void SetCollar(D3DXCOLOR col) { m_col = col; }

	//位置管理
	virtual D3DXVECTOR3 GetPosition(void);

protected:
	void Release(void);

private:
	//static CScene	*m_apScene[MAX_POLYGON][6][3];			//シーンへのポインタ
	static int		m_NumAll;
	int				m_nID;									//格納先の番号
	OBJTYPE			m_objType;								//オブジェクトの種類
	float			m_fSizeX;
	float			m_fSizeY;
	int				m_nPriority;							// 優先順位
	int				m_nType;
	int				m_nLife;
	D3DXCOLOR		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	static CScene *m_pTop[6][3];
	static CScene *m_pCur[6][3];
	CScene *m_pPrev;
	CScene *m_pNext;
	bool m_bDeath  = false;		//死亡フラグ
};

#endif
