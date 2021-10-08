//=============================================================================
//
// ���C������ [renderer.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RENDERE_H_
#define _RENDERE_H_

#include "main.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CRenderer
{
public:
	CRenderer();								//�R���X�g���N�^
	~CRenderer();								//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);		
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	void DrawFPS();

	LPDIRECT3D9					m_pD3D = NULL;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_pD3DDevice = NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)

	//FPS�̏��
	LPD3DXFONT					m_pFont = NULL;				// �t�H���g�ւ̃|�C���^
};

#endif
