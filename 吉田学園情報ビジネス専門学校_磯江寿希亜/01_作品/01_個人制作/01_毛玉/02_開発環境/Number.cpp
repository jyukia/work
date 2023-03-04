//=============================================================================
//
// Number.cpp
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
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
	//動的確保
	pNumber = new CNumber(nPriority);

	if (pNumber != nullptr)
	{

		pNumber->Init();

		//位置情報
		pNumber->SetPos(pos);
		//サイズ変更
		pNumber->SetSize(size);
		pNumber->SetCol(col);
		pNumber->AnimVtx(10, 0);
		pNumber->BindTexture(aFileName);

	}
	else
	{//処理を止める
		assert(false);
	}

	return pNumber;
}
