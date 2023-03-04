#include "meshorbit.h"
#include"application.h"
#include "renderer.h"
#include "object3D.h"

CMeshOrbit::CMeshOrbit(int nPriority):m_pVtxMax(0), m_col(0.0f,0.0f,0.0f,0.0f)
{
}
CMeshOrbit::~CMeshOrbit()
{
}

HRESULT CMeshOrbit::Init()
{
	{//初期化
		m_pVtxMax = 100;	//頂点数最大数
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer((sizeof(VERTEX_3D) * m_pVtxMax),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = 0; Cnt < m_pVtxMax ; Cnt ++)
	{
		// 頂点情報を設定
		pVtx[Cnt].pos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//各頂点の法線の設定（※ベクトルの大きさは1にする必要がある）
		pVtx[Cnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[Cnt].col = D3DXCOLOR(m_col);

		//テクスチャの座標設定
		pVtx[Cnt].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CMeshOrbit::Uninit()
{
	//頂点バッファの解放・削除
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CMeshOrbit::Update()
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = m_pVtxMax -3; Cnt >= 0; Cnt--)
	{
		pVtx[Cnt+2].pos = pVtx[Cnt].pos;
	}
	D3DXVECTOR3 OfSetPos(0.0f,100.0f,0.0f);	//	縦座標の変換 サイズ変更可能
	D3DXVec3TransformCoord(&OfSetPos, &OfSetPos, m_pMtxParent);
	D3DXVECTOR3 Pos(0.0f,0.0f,0.0f);	//原点
	D3DXVec3TransformCoord(&Pos, &Pos, m_pMtxParent);

	pVtx[1].pos = OfSetPos;	//高さ変更
	pVtx[0].pos = Pos;//原点

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

void CMeshOrbit::Draw()
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//ライト設定falseにするとライトと食らわない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);				//行列初期化関数(第一引数の行列を単位行列に初期化)

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); //行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

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
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_pVtxMax - 2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

void CMeshOrbit::SetOfSetPos(D3DXVECTOR3 ofsetpos)
{
	OfSetPos = ofsetpos;
}

void CMeshOrbit::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CMeshOrbit::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CMeshOrbit::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

CMeshOrbit * CMeshOrbit::Create(D3DXCOLOR col)
{
	CMeshOrbit *pMesh = new CMeshOrbit(3);

	if (pMesh != nullptr)
	{
		pMesh->SetCol(col);
		pMesh->Init();
	}
	else
	{
		assert(false);
	}

	return pMesh;
}
