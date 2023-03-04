#include "Meshline.h"
#include"application.h"
#include "renderer.h"
#include "object3D.h"
#include "player.h"
#include "game.h"
#include "game1.h"
#include "mode.h"
#include "movelife.h"
#include "input.h"
#include "camera.h"
#include "Item.h"
#include "ranking.h"

#include"DebugProc.h"

bool CMeshLine::bIsLanding = false;

CMeshLine::CMeshLine(int nPriority) :m_pVtxMax(0), m_col(0.0f, 0.0f, 0.0f, 0.0f), m_Vtxcount(0), bUseflg(false)
{

}

CMeshLine::~CMeshLine()
{
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
void CMeshLine::LoadTexture(const char * aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}

//初期化
HRESULT CMeshLine::Init()
{
	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		m_pVtxMax = MaxLineTitle;	//頂点数最大数
	}
	else
	{//初期化
		m_pVtxMax = MaxLine;	//頂点数最大数
	}

	if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME)
	{
		m_pos = D3DXVECTOR3(110.0f, 610.0f, -600.0f);
	}
	else if(CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
	{
		m_pos = D3DXVECTOR3(2300.0f, 20.0f, -2900.0f);
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
	{
		m_pos = D3DXVECTOR3(1850.0f, 20.0f, -600.0f);
	}
	else if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_RANKING)
	{
		m_pos = D3DXVECTOR3(1100.0f, 610.0f, -2600.0f);
	}

	LoadTexture("Data/TEXTURE/kedama.png");

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

	int X = 0;
	for (int Cnt = 0; Cnt < m_pVtxMax; Cnt++)
	{
		// 頂点情報を設定
		//pVtx[Cnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[Cnt].pos = m_pos;

		//各頂点の法線の設定（※ベクトルの大きさは1にする必要がある）
		pVtx[Cnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[Cnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[Cnt].tex = D3DXVECTOR2(0.0f, 1.0f);


		float Y = (float)Cnt / 2;
		pVtx[Cnt].tex = D3DXVECTOR2((float)X, Y);
		X++;
		if (X >= 2)	//テクスチャ
		{
			X = 0;
		}

	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CMeshLine::Uninit()
{
	//頂点バッファの解放・削除
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CMeshLine::Update()
{

	D3DXVECTOR3 axis = CObjectX::GetAxis();

	//プレイヤー情報
	if (CApplication::Getinstnce()->GetpMode()->GetPlayer() != nullptr)
	{
		D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
		D3DXVECTOR3 pPlayerPosOld = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPosOld();

		//頂点情報へのポインタ
		VERTEX_3D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (pPlayerPosOld != pPlayerPos && !(axis.x == 0 && axis.y == 0 && axis.z == 0))	//動いてるとき実行
		{
			pVtx[m_Vtxcount + 2].pos = pPlayerPos + axis * 5.0f;			//高さ変更
			pVtx[m_Vtxcount + 1].pos = pPlayerPos - axis * 5.0f;			//原点
			m_Vtxcount += 2;
		}

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

		//移動を止める計算
		if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_TITLE)
		{
			if (m_Vtxcount >= 900)	//最大移動量に達した場合	プレイヤーの移動を制限
			{
				CMode::GetPlayer()->SetbMoveFlg(false);
			}
		}
		else
		{
			int a = 0;
			if (m_Vtxcount >= 5000)	//最大移動量に達した場合	プレイヤーの移動を制限
			{
				CMode::GetPlayer()->SetbMoveFlg(false);
			}
			else
			{
				CMode::GetPlayer()->SetbMoveFlg(true);
			}
		}


#ifdef _DEBUG
		CDebugProc::Print("プレイヤーの進行方向       (axis)       | X : %.2f | Y : %.2f | Z : %.2f |\n", axis.x, axis.y, axis.z);

		CDebugProc::Print("プレイヤーの座標       (pPlayerPos)       | X : %.2f | Y : %.2f | Z : %.2f |\n", pPlayerPos.x, pPlayerPos.y, pPlayerPos.z);

		CDebugProc::Print("m_Vtxcount       (m_Vtxcount)       %d\n", m_Vtxcount);

#endif // _DEBUG
	}
}

void CMeshLine::Draw()
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f); //行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);		//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_Vtxcount - 2/*m_pVtxMax - 2*/);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

}
void CMeshLine::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}

void CMeshLine::SetOfSetPos(D3DXVECTOR3 ofsetpos)
{
	OfSetPos = ofsetpos;
}

void CMeshLine::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

}

