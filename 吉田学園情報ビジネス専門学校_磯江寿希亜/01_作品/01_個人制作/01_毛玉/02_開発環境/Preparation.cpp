//=============================================================================
//
// Cpreparation.cpp
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Preparation.h"
#include"DebugProc.h"
#include "player.h"
#include "mode.h"
#include "sound.h"

//�R���X�g���N�^
Cpreparation::Cpreparation(int nPriority):ChangeCount(0)
{

}
//�f�X�g���N�^
Cpreparation::~Cpreparation()
{

}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT Cpreparation::Init()
{
	{//������
		ChangeCount = 0;

	}
	CObject2D::Init();

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_REDY_SOUND);

	return S_OK;
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void Cpreparation::Update()
{
	ChangeCount++;	//�e�N�X�`���ύX�J�E���g

	D3DXVECTOR3 pos = CObject2D::GetPos();
	D3DXVECTOR3 size = CObject2D::GetSize();
	D3DXVECTOR3 rot = CObject2D::GetRot();
	D3DXCOLOR col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);


	if (pos.x <= SCREEN_WIDTH_HALF)	//��ʔ����܂Ői�ݎ~�܂�����
	{
		count++;
		if (count >= 60)
		{
			BindTexture("GO");
		}

		pos.x = SCREEN_WIDTH_HALF;
		rot.z = sinf(ChangeCount * -0.1f);

		if (ChangeCount >= 60)
		{
			rot.z = 0.0f;
		}
		if (ChangeCount >= 150)
		{
			CApplication::Getinstnce()->GetpMode()->GetPlayer()->Setbredycheck(true);
		}
		if (ChangeCount == 160)
		{
			//SetCol(col);
			Cpreparation::Uninit();
		}
	}
	else	//��ʔ����܂Ői�݂����Ă��Ȃ��Ƃ�
	{
		pos.x -= 10.0f;
	}

	CObject2D::SetRot(rot);
	CObject2D::SetPos(pos);
	CObject2D::Update();
}

Cpreparation * Cpreparation::Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriority)
{
	Cpreparation* pPreparation = nullptr;
	//���I�m��
	pPreparation = new Cpreparation(nPriority);

	if (pPreparation != nullptr)
	{
		pPreparation->Init();

		//�ʒu���
		pPreparation->SetPos(pos);
		pPreparation->SetSize(size);
		pPreparation->SetRot(rot);
		pPreparation->SetCol(D3DXCOLOR(1.f,1.f,1.f,1.f));
		pPreparation->BindTexture(aFileName);

	}
	else
	{//�������~�߂�
		assert(false);
	}

	return pPreparation;
}

