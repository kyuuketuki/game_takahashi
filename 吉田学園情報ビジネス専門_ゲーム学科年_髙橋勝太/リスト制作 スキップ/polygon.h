//=============================================================================
//
// ���C������ [polygon.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
// �e�N���X�̒�`
//=============================================================================

//�p����`��N���X
class CPolygon : public CScene2D
{
public:
	CPolygon();								//�R���X�g���N�^
	virtual ~CPolygon();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType, int nTypeNumber);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//Create�֐�
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSizeX, float fSizeY, float fmove, float fRot, float fRotMove, int nMaxSize, int MinSize, int nType , int nTypeNumber);
	static void PlayerBullet(int nDamage);
	static void UninitBullet(void);

private:
	static bool	m_bUsePolygon;				//�G�̎�ނ��^�C�v�ŊǗ�

	D3DXVECTOR3 m_move;							//�ړ���
	D3DXCOLOR   m_col;
	int			m_nLife;						//���C�t
	int			m_nType;
	int			m_nTypeNumber;					//�^�C�v
	int			m_CirclePattern;
	int			m_nMaxSize;
	int			m_nMinSize;
	float		m_fmove;						//�ړ���
	float		m_fRot;							//��]�p�x
	float		m_fSizeX;						//X�̑傫��
	float		m_fSizeY;						//Y�̑傫��
	float		m_fRotMove;
	bool m_bUse;

	static int m_nDamage;
};

#endif