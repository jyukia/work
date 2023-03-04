//=============================================================================
// インクルードファイル
//=============================================================================
#include "light.h"
#include "application.h"
#include "renderer.h"

D3DLIGHT9 CLight::m_aLight[MAX_LIGHT];

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLight::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir1;		//ライトの方向ベクトル
	D3DXVECTOR3 vecDir2;		//ライトの方向ベクトル
	D3DXVECTOR3 vecDir3;		//ライトの方向ベクトル
	D3DXVECTOR3 vecDir4;		//ライトの方向ベクトル
	D3DXVECTOR3 vecDir5;		//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&m_aLight[0], sizeof(m_aLight));		//←構造体変数をゼロクリアできる便利関数(memsetと同じ)

	//ライトの種類を設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;		//平行光源
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;		//平行光源
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;		//平行光源
	m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;		//平行光源
	m_aLight[4].Type = D3DLIGHT_DIRECTIONAL;		//平行光源

	//ライトの拡散光を設定
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//ライトの色
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//ライトの色
	m_aLight[2].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);		//ライトの色
	m_aLight[3].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);		//ライトの色
	m_aLight[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//ライトの色

	//ライトの方向を設定
	vecDir1 = D3DXVECTOR3(-1.0f, 0.5f, -0.5f);
	vecDir2 = D3DXVECTOR3(-0.3f, 0.8f, 0.4f);
	vecDir3 = D3DXVECTOR3(0.6f, -0.4f, -0.2f);
	vecDir4 = D3DXVECTOR3(-0.8f, 0.4f, 0.2f);
	vecDir5 = D3DXVECTOR3(0.0f, 0.4f, 0.4f);

	//正規化する（大きさ1のベクトルにする）
	D3DXVec3Normalize(&vecDir1, &vecDir1);		//←ベクトルを大きさ1のする便利関数
	D3DXVec3Normalize(&vecDir2, &vecDir2);		//←ベクトルを大きさ1のする便利関数
	D3DXVec3Normalize(&vecDir3, &vecDir3);		//←ベクトルを大きさ1のする便利関数
	D3DXVec3Normalize(&vecDir4, &vecDir4);		//←ベクトルを大きさ1のする便利関数
	D3DXVec3Normalize(&vecDir5, &vecDir5);		//←ベクトルを大きさ1のする便利関数

	m_aLight[0].Direction = vecDir1;
	m_aLight[1].Direction = vecDir2;
	m_aLight[2].Direction = vecDir3;
	m_aLight[3].Direction = vecDir4;
	m_aLight[4].Direction = vecDir5;

	//ライトを設定する
	pDevice->SetLight(0, &m_aLight[0]);			//0番目のライトを設定・有効にする
	pDevice->SetLight(1, &m_aLight[1]);
	pDevice->SetLight(2, &m_aLight[2]);
	pDevice->SetLight(3, &m_aLight[3]);
	pDevice->SetLight(4, &m_aLight[4]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->LightEnable(3, TRUE);
	pDevice->LightEnable(4, TRUE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CLight::Update(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CLight *CLight::Create()
{
	//ポインタ宣言
	CLight *pLight = nullptr;

	//インスタンス生成
	pLight = new CLight;

	if (pLight != nullptr)
	{//ポインタが存在したら実行
		pLight->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pLight;
}