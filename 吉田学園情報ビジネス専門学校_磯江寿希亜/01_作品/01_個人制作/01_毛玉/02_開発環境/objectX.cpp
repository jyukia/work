//=============================================================================
// インクルードファイル
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "objectX_group.h"
#include "texture.h"
#include "player.h"
#include"light.h"
#include"camera.h"
#include "Mapcamera.h"

D3DXVECTOR3 CObjectX::m_axis;    // 回転軸

CObjectX::MODEL_MATERIAL *CObjectX::m_material = nullptr;		// マテリアル情報

//=============================================================================
// コンストラクタ
//=============================================================================
CObjectX::CObjectX(int nPriority) :
	CObject(nPriority),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pParent(nullptr)
{
	//オブジェクトのタイプセット処理
	CObject::SetType(OBJTYPE_MODEL);

	pEffect = NULL;
	m_hmWVP = NULL;
	m_hmWIT = NULL;
	m_hvLightDir = NULL;
	m_hvCol = NULL;
	m_hvEyePos = NULL;
	m_hTechnique = NULL;
	m_hTexture = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CObjectX::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

		{
			D3DXCreateEffectFromFile(
				pDevice, "Effect.fx", NULL, NULL,
				0, NULL, &pEffect, nullptr);

			m_hTechnique = pEffect->GetTechniqueByName("Diffuse");				//エフェクト
			m_hTexture = pEffect->GetParameterByName(NULL, "Tex");				//テクスチャ
			m_hmWVP = pEffect->GetParameterByName(NULL, "mWVP");				//ローカル-射影変換行列
			m_hmWIT = pEffect->GetParameterByName(NULL, "mWIT");				//ローカル-ワールド変換行列
			m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");		//ライトの方向
			m_hvCol = pEffect->GetParameterByName(NULL, "vColor");				//頂点カラー
			m_hvEyePos = pEffect->GetParameterByName(NULL, "vEyePos");
			m_hBool = pEffect->GetParameterByName(NULL, "bTex");				// テクスチャの中身があるかないかをチェックする
	}
	{
		m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	// クォータニオン初期化
	{
		m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
		bQuaternion = false;
	}

	return S_OK;
}

//=============================================================================
// オブジェクトの終了
//=============================================================================
void CObjectX::Uninit()
{
	//インスタンスの解放処理
	Release();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObjectX::Update()
{
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObjectX::Draw()
{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxParent;		//計算用マトリックス
		D3DMATERIAL9 matDef;				//現在のマテリアル保存用
		D3DXMATERIAL *pMat;					//マテリアルデータへのポインタ

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//計算用マトリックス
		D3DXMATRIX mtxSiz;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxSiz);		//行列初期化関数(第一引数の行列を単位行列に初期化)

		D3DXMatrixScaling(&mtxSiz, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxSiz);

		if (bQuaternion)
		{
			// クォータニオンの使用した姿勢の設定
			D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);	// クオータニオンによる行列回転
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot); // 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		}
		else
		{
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
		}

		//位置を反映
		D3DXMatrixTranslation(&mtxTransPos, m_pos.x, m_pos.y, m_pos.z);		//(※行列移動関数(第1引数にx,y,z方向の移動行列を作成))
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransPos);

		if (m_pParent != nullptr)
		{
			mtxParent = *m_pParent->GetMtxWorld();

			// 行列掛け算関数
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
		}

	Projection();

	//CMapcamera* pMapCamera = CApplication::Getinstnce()->GetMapCamera();
	//if(pMapCamera)
	//{
	//	//ワールドマトリックスの設定（ワールド座標行列の設定）
	//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//	//現在のマテリアルを保持
	//	pDevice->GetMaterial(&matDef);
	//	//マテリアルデータへのポインタを取得
	//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	//	{
	//		//マテリアルの設定
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//		//モデルパーツの描画
	//		m_pMesh->DrawSubset(nCntMat);
	//	}
	//	//保持していたマテリアルを戻す
	//	pDevice->SetMaterial(&matDef);
	//}

	DrawMaterial();
}

