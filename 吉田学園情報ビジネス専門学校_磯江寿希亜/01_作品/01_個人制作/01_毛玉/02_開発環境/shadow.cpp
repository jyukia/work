//=============================================================================
// インクルードファイル
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "shadow.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow(int nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(void)
{
	CObject3D::Init();

	//テクスチャの読み込み
	LoadTexture("Data\\TEXTURE\\shadow000.jpg");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CShadow::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CShadow::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//減算合成を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 生成処理
//=============================================================================
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, int nPriority)
{
	//ポインタ宣言
	CShadow *pShadow = nullptr;

	pShadow = new CShadow(nPriority);

	if (pShadow != nullptr)
	{
		pShadow->Init();
		pShadow->SetPos(pos);
		pShadow->SetSize(size);
	}

	return pShadow;
}