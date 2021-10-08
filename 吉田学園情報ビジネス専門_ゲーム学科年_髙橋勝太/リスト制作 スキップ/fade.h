//=============================================================================
//
//�t�F�[�h����[fade.h]
// Author; takahashi
//
//=============================================================================

#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"

//=============================================================================
//�t�F�[�h�N���X�̒�`
//=============================================================================
class CFade : public CScene
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;
	CFade(int nPriority = 5, int nType = 1);				//�R���X�g���N�^
	~CFade();//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fHight, float fWidth);  //����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	D3DXVECTOR3 GetAllPosition(void) { return D3DXVECTOR3(); }
	static void SetFade(FADE fade, CManager::MODE modeNext, D3DXCOLOR col);
	static CFade *Create(CManager::MODE modenext);
	FADE GetFade(void) { return m_fade; }

private:
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_���
	static FADE m_fade;
	static CManager::MODE m_modenext;
	static D3DXCOLOR m_col;
	D3DXVECTOR3 m_pos;
};
#endif