void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// 行列掛け算関数

	// 行列掛け算関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::Getinstnce()->GetTexture();

	// マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	if (m_pBuffMat != nullptr)
	{// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetTexture("NULL"));

			// モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);

			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
	}

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//DrawMaterial();

}
//=============================================================================
// マテリアル描画
//=============================================================================
void CObjectX::DrawMaterial()
{
	if (pEffect != NULL)
	{
		CCamera* pCamera = CApplication::Getinstnce()->GetCamera();

		D3DMATRIX viewMatrix = pCamera->GetMtxView();
		D3DMATRIX projMatrix = pCamera->GetProjection();

		CLight* lightClass = CApplication::Getinstnce()->GetLight();
		D3DLIGHT9 light = lightClass->GetLight();

		D3DXVECTOR4 v, light_pos;

		D3DXMATRIX m;

		//-------------------------------------------------
		// シェーダの設定
		//-------------------------------------------------
		pEffect->SetTechnique(m_hTechnique);
		pEffect->Begin(NULL, 0);

		D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);

		// ローカル-射影変換行列
		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXMatrixTranspose(&m, &m);
		pEffect->SetMatrix(m_hmWIT, &m);

		// ローカル-射影変換行列
		m = m_mtxWorld * viewMatrix * projMatrix;
		pEffect->SetMatrix(m_hmWVP, &m);

		// ライトの方向
		light_pos = D3DXVECTOR4(light.Direction.x, light.Direction.y, light.Direction.z, 0);

		D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
		D3DXVec4Transform(&v, &-light_pos, &m);

		D3DXVec3Normalize((D3DXVECTOR3 *)&v, (D3DXVECTOR3 *)&v);

		//環境光の大きさ
		v.w = -0.8f;
		pEffect->SetVector(m_hvLightDir, &v);

		// 視点
		m = m_mtxWorld *viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);

		//環境光
		v = D3DXVECTOR4(1, 0, 0, 1);

		//マテリアルデータのポインタを取得する
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		D3DMATERIAL9 *pMtrl = &pMat->MatD3D;

		D3DXVec4Transform(&v, &v, &m);

		//視点をシェーダーに渡す
		pEffect->SetVector(m_hvEyePos, &v);

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{
			{
				// モデルの色の設定 
				D3DXVECTOR4 Diffuse;
				Diffuse = D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a);

				pEffect->SetVector(m_hvCol, &Diffuse);
			} 

			if (pTex0 != nullptr)
			{// テクスチャの適応
				pTex0 = m_pTexture[nCntMat];
				// テクスチャの設定
				pEffect->SetTexture(m_hTexture, pTex0);
				pEffect->SetBool(m_hBool, true);
			}
			else
			{
				pEffect->SetBool(m_hBool, false);
				pEffect->SetTexture(m_hTexture,0);
			}


			pEffect->BeginPass(0);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);

			pEffect->EndPass();

			pMtrl++;
		}

		pEffect->End();
	}
	else
	{
		assert(false);
	}
}


//=============================================================================
// 頂点最大小値の計算処理
//=============================================================================
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// 行列掛け算関数

	D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_MinVtx, &m_MinVtx, &mtxWorld);


	if (m_MaxVtx.x < m_MinVtx.x)
	{
		float change = m_MaxVtx.x;
		m_MaxVtx.x = m_MinVtx.x;
		m_MinVtx.x = change;
	}

	if (m_MaxVtx.y < m_MinVtx.y)
	{
		float change = m_MaxVtx.y;
		m_MaxVtx.y = m_MinVtx.y;
		m_MinVtx.y = change;
	}

	if (m_MaxVtx.z < m_MinVtx.z)
	{
		float change = m_MaxVtx.z;
		m_MaxVtx.z = m_MinVtx.z;
		m_MinVtx.z = change;
	}
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 生成処理
//=============================================================================
CObjectX * CObjectX::Create(const char *aFileName, D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObjectX *pObjectX = nullptr;

	//インスタンス生成
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//ポインタが存在したら実行
		pObjectX->Init();

		pObjectX->Setstring(aFileName);
		pObjectX->LoadModel(aFileName);
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObjectX->CalculationVtx();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObjectX;
}
//=============================================================================
// 生成処理
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObjectX *pObjectX = nullptr;

	//インスタンス生成
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//ポインタが存在したら実行
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObjectX;
}

CObjectX * CObjectX::Create(const char * aFileName, D3DXVECTOR3 rot, D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObjectX *pObjectX = nullptr;

	//インスタンス生成
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//ポインタが存在したら実行
		pObjectX->Init();

		pObjectX->Setstring(aFileName);
		pObjectX->LoadModel(aFileName);
		pObjectX->SetPos(pos);
		pObjectX->SetRot(rot);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObjectX->CalculationVtx();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObjectX;
}

