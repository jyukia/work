//=============================================================================
// インクルードファイル
//=============================================================================
#include "object2D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CObject2D::CObject2D(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_nTime(0),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_fSquareSize(10.0f),
	m_bRotate(false),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2D::~CObject2D()
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
HRESULT CObject2D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer((sizeof(VERTEX_2D) * 4),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//対角線の長さ算出
	m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y)));

	//角度の算出
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 頂点情報を設定
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インスタンスの解放処理
	Release();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObject2D::Update()
{
	//位置更新
	m_pos += m_move;

	//頂点座標更新処理
	VtxUpdate();

	if (m_bRotate)
	{
		m_nTime++;

		D3DXVECTOR3 addPos[4];
		D3DXMATRIX mtx;    // 計算用マトリックス

		VERTEX_2D*pVtx;        //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// マトリックスの生成
		D3DXMatrixIdentity(&mtx);

		// ヨー、ピッチ、ロールを指定してマトリックスを作成
		D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, ((D3DX_PI * 1.5f) / 50.0f) * m_nTime);

		// 頂点座標
		for (int i = 0; i < 4; ++i)
		{
			D3DXVec3TransformCoord(&addPos[i], &sVtx[i], &mtx);
			pVtx[i].pos = m_pos + addPos[i] * (m_fSquareSize);
		}

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObject2D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CObject2D::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//対角線の長さ算出
		m_fLength = sqrtf(((m_size.x * m_size.x) + (m_size.y * m_size.y))) / 2;

		//角度の算出
		m_fAngle = atan2f(m_size.x, m_size.y);

		//頂点座標の更新
		pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.z = 0.0f;

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
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CObject2D::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::Getinstnce()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

//=============================================================================
// テクスチャ座標更新処理
//=============================================================================
void CObject2D::SetUV(float x_1, float x_2, float y_1, float y_2)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

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
// 座標更新処理
//=============================================================================
void CObject2D::SetPosUV(float x_1, float x_2, float y_1, float y_2, float x_width1, float x_width2)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].pos = D3DXVECTOR3(x_1, y_1,0.f);
	pVtx[1].pos = D3DXVECTOR3(x_2, y_1,0.f);
	pVtx[2].pos = D3DXVECTOR3(x_width1, y_2,0.f);
	pVtx[3].pos = D3DXVECTOR3(x_width2, y_2,0.f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//---------------------------------------------------------------------------
//スコア使用
//---------------------------------------------------------------------------
void CObject2D::ScoreVtx(float fstposX, float fstposY, float secdposX, float secdposY)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(fstposX, fstposY);
	pVtx[1].tex = D3DXVECTOR2(secdposX, fstposY);
	pVtx[2].tex = D3DXVECTOR2(fstposX, secdposY);
	pVtx[3].tex = D3DXVECTOR2(secdposX, secdposY);

	//頂点をアンロックする
	m_pVtxBuff->Unlock();
}

//---------------------------------------------------------------------------
// アニメーション頂点設定
//---------------------------------------------------------------------------
void CObject2D::AnimVtx(int nummax, int PtternAnim)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//表示座標を更新
	pVtx[0].tex = D3DXVECTOR2((1.0f / nummax)*PtternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nummax)*(PtternAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nummax)*PtternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nummax)*(PtternAnim + 1), 1.0f);

	//頂点をアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 生成処理
//=============================================================================
CObject2D * CObject2D::Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
	//ポインタ宣言
	CObject2D *pObject2D = nullptr;

	//インスタンス生成
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{//ポインタが存在したら実行
		pObject2D->BindTexture(aFileName);
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
		pObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObject2D->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObject2D;
}
