//=============================================================================
//
// Particle.cpp
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"2dParticle.h"
#include"application.h"
#include "renderer.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************


//*****************************************************************************
//マクロ定義
//*****************************************************************************


//-----------------------------------------
//コンストラクタ
//-----------------------------------------
CParticle2D::CParticle2D(int nPriority)
{
}
//-----------------------------------------
//デストラクタ
//-----------------------------------------
CParticle2D::~CParticle2D()
{
}
HRESULT CParticle2D::Init()
{
	CObject2D::Init();

	return S_OK;
}
void CParticle2D::Update()
{
	//寿命
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
		CObject2D::Uninit();
		return;
	}

	//pos代入
	D3DXVECTOR3 ParticlePos = GetPos();

	D3DXVECTOR3 ParticleMove = GetMove();
	ParticlePos += ParticleMove;

	//移動方向
	ParticleMove.x = cosf((float)(rand() % 360) / 20) * ((float)(rand() % 10) + 10);
	ParticleMove.y = sinf((float)(rand() % 360) / -80) * ((float)(rand() % 10) + 5);


	SetMove(D3DXVECTOR3(ParticleMove));
	SetPos(D3DXVECTOR3(ParticlePos));

}
void CParticle2D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//設定をもとに戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
CParticle2D * CParticle2D::Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
	CParticle2D* pParticle = nullptr;

	//動的確保
	pParticle = new CParticle2D(nPriority);

	//NULLチェック
	if (pParticle != nullptr)
	{
		pParticle->BindTexture(aFileName);
		pParticle->SetPos(pos);
		pParticle->SetSize(size);

		pParticle->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
		pParticle->Init();
	}
	else
	{//処理を止める
		assert(false);
	}

	return pParticle;
}

