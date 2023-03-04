#include "Precompile.h"
#include "line.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"

CLine::CLine(int nPriority) :
	m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_size(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_rot(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_start(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_goal(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)),
	m_pVtxBuff(nullptr)
{
}

CLine::~CLine()
{
}

HRESULT CLine::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

void CLine::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CLine::Update()
{
}

void CLine::Draw()
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;		

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを使用する
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ライン描画
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ライトを有効	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Zテストの終了
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

CLine * CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 start, D3DXVECTOR3 goal, D3DXCOLOR col, int nPriority)
{
	CLine * pLine = new CLine;

	if (FAILED(pLine->Init()))
	{
		return nullptr;
	}

	// メンバ変数に値を設定
	pLine->m_pos = pos;			// 位置
	pLine->m_rot = rot;			// 角度
	pLine->m_start = start;		// 始点
	pLine->m_goal = goal;		// 終点
	pLine->m_col = col;			// 色

	// ラインセット処理
	pLine->SetLine();			

	// ポインタを返す
	return pLine;
}

void CLine::SetLine()
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_start.x, m_start.y, m_start.z);
	pVtx[1].pos = D3DXVECTOR3(m_goal.x, m_goal.y, m_goal.z);

	// 頂点カラー
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CLine::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CLine::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CLine::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

void CLine::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CLine::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
