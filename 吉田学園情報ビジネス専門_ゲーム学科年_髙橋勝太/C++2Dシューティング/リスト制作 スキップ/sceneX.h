//=============================================================================
//
// ���C������ [sceneX.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENEX_H_
#define _SCENEX_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"

//=============================================================================
// �|���S���N���X�̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
} VERTEX_3D;

//�p����`��N���X
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 5, int nType = 0);								//�R���X�g���N�^
	virtual ~CSceneX();					//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create();

private:
	LPD3DXMESH		m_pMesh;
	LPD3DXBUFFER	m_pBuffMat;
	DWORD			m_nNumMat;
	D3DXMATRIX		m_mtxWorld;
	int				m_nNumVtx;			//���_��
	D3DXVECTOR3		m_pos;				//�ʒu
	D3DXVECTOR3		m_rot;				//����
	float			m_fRot;

};

#endif