//=============================================================================
// インクルードファイル
//=============================================================================
#include "billboard.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "texture.h"
#include"mode.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_PatternAnimX(1),
	m_PatternAnimY(1),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f)),
	m_blend(BLEND_NONE)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CBillboard::Init()
{
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
void CBillboard::Uninit()
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
void CBillboard::Update()
{
	m_pos += m_move;

	//頂点座標更新処理
	VtxUpdate();

	if (m_bAnimation)
	{// テクスチャアニメーションをする場合
		m_CntTime++;

		if (m_CntTime >= m_Timer)
		{
			m_AnimationSpdCnt++;
			if (m_AnimationSpdCnt >= m_AnimationSpeed)
			{
				m_AnimationSpdCnt = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{//アニメーション
					m_PatternAnimX = 0;
					m_PatternAnimY++;
					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;
						if (!m_bLoop)
						{
							Uninit();
						}
						return;
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetUV(U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V);
			}
		}
	}
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CBillboard::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxTrans, mtxRot, mtxView;

	switch (m_blend)
	{
	case BLEND_ADDITIVE:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	case BLEND_SUBSTRUCT:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		break;
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);		//行列初期化関数(第一引数の行列を単位行列に初期化)

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	if (m_bIsRotate)
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カメラから見て近い部分を上書き
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zバッファの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

}

//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CBillboard::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_3D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

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
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VtxUpdate();
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CBillboard::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::Getinstnce()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

//=============================================================================
// テクスチャ座標更新処理
//=============================================================================
void CBillboard::SetUV(float x_1, float x_2, float y_1, float y_2)
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
// Animationの枚数設定関数
//=============================================================================
void CBillboard::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 1;
	m_PatternAnimY = 1;
	m_AnimationSpeed = Speed;
	m_Timer = Drawtimer;
	m_bAnimation = true;
	m_bLoop = loop;

	//表示座標を更新
	SetUV(1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY));
}

//=============================================================================
// アニメーションを指定のタイミングで止める処理
//=============================================================================
void CBillboard::SetStopAnim(const int X, const int Y)
{
	m_bAnimation = false;

	m_PatternAnimX = X;
	m_PatternAnimY = Y;

	float U = 1.0f / (m_DivisionX);
	float V = 1.0f / (m_DivisionY);

	SetUV(U * (m_PatternAnimX)
		, U *(m_PatternAnimX)+U
		, V * (m_PatternAnimY)
		, V * (m_PatternAnimY)+V);
}

//=============================================================================
// テクスチャの反転処理
//=============================================================================
void CBillboard::SetFlip(EFlip flip)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	switch (flip)
	{
	case FLIP_VERTICAL:
		pVtx[0].tex.y = -pVtx[0].tex.y;
		pVtx[1].tex.y = -pVtx[1].tex.y;
		pVtx[2].tex.y = -pVtx[2].tex.y;
		pVtx[3].tex.y = -pVtx[3].tex.y;
		break;

	case FLIP_HORIZON:
		pVtx[0].tex.x = -pVtx[0].tex.x;
		pVtx[1].tex.x = -pVtx[1].tex.x;
		pVtx[2].tex.x = -pVtx[2].tex.x;
		pVtx[3].tex.x = -pVtx[3].tex.x;
		break;

	default:
		pVtx[0].tex = -pVtx[0].tex;
		pVtx[1].tex = -pVtx[1].tex;
		pVtx[2].tex = -pVtx[2].tex;
		pVtx[3].tex = -pVtx[3].tex;
		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 生成処理
//=============================================================================
CBillboard * CBillboard::Create(std::string inPath,D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CBillboard *pBillboard = nullptr;

	//インスタンス生成
	pBillboard = new CBillboard(nPriority);

	if (pBillboard != nullptr)
	{//ポインタが存在したら実行
		pBillboard->BindTexture(inPath);
		pBillboard->SetPos(pos);
		pBillboard->SetSize(D3DXVECTOR3(55.0f, 55.0f, 0.0f));
		pBillboard->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pBillboard;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void CBillboard::LoadTexture(const char * aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}
