//=============================================================================
//
// ���C������ [bg.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �w�i�N���X�̒�`
//=============================================================================
//�p����`��N���X
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);				//�R���X�g���N�^
	~CBg();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	static HRESULT Load(void);
	static void Unload(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[3];			// �p�ӂ���e�N�X�`���̐�
	CScene2D *m_apScene2D[3];							// �V�[��2D�ւ̃|�C���^
	D3DXVECTOR3 m_pos;									// �ʒu���
	float m_nCntAnime;									// �e�N�X�`�������炷
};

#endif