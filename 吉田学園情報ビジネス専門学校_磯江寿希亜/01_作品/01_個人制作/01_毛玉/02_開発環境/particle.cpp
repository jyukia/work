//=============================================================================
//
// Particle.cpp
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Particle.h"
#include "application.h"
#include"game.h"
#include"player.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************


//*****************************************************************************
//�}�N����`
//*****************************************************************************


//-----------------------------------------
//�R���X�g���N�^
//-----------------------------------------
CParticle::CParticle(int list) :CObject3D(list)
{
}
//-----------------------------------------
//�f�X�g���N�^
//-----------------------------------------
CParticle::~CParticle()
{
}
HRESULT CParticle::Init()
{
	CObject3D::Init();

	return S_OK;
}
void CParticle::Update()
{
	//����
	m_nLife--;

	m_nLife = ((rand() % 5));

	size--;
	size -= 0.05f;

	if (size <= 0)
	{
		size = 0;
	}
	if (m_nLife <= 0.0f)
	{
		Uninit();
		return;
	}

	//pos���
	D3DXVECTOR3 ParticlePos = GetPos();

	D3DXVECTOR3 ParticleMove = GetMove();
	ParticlePos += ParticleMove;

	//�ړ�����
	ParticleMove.x = cosf((float)(rand() % 360) / 10) * ((float)(rand() % 1) + 0);
	ParticleMove.y = sinf((float)(rand() % 360) / 80) * ((float)(rand() % 100) + 20);


	SetMove(D3DXVECTOR3(ParticleMove));
	SetPos(D3DXVECTOR3(ParticlePos));
}
void CParticle::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// ������
//------------------------------------
void CParticle::Uninit()
{
	CObject3D::Uninit();
}
CParticle * CParticle::Create(const char *aFileName,D3DXVECTOR3 pos, D3DXVECTOR3 size,int nPriority)
{
	CParticle * pObject = nullptr;
	pObject = new CParticle(nPriority);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->LoadTexture(aFileName);//�e�N�X�`���I��
		pObject->SetSize(size);//�T�C�Y�ݒ�
		pObject->SetPos(pos);//���W�ݒ�
		pObject->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�F�ݒ�

		 //������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		//pObject->SetAnimation(5, 4, 4, 0, true);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}
	return pObject;
}

void CParticle::move()
{
}
