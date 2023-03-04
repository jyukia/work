//=============================================================================
// インクルードファイル
//=============================================================================
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include"camera.h"
#include"light.h"


//=============================================================================
// コンストラクタ
//=============================================================================
CObject3D::CObject3D(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3D::~CObject3D()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	////バッファが消去されてたら普通に通る(NULLチェック)
	assert(m_pVtxBuff == nullptr);

}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CObject3D::Init()
{
	{
		m_bBillboard = false;							// ビルボードかどうか
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D) * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	//LoadTexture("Data\\TEXTURE\\yuka000.jpg");

	//対角線の長さ算出
	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y)));

	//角度の算出
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[1].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[2].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[3].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//各頂点の法線の設定（※ベクトルの大きさは1にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// オブジェクトの終了
//=============================================================================
void CObject3D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//インスタンスの解放処理
	Release();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObject3D::Update()
{
	//頂点座標更新処理
	VtxUpdate();
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObject3D::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);			//行列初期化関数(第一引数の行列を単位行列に初期化)

	//カメラの逆行列を設定
	if (m_bBillboard)
	{
		// ライトを無効
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスの設定
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// カメラ逆行列を設定
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	else
	{
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)
	}

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);					//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

}
//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CObject3D::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_3D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (m_bBillboard)	//ビルボード時
		{
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_size.x,  m_size.y,  0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_size.x,  -m_size.y,  0.0f);
		}
		else
		{	
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
			pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
			pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
			pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);
		}
		//頂点カラーの更新
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;


		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// 座標設定関数
//=============================================================================
void CObject3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObject3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObject3D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObject3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//テクスチャのポインタ
}

//=============================================================================
// テクスチャ座標更新処理
//=============================================================================
void CObject3D::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(x_1, y_1);
	pVtx[1].tex = D3DXVECTOR2(x_2, y_1);
	pVtx[2].tex = D3DXVECTOR2(x_1, y_2);
	pVtx[3].tex = D3DXVECTOR2(x_2, y_2);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 生成処理
//=============================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObject3D *pObject3D = nullptr;

	//インスタンス生成
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{//ポインタが存在したら実行
		pObject3D->SetPos(pos);
		pObject3D->SetSize(D3DXVECTOR3(150.0f, 0.0f, 150.0f));
		pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject3D->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObject3D;
}

CObject3D * CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nPriority)
{
	//ポインタ宣言
	CObject3D *pObject3D = nullptr;

	//インスタンス生成
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{//ポインタが存在したら実行
		pObject3D->SetPos(pos);
		pObject3D->SetRot(rot);
		pObject3D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject3D->Init();
		pObject3D->SetSize(size);

	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObject3D;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void CObject3D::LoadTexture(const char * aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}
