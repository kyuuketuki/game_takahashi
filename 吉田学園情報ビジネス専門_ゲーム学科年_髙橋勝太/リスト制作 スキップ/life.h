//=============================================================================
//
// ���C������ [bg.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �w�i�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CLife : public CScene2D
{
public:
	CLife(int nPriority = 5);								//�R���X�g���N�^
	~CLife();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLife *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	static HRESULT Load(void);
	static void Unload(void);

	static void Recovery(int nLife);

private:
	static LPDIRECT3DTEXTURE9 m_apTextureLife[1];		// �p�ӂ���e�N�X�`���̐�
	CScene2D *m_apScene2D[1];							// �V�[��2D�ւ̃|�C���^
	D3DXVECTOR3 m_pos;									// �ʒu���
	float m_nCntAnime;									// �e�N�X�`�������炷
	int m_nCount;
};

#endif