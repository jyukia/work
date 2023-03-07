//**************************************************
//
// 制作 ( Right )
// Author  : 
//
//**************************************************
#include "right.h"

static LPDIRECT3DTEXTURE9 s_TextureRight[TYPERIGHT_MAX] = {};			//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_PvtxBuffRight = NULL;				//頂点バッファへのポインタ
static RIGHT s_Right[MAX_RIGHT];

static int Count;

void InitRight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み	敵テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/bowling.png",			
		&s_TextureRight[TYPERIGHT_BOWLING]);

	//テクスチャ読み込み	敵テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/dream.png",				
		&s_TextureRight[TYPERIGHT_DREAM]);

	//テクスチャ読み込み	敵テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/love.png",			
		&s_TextureRight[TYPERIGHT_LOVE]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_RIGHT,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&s_PvtxBuffRight,
		NULL);

	for (int Cnt = 0; Cnt < MAX_RIGHT; Cnt++)
	{//初期化
		s_Right[Cnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		s_Right[Cnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		s_Right[Cnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		Count = 0;

		bool bUse = false;					//使用してるかどうか	
	}

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_PvtxBuffRight->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = 0; Cnt < MAX_RIGHT; Cnt++, pVtx += 4)
	{

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//頂点をアンロックする
	s_PvtxBuffRight->Unlock();


}
void UninitRight(void)
{
	for (int count = 0; count < TYPERIGHT_MAX; count++)
	{
		if (s_TextureRight[count] != NULL)
		{
			s_TextureRight[count]->Release();
			s_TextureRight[count] = NULL;
		}
	}
	//頂点バッファ破棄
	if (s_PvtxBuffRight != NULL)
	{
		s_PvtxBuffRight->Release();
		s_PvtxBuffRight = NULL;
	}
}
void UpdateRight(void)
{
	Count++;

	if (Count > 100)
	{
		FalseSet();
	}
	if (Count > 150)
	{
		TrueSet();
	}
	if (Count > 200)
	{
		Count = 0;

	}

	
}
void DrawRight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_PvtxBuffRight, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_RIGHT; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_TextureRight[s_Right[nCnt].nType]);

		if (s_Right[nCnt].bUse)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}
void SetRight(D3DXVECTOR3 pos, D3DXCOLOR col, TYPERIGHT Type,int SIZ_X,int SIZ_Y)
{
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_PvtxBuffRight->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = 0; Cnt < MAX_RIGHT; Cnt++)
	{
		if (!s_Right[Cnt].bUse)
		{
			s_Right[Cnt].pos = pos;

			s_Right[Cnt].nType = Type;

			//頂点座標の設定
			pVtx[0].pos.x = s_Right[Cnt].pos.x - SIZ_X;
			pVtx[0].pos.y = s_Right[Cnt].pos.y - SIZ_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = s_Right[Cnt].pos.x + SIZ_X;
			pVtx[1].pos.y = s_Right[Cnt].pos.y - SIZ_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = s_Right[Cnt].pos.x - SIZ_X;
			pVtx[2].pos.y = s_Right[Cnt].pos.y + SIZ_Y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = s_Right[Cnt].pos.x + SIZ_X;
			pVtx[3].pos.y = s_Right[Cnt].pos.y + SIZ_Y;
			pVtx[3].pos.z = 0.0f;

			s_Right[Cnt].col = col;
			s_Right[Cnt].bUse = true;
			break;
		}
		pVtx += 4;	//頂点座標データのポインタを４つ分進める
	}
	//頂点をアンロックする
	s_PvtxBuffRight->Unlock();
}
void FalseSet(void)
{
	for (int Count = 0; Count < MAX_RIGHT; Count++)
	{
		if (s_Right[Count].nType >= TYPERIGHT_BOWLING)
		{
			s_Right[Count].bUse = false;
		}
		if (s_Right[Count].nType >= TYPERIGHT_DREAM)
		{
			s_Right[Count].bUse = false;
		}
		if (s_Right[Count].nType >= TYPERIGHT_LOVE)
		{
			s_Right[Count].bUse = false;
		}
	}
}
void TrueSet(void)
{
	SetRight(D3DXVECTOR3(270.0f, 475.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPERIGHT_BOWLING, 60, 60);
	SetRight(D3DXVECTOR3(770.0f, 400.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPERIGHT_DREAM, 50, 50);
	SetRight(D3DXVECTOR3(970.0f, 420.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPERIGHT_LOVE, 100, 70);
}