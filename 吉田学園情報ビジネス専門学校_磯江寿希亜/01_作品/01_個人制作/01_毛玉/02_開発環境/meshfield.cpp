//=============================================================================
// インクルードファイル
//=============================================================================
#include "meshfield.h"
#include "object3D.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "game.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshfield::CMeshfield(int nPriority) :
	CObject(nPriority),
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_fLength(0.0f),
	m_fAngle(0.0f),
	m_fRotMove(5.0f),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshfield::~CMeshfield()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshfield::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	//LoadTexture("Data\\TEXTURE\\wood.png");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点座標へのポインタ
	VERTEX_3D * pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			//m_RandHeight = (float)(rand() % 30 + 1);
			m_RandHeight = sinf(nCntX * 0.5f) * 120;

			//頂点座標の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].pos = D3DXVECTOR3(-POLYGON_WIDTH + (POLYGON_WIDTH * nCntX), 0.0f, POLYGON_DEPTH - (POLYGON_DEPTH * nCntZ));

			//各頂点の法線の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCntX + (nCntZ * (MESHFIELD_X_BLOCK + 1))].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (int nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHFIELD_X_BLOCK + 1; nCntX++)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1);
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) + nCntX + nCntZ * (MESHFIELD_X_BLOCK + 1) - (MESHFIELD_X_BLOCK + 1);

			pIdx += 2;
		}

		//縮退ポリゴン
		if (nCntZ != MESHFIELD_Z_BLOCK)
		{
			pIdx[0] = (MESHFIELD_X_BLOCK + 1) * nCntZ + MESHFIELD_X_BLOCK;
			pIdx[1] = (MESHFIELD_X_BLOCK + 1) * (nCntZ + 2);

			pIdx += 2;
		}
	}

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	D3DXVECTOR3 IdxPosNor[3];				//Idxのpos
	D3DXVECTOR3 Calculation3DNor[2];		//3次元外積の計算結果
	D3DXVECTOR3 VecAnswer;					//外積の計算結果
	D3DXVECTOR3 SaveVtxNor[MESHFIELD_VERTEX_NUM];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM - 2; nCnt++)
	{
		//Idxのpos
		IdxPosNor[0] = pVtx[pIdx[nCnt]].pos;
		IdxPosNor[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPosNor[2] = pVtx[pIdx[nCnt + 2]].pos;

		//縮退ポリゴンの場合実行
		if (pIdx[nCnt] == pIdx[nCnt + 1] || pIdx[nCnt + 1] == pIdx[nCnt + 2] || pIdx[nCnt + 2] == pIdx[nCnt])
		{
			continue;
		}

		//3次元外積の計算
		Calculation3DNor[0] = IdxPosNor[1] - IdxPosNor[0];
		Calculation3DNor[1] = IdxPosNor[2] - IdxPosNor[0];
		D3DXVec3Cross(&VecAnswer, &Calculation3DNor[0], &Calculation3DNor[1]);

		if (nCnt % 2 == 0)
		{
			VecAnswer *= -1;
		}

		//正規化
		D3DXVec3Normalize(&VecAnswer, &VecAnswer);

		//保存用配列に法線ベクトルを保存
		SaveVtxNor[pIdx[nCnt]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 1]] += VecAnswer;
		SaveVtxNor[pIdx[nCnt + 2]] += VecAnswer;

		//正規化
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt]], &SaveVtxNor[pIdx[nCnt]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 1]], &SaveVtxNor[pIdx[nCnt + 1]]);
		D3DXVec3Normalize(&SaveVtxNor[pIdx[nCnt + 2]], &SaveVtxNor[pIdx[nCnt + 2]]);

		pVtx[pIdx[nCnt]].nor = SaveVtxNor[pIdx[nCnt]];
		pVtx[pIdx[nCnt + 1]].nor = SaveVtxNor[pIdx[nCnt + 1]];
		pVtx[pIdx[nCnt + 2]].nor = SaveVtxNor[pIdx[nCnt + 2]];
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshfield::Uninit()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファの解放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//インスタンスの解放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshfield::Update()
{
	//m_fRotMove += 0.1f;

	//if (m_fRotMove >= D3DX_PI)
	//{// 移動方向の正規化
	//	m_fRotMove -= D3DX_PI * 2;
	//}
	//else if (m_fRotMove <= -D3DX_PI)
	//{// 移動方向の正規化
	//	m_fRotMove += D3DX_PI * 2;
	//}

	////高さ更新
	//m_pos.y += sinf(m_fRotMove) * 4.0f;

	////座標設定
	//SetPos(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshfield::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_VERTEX_NUM, 0, MESHFIELD_PRIMITIVE_NUM);

	//ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//テクスチャの設定	(テクスチャがモデルにかぶらないようにする)
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点座標更新処理
//=============================================================================
void CMeshfield::VtxUpdate()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点情報へのポインタ
		VERTEX_3D*pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
		pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
		pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);

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
// 座標設定処理
//=============================================================================
void CMeshfield::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズ設定処理
//=============================================================================
void CMeshfield::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動量設定処理
//=============================================================================
void CMeshfield::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// カラー設定処理
//=============================================================================
void CMeshfield::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定処理
//=============================================================================
void CMeshfield::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 派生のテクスチャポインタを親のテクスチャポインタに代入する処理
//=============================================================================
void CMeshfield::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//テクスチャのポインタ
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
void CMeshfield::LoadTexture(const char * aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		aFileName,
		&m_pTexture);
}

