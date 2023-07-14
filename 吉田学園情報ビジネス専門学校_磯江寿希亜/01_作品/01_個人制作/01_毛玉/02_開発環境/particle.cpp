//=============================================================================
//
// Particle.cpp
// Author : 磯江寿希亜
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Particle.h"
#include "application.h"
#include"game.h"
#include"player.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************


//*****************************************************************************
//マクロ定義
//*****************************************************************************


//-----------------------------------------
//コンストラクタ
//-----------------------------------------
CParticle::CParticle(int list) :CObject3D(list)
{
}
//-----------------------------------------
//デストラクタ
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
		Uninit();
		return;
	}

	//pos代入
	D3DXVECTOR3 ParticlePos = GetPos();

	D3DXVECTOR3 ParticleMove = GetMove();
	ParticlePos += ParticleMove;

	//移動方向
	ParticleMove.x = cosf((float)(rand() % 360) / 10) * ((float)(rand() % 1) + 0);
	ParticleMove.y = sinf((float)(rand() % 360) / 80) * ((float)(rand() % 100) + 20);


	SetMove(D3DXVECTOR3(ParticleMove));
	SetPos(D3DXVECTOR3(ParticlePos));
}
void CParticle::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// 初期化
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
		pObject->LoadTexture(aFileName);//テクスチャ選択
		pObject->SetSize(size);//サイズ設定
		pObject->SetPos(pos);//座標設定
		pObject->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//色設定

		 //↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		//pObject->SetAnimation(5, 4, 4, 0, true);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}
	return pObject;
}

void CParticle::move()
{
}
