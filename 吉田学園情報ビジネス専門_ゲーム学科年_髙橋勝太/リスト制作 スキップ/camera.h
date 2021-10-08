//=============================================================================
//
// ���C������ [camera.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "manager.h"

//=============================================================================
// �e�N���X�̒�`
//=============================================================================

//�p����`��N���X
class CCamera
{
public:
	CCamera();								//�R���X�g���N�^
	virtual ~CCamera();						//�f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCamera(void);

private:
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���݂̎��_
	D3DXVECTOR3 m_posR;			// ���݂̒����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// �J�����̊p�x
	//D3DVIEWPORT9 viewport;		//�r���[�|�[�g
};

#endif