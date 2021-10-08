//=============================================================================
//
// ���C������ [player.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//�}�N����`
#define PLAYER_SIZE (50)

//=============================================================================
// �v���C���[�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 2);								//�R���X�g���N�^
	virtual ~CPlayer();										//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static CPlayer	*Create(D3DXVECTOR3 pos, int nLifefloat, float fSizeX, float fSizeY);
	static HRESULT	Load(void);
	static void		Unload(void);

	static void BulletLevel(void);
	static void SetBulletLevel(int nData);

	static bool GetBumped(void);
	static void SetBumped(bool bBumped);

	static D3DXVECTOR3	GetPlayer(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[5];
	D3DXVECTOR3					m_pos;
	D3DXVECTOR3					m_move;
	int							m_nType;
	int							m_nSpeed;
	bool						m_nBulletLevelUP;
	bool						m_nBullet;
	bool						m_nBullet2;
	bool						m_nBullet3;
};

#endif