//=============================================================================
//
// Cpreparation.cpp
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Preparation.h"
#include"DebugProc.h"
#include "player.h"
#include "mode.h"
#include "sound.h"

//コンストラクタ
Cpreparation::Cpreparation(int nPriority):ChangeCount(0)
{

}
//デストラクタ
Cpreparation::~Cpreparation()
{

}
//-----------------------------------------
//初期化
//-----------------------------------------
HRESULT Cpreparation::Init()
{
	{//初期化
		ChangeCount = 0;

	}
	CObject2D::Init();

	CApplication::Getinstnce()->GetSound()->Play(CSound::LABEL_REDY_SOUND);

	return S_OK;
}
//-----------------------------------------
//更新
//-----------------------------------------
void Cpreparation::Update()
{
	ChangeCount++;	//テクスチャ変更カウント

	D3DXVECTOR3 pos = CObject2D::GetPos();
	D3DXVECTOR3 size = CObject2D::GetSize();
	D3DXVECTOR3 rot = CObject2D::GetRot();
	D3DXCOLOR col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);


	if (pos.x <= SCREEN_WIDTH_HALF)	//画面半分まで進み止まった際
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
	else	//画面半分まで進みきっていないとき
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
	//動的確保
	pPreparation = new Cpreparation(nPriority);

	if (pPreparation != nullptr)
	{
		pPreparation->Init();

		//位置情報
		pPreparation->SetPos(pos);
		pPreparation->SetSize(size);
		pPreparation->SetRot(rot);
		pPreparation->SetCol(D3DXCOLOR(1.f,1.f,1.f,1.f));
		pPreparation->BindTexture(aFileName);

	}
	else
	{//処理を止める
		assert(false);
	}

	return pPreparation;
}

