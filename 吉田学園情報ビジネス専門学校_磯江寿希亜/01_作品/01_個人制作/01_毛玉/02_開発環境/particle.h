//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "renderer.h"
#include "object3D.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************


//*****************************************************************************
//�}�N����`
//*****************************************************************************

class CParticle : public CObject3D
{
private:
	float Particle_Size = 10.0f;
	//�ړ�����
	const float m_fmaxmove = 20.0f;
	//���C�t
	int m_nLife = 15;
	//�T�C�Y
	float size = Particle_Size;

public:
	//�R���X�g���N�^
	CParticle(const int list);

	//�f�X�g���N�^
	~CParticle() override;

	//������
	HRESULT Init() override;

	void Uninit() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	static CParticle* Create(const char *aFileName,D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);

private:
	void move();
	D3DXVECTOR3 m_Move;

};

#endif