//=============================================================================
//
// Number.cpp
// Author : ��]����
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************

#include "Number.h"

CNumber::CNumber(int nPriority)
{
}

CNumber::~CNumber()
{
}

HRESULT CNumber::Init()
{
	CObject2D::Init();

	return S_OK;
}
CNumber * CNumber::Create(const char *aFileName,D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nPriority)
{
	CNumber* pNumber = nullptr;
	//���I�m��
	pNumber = new CNumber(nPriority);

	if (pNumber != nullptr)
	{

		pNumber->Init();

		//�ʒu���
		pNumber->SetPos(pos);
		//�T�C�Y�ύX
		pNumber->SetSize(size);
		pNumber->SetCol(col);
		pNumber->AnimVtx(10, 0);
		pNumber->BindTexture(aFileName);

	}
	else
	{//�������~�߂�
		assert(false);
	}

	return pNumber;
}
