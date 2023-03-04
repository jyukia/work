//=============================================================================
//
// Score.cpp
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Number.h"
#include "score.h"
#include "application.h"
#include"input.h"
#include "Item.h"

int CScore::m_Score;

//�R���X�g���N�^
CScore::CScore(int nPriority)
{
}
//�f�X�g���N�^
CScore::~CScore()
{
}
//-----------------------------------------
//������
//-----------------------------------------
HRESULT CScore::Init()
{
	for (int numberCnt =0; numberCnt <8; numberCnt++)
	{
		pNumber[numberCnt] = CNumber::Create("NUMBER",D3DXVECTOR3(50.0f+numberCnt *45.0f,70.0f,0.0f), D3DXVECTOR3(35.0f, 40.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),3);
	}
	return S_OK;
}
//-----------------------------------------
//�I��
//-----------------------------------------
void CScore::Uninit()
{
}
//-----------------------------------------
//�X�V
//-----------------------------------------
void CScore::Update()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();

	// �L�[�{�[�h�̏��擾
	CInput *pInputKeyboard = CApplication::Getinstnce()->GetInput();

	//bool bScoreAdd = CApplication::Getinstnce()->GetItem()->GetScoreUpflg();

	//if (bScoreAdd)
	//{
	//	AddScore(100);
	//}
	

	CObject2D::SetPos(pos);

}
//-----------------------------------------
//�`��
//-----------------------------------------
void CScore::Draw()
{

}
//���Z����
void CScore::AddScore(int nGain)
{
	int aPosTexU[8];	//�e���̐������i�[

	m_Score += nGain;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

	for (int nCount = 0; nCount < 8; nCount++)
	{
		//�e�N�X�`���ݒ�
		pNumber[nCount]->ScoreVtx
		( 0.1f * aPosTexU[nCount] ,
							 0.0f ,
	0.1f * aPosTexU[nCount] + 0.1f,
							 1.0f);
	}
}
//���Z����
void CScore::SubScore(int nscore)
{
	int aPosTexU[8];	//�e���̐������i�[

	m_Remaining -= nscore;

	if (m_Remaining <= 0)
	{//0�ȉ���������
		m_Remaining = 0;
	}

	aPosTexU[0] = (m_Remaining % 10) / 1;
	aPosTexU[1] = (m_Remaining % 100) / 10;
	aPosTexU[2] = (m_Remaining % 1000) / 100;
	aPosTexU[3] = (m_Remaining % 10000) / 1000;
	aPosTexU[4] = (m_Remaining % 100000) / 10000;
	aPosTexU[5] = (m_Remaining % 1000000) / 100000;
	aPosTexU[6] = (m_Remaining % 10000000) / 1000000;
	aPosTexU[7] = (m_Remaining % 100000000) / 10000000;

	for (int nCount = 0; nCount < 8; nCount++)
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
void CScore::SetScore(int nScore)
{
	int aPosTexU[8];	//�e���̐������i�[

	m_Score = nScore;

	aPosTexU[0] = m_Score % 100000000 / 10000000;
	aPosTexU[1] = m_Score % 10000000 / 1000000;
	aPosTexU[2] = m_Score % 1000000 / 100000;
	aPosTexU[3] = m_Score % 100000 / 10000;
	aPosTexU[4] = m_Score % 10000 / 1000;
	aPosTexU[5] = m_Score % 1000 / 100;
	aPosTexU[6] = m_Score % 100 / 10;
	aPosTexU[7] = m_Score % 10 / 1;

}

CScore * CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore = nullptr;
	//���I�m��
	pScore = new CScore(3);

	if (pScore != nullptr)
	{
		pScore->Init();

		//�ʒu���
		pScore->SetPos(pos);

	}
	else
	{//�������~�߂�
		assert(false);
	}

	return pScore;
}