//=============================================================================
// テクスチャ座標設定処理
//=============================================================================
void CMeshfield::SetUV(float x_1, float x_2, float y_1, float y_2)
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
CMeshfield * CMeshfield::Create(const D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CMeshfield *pMeshfield = nullptr;

	//インスタンス生成
	pMeshfield = new CMeshfield(nPriority);

	if (pMeshfield != nullptr)
	{//ポインタが存在したら実行
		pMeshfield->SetPos(pos);
		pMeshfield->SetSize(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		pMeshfield->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pMeshfield->Init();
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pMeshfield;
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CMeshfield::Collision(D3DXVECTOR3 *PlayerPos, D3DXVECTOR3 *PlayerSize, bool bQuaternion)
{
	//頂点情報へのポインタ
	VERTEX_3D * pVtx = nullptr;
	WORD * pIdx;
	D3DXVECTOR3 IdxPos[3];				//Idxのpos
	D3DXVECTOR3 VecA[3];				//VecA
	D3DXVECTOR3 VecB[3];				//VecB
	D3DXVECTOR3 Calculation3D[2];		//3次元外積の計算結果
	float Calculation2D[3];				//2次元外積の計算結果
	D3DXVECTOR3 Answer;					//外積の計算結果
	bool bIsLanding = false;

	CPlayer * pPlayer = CGame::GetPlayer();

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHFIELD_PRIMITIVE_NUM; nCnt++)
	{
		//Idxのpos
		IdxPos[0] = pVtx[pIdx[nCnt]].pos;
		IdxPos[1] = pVtx[pIdx[nCnt + 1]].pos;
		IdxPos[2] = pVtx[pIdx[nCnt + 2]].pos;

		//VecA
		VecA[0] = IdxPos[1] - IdxPos[0];
		VecA[1] = IdxPos[2] - IdxPos[1];
		VecA[2] = IdxPos[0] - IdxPos[2];

		//VecB
		VecB[0] = *PlayerPos - (IdxPos[0] + m_pos);
		VecB[1] = *PlayerPos - (IdxPos[1] + m_pos);
		VecB[2] = *PlayerPos - (IdxPos[2] + m_pos);

		//2次元外積の計算結果
		Calculation2D[0] = VecA[0].x * VecB[0].z - VecB[0].x * VecA[0].z;
		Calculation2D[1] = VecA[1].x * VecB[1].z - VecB[1].x * VecA[1].z;
		Calculation2D[2] = VecA[2].x * VecB[2].z - VecB[2].x * VecA[2].z;

		//プレイヤーの位置が全部-か+
		if ((Calculation2D[0] >= 0 && Calculation2D[1] >= 0 && Calculation2D[2] >= 0) || (Calculation2D[0] <= 0 && Calculation2D[1] <= 0 && Calculation2D[2] <= 0))
		{
			//3次元外積の計算
			Calculation3D[0] = IdxPos[1] - IdxPos[0];
			Calculation3D[1] = IdxPos[2] - IdxPos[0];
			D3DXVec3Cross(&Answer, &Calculation3D[0], &Calculation3D[1]);

			//正規化
			D3DXVec3Normalize(&Answer, &Answer);

			//if (PlayerPos->y <= posLineVec[0].y - (Normal.x*(PlayerPos->x - posLineVec[0].x) + Normal.z*(PlayerPos->z - posLineVec[0].z)) / Normal.y)
			//{
			//	//CGame::GetStage()->GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetStage()->GetPlayer()->GetMove().x, 0.0f, CGame::GetStage()->GetPlayer()->GetMove().z));
			//	PlayerPos->y = (posLineVec[0].y - (Normal.x*(PlayerPos->x - posLineVec[0].x) + Normal.z*(PlayerPos->z - posLineVec[0].z)) / Normal.y) - 0.001f;
			//}

			if (bQuaternion)
			{
				//内積の計算
				PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y + PlayerSize->y / 2.0f;

				//内積の計算結果保存
				m_AnswerKeep = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y + PlayerSize->y / 2.0f;
			}
			else
			{
				//内積の計算
				PlayerPos->y = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;

				//内積の計算結果保存
				m_AnswerKeep = (IdxPos[0].y + m_pos.y) - ((PlayerPos->x - (IdxPos[0].x + m_pos.x)) * Answer.x + (PlayerPos->z - (IdxPos[0].z + m_pos.z)) * Answer.z) / Answer.y;
			}

			bIsLanding = true;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return bIsLanding;
}