void CMeshLine::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

void CMeshLine::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

CMeshLine * CMeshLine::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 distancepos)
{
	CMeshLine *pMeshLine = new CMeshLine(2);

	if (pMeshLine != nullptr)
	{
		pMeshLine->Init();
		pMeshLine->SetOfSetPos(distancepos);
		pMeshLine->SetCol(col);
		pMeshLine->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pMeshLine;
}
//毛糸が障害物に触れた際接触した際きれる処理
bool CMeshLine::Collision(D3DXVECTOR3 * PlayerPos, D3DXVECTOR3 * PlayerSize)
{
	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;
	//WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idxのpos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB

	bool bIsLanding = false;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return bIsLanding;
}
//=============================================================================
// 当たり判定 プレイヤーが戻った際毛糸の回収を行う
//=============================================================================
bool CMeshLine::CollisionReturn(D3DXVECTOR3 * PlayerPos)
{
	const int LineDiameter = 2;

	const int nPolygon = 100;
	D3DXVECTOR3 VecA[nPolygon * 3];				//VecA
	D3DXVECTOR3 VecB[nPolygon * 3];				//VecB
	float Calculation2D[nPolygon * 3];			//2次元外積の計算結果
	const int vecCount = 3;
	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;
	bIsLanding = false;

	//スケール対応したサイズを計算		当たり判定使用
	D3DXVECTOR3 Scale = CMode::GetPlayer()->GetScale();
	D3DXVECTOR3 Size = CMode::GetPlayer()->GetSize();
	{
		//スケールとサイズ
		Size.x = Scale.x * Size.x;
		Size.y = Scale.y * Size.y;
		Size.z = Scale.z * Size.z;
	}

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int count = 0; count < nPolygon; count++)
	{
		//ベクトルの取得 VecA
		VecA[count * 3] = pVtx[3 + count].pos - pVtx[2 + count].pos;
		VecA[count * 3 + 1] = pVtx[4 + count].pos - pVtx[3 + count].pos;
		VecA[count * 3 + 2] = pVtx[2 + count].pos - pVtx[4 + count].pos;

		//プレイヤー頂点を測る
		VecB[count * 3] = *PlayerPos - pVtx[2 + count].pos;
		VecB[count * 3 + 1] = *PlayerPos - pVtx[3 + count].pos;
		VecB[count * 3 + 2] = *PlayerPos - pVtx[4 + count].pos;

		Calculation2D[count * 3] = Vec2Cross(&VecA[count * 3], &VecB[count * 3]);
		Calculation2D[count * 3 + 1] = Vec2Cross(&VecA[count * 3 + 1], &VecB[count * 3 + 1]);
		Calculation2D[count * 3 + 2] = Vec2Cross(&VecA[count * 3 + 2], &VecB[count * 3 + 2]);

		//プレイヤーの位置が全部-か+
		if ((Calculation2D[count * 3] > 0 && Calculation2D[count * 3 + 1] > 0 && Calculation2D[count * 3 + 2] > 0) || (Calculation2D[count * 3] < 0 && Calculation2D[count * 3 + 1] < 0 && Calculation2D[count * 3 + 2] < 0))
		{//当たった時
			for (int Cnt = 0; Cnt < m_pVtxMax - 3; Cnt++)
			{
				CMode::GetPlayer()->SetScaleType(CPlayer::TypeScaleUp);

				//配列を入れ替える事で消している
				pVtx[Cnt] = pVtx[Cnt + 2];
			}

			m_Vtxcount -= 2;

			//false生成無し
			bUseflg = false;
			bIsLanding = true;
		}
		else
		{//当たっていないとき
			int a = 1;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return bIsLanding;
}

//中心を求める
D3DXVECTOR3 CMeshLine::GetCenterVtx()
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//真ん中を求めるため作成
	m_returnpos = pVtx[m_Vtxcount].pos + (pVtx[m_Vtxcount - 1].pos - pVtx[m_Vtxcount].pos) / 2;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

return  m_returnpos; } 

//=========================================
// 2Dベクトルの外積
// Author: Yuda Kaito
//=========================================
float CMeshLine::Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//=========================================
// 2Dベクトルの内積
// Author: hamada ryuuga
//=========================================
float CMeshLine::Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}