//=============================================================================
// モデルの読み込み
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{

	CObjectXGroup *xGroup = CApplication::Getinstnce()->GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtx = xGroup->GetMaxVtx(aFileName);
	m_pMesh = xGroup->GetMesh(aFileName);
	m_MinVtx = xGroup->GetMinVtx(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
	m_pTexture = xGroup->GetTexture(aFileName);
}

//=============================================================================
// 平行投影処理
//=============================================================================
void CObjectX::Projection(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9 matDef;				//現在のマテリアル保存用
	D3DXMATERIAL *pMat;					//マテリアルデータへのポインタ

	//変数宣言
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(0.2f, -0.5f, 0.3f, 0.0f);

	if (m_pos.y < -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, -209.1f, 0.0f);
	}

	if (m_pos.y >= -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	}

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//ワールドマトリックスの設定（ワールド座標行列の設定）
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		Material = pMat[nCntMat].MatD3D;

		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetMaterial(&Material);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion)
{
	// 変数宣言
	bool bIsLanding = false;

	if (bQuaternion)
	{
		// モデルの左側当たり判定(クォータニオンVer)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MinVtx.x - (pSize->x / 2.0f);
		}
		// モデルの右側当たり判定(クォータニオンVer)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MaxVtx.x + (pSize->x / 2.0f);
		}
		// モデルの奥側当たり判定(クォータニオンVer)
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z) &&
			(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MaxVtx.z + (pSize->z / 2.0f);
		}
		// モデルの手前側当たり判定(クォータニオンVer)
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MinVtx.z - (pSize->z / 2.0f);
		}
	}

	else
	{
		// モデルの左側当たり判定
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
		}
		// モデルの右側当たり判定
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
		}
		// モデルの奥側当たり判定
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
			(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
		}
		// モデルの手前側当たり判定
		if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f) &&
			(pPos->y + pSize->y > m_pos.y) &&
			(pPos->y < m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
		}
	}

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 当たり判定 (上側)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove, bool bQuaternion)
{
	// 変数宣言
	bool bIsLanding = false;

	if (bQuaternion)
	{
		// モデルの上側当たり判定(クォータニオンVer)
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y <= m_pos.y + m_MaxVtx.y + (pSize->y / 2.0f)))
		{
			bIsLanding = true;
			if (pPos->y == pPosOld->y)
			{
				pMove->y = 0.0f;
			}
			pPos->y = m_pos.y + m_MaxVtx.y + (pSize->y / 2.0f);
		}
	}

	else
	{
		// モデルの上側当たり判定
		if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
			(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
			(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
			(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
			(pPos->y <= m_pos.y + m_MaxVtx.y))
		{
			bIsLanding = true;
			if (pPos->y == pPosOld->y)
			{
				pMove->y = 0.0f;
			}
			pPos->y = m_pos.y + m_MaxVtx.y;
		}
	}

	// 値を返す
	return bIsLanding;
}
//=============================================================================
//クオータニオン計算式
void CObjectX::QuaternionCalculation(float ModelDiameter/*モデルの直径*/, D3DXVECTOR3 *move, D3DXQUATERNION *FstQuaternion /*計算後*/)
{
	// クオータニオン
	D3DXQUATERNION quaternion;

	D3DXVECTOR3 inverseVec = -*move / (ModelDiameter/*(モデルの直径)*/ * 2);
	// move値を反対にする
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//大きさを１に	
	D3DXVec3Normalize(&inverseVec, &inverseVec);

	// 外積で回転軸を算出
	D3DXVec3Cross(&m_axis, &inverseVec, &vecY);
	D3DXVec3Normalize(&m_axis, &m_axis);

	float fLength = D3DXVec3Length(move);

	int Cnt = CPlayer::GetKeyCnt();

	float Length = fLength / Cnt;
	// クオータニオンの計算
	D3DXQuaternionRotationAxis(&quaternion, &m_axis, Length *0.3f);	// 回転軸と回転角度を指定

	*FstQuaternion *= quaternion;

	// クオータニオンのノーマライズ
	D3DXQuaternionNormalize(FstQuaternion, FstQuaternion);
}



//=============================================================================
// 頂点最大値設定処理
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// 頂点最小値設定処理
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
