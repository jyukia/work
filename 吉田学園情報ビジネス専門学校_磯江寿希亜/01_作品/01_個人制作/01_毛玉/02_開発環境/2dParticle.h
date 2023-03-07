//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _PARTICLE_2d_H_
#define _PARTICLE_2d_H_

#include "object2D.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************


//*****************************************************************************
//�}�N����`
//*****************************************************************************

class CParticle2D : public CObject2D
{
private:
	float Particle_Size = 10.0f;
	//�ړ�����
	const float m_fmaxmove = 20.0f;
	//���C�t
	int m_nLife = 8;
	//�T�C�Y
	float size = Particle_Size;

public:
	//�R���X�g���N�^
	explicit CParticle2D(int nPriority);

	//�f�X�g���N�^
	~CParticle2D();

	//������
	HRESULT Init() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	static CParticle2D* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);

private:

};

#endif