//=============================================================================
//
// ���C������ [title.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �^�C�g���N���X�̒�`
//=============================================================================
//�p����`��N���X
class CTitle : public CScene
{
public:
	CTitle();								//�R���X�g���N�^
	~CTitle();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitle *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	//CScene2D *m_pScene2D;					// �V�[��2D�ւ̃|�C���^
};
#endif
