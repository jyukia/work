//=============================================================================
//
// timer.cpp
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************

#include "Timer.h"
#include"input.h"
#include "mode.h"
#include"Meshline.h"
#include"player.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include"Timer.h"
#include "application.h"
#include "Item.h"

CFade *m_pFadeTime;

//�R���X�g���N�^
CTimer::CTimer(int nPriority)
{
}
//�f�X�g���N�^
CTimer::~CTimer()
{
}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT CTimer::Init()
{
	returnflg = false;

	for (int numberCnt = 0; numberCnt <2; numberCnt++)
	{//
		pNumber[numberCnt] = CNumber::Create("NUMBER", D3DXVECTOR3(SCREEN_WIDTH - 90 + numberCnt *50.0f, SCREEN_HEIGHT - 90, 0.0f), D3DXVECTOR3(65.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
	}

	Setlife(60);

	return S_OK;
}
//-----------------------------------------
//�I��
//-----------------------------------------
void CTimer::Uninit()
{
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void CTimer::Update()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();

	//// �L�[�{�[�h�̏��擾
	//CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();

	//if (pInputKeyboard->Press(DIK_T))
	//{// ���Ɉړ�
	//}

	bool bflg =CItem::GetSizdownflg();	//�t���O���擾���Ԃ𑝂₷
	if (bflg)	
	{
			Addlife(5);
			CItem::SetSizdownflg(false);
	}

	bool flg = CApplication::Getinstnce()->GetpMode()->GetGoal()->GetGoalFlg();
	if (flg)		//�S�[���ƃv���C���[���G�ꂽ��
	{
		returnflg = true;
	}
	else			//�G�ꂢ�Ă��Ȃ��Ƃ�
	{
		bool flg = CApplication::Getinstnce()->GetpMode()->GetPlayer()->Getbredycheck();
		if (flg)
		{
			if (returnflg)
			{
				return;
			}
			TimeCnt++;
			//�P�b�o������
			if (TimeCnt >= 60)
			{
				TimeCnt = 0;
				//���鏈��
				Sublife(1);
			}
		}
	}
	CObject2D::SetPos(pos);
}
//-----------------------------------------
//�`��
//-----------------------------------------
void CTimer::Draw()
{
}
//���Z����
void CTimer::Addlife(int nGain)
{
	int aPosTexU[2];	//�e���̐������i�[

	m_Time += nGain;

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���ݒ�
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}
//���Z����
void CTimer::Sublife(int nDecrease)
{
	int aPosTexU[2];	//�e���̐������i�[

	m_Time -= nDecrease;


	if (m_Time <= 0)
	{//0�ȉ���������
		m_Time = 0;
		flg = false;

		CApplication::Getinstnce()->GetSound()->Stop(CSound::LABEL_GAME);

		if (m_pFadeTime->GetFade() == CFade::FADE_NONE)
		{
			// �J��
			CFade::SetFade(CApplication::MODE_RANKING);
		}

		//�ړ��o���Ȃ��悤�ɂ���
		CApplication::Getinstnce()->GetpMode()->GetPlayer()->Setbredycheck(flg);
	}

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���ݒ�
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}
//�X�R�A�ݒ菈��
void CTimer::Setlife(int nLife)
{
	int aPosTexU[2];	//�e���̐������i�[

	m_Time = nLife;

	aPosTexU[0] = m_Time % 100 / 10;
	aPosTexU[1] = m_Time % 10 / 1;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���ݒ�
		pNumber[nCount]->ScoreVtx
		(0.1f * aPosTexU[nCount],
			0.0f,
			0.1f * aPosTexU[nCount] + 0.1f,
			1.0f);
	}
}

CTimer * CTimer::Create(D3DXVECTOR3 pos, int nPriority)
{
	CTimer* pTime = nullptr;
	//���I�m��
	pTime = new CTimer(nPriority);

	if (pTime != nullptr)
	{
		pTime->Init();

		//�ʒu���
		pTime->SetPos(pos);

	}
	else
	{//�������~�߂�
		assert(false);
	}

	return pTime;
}
