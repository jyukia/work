//================================
//
// comboの設定
// Author:Teruto Sato
//
//================================

#include "combo.h"
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"

#define	NUR_COMBO	(1)

//グローバル関数
static LPDIRECT3DTEXTURE9 g_pTextureCombo[NUR_COMBO] = {}; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCombo = NULL; //頂点バッファの設定
static Combo g_aCombo[MAX_COMBO];
static float coleff;//エフェクトの色
static float coleff2;//エフェクトの色

 //==================
 //たまの初期化設定
 //==================
void InitCombo(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntCombo;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/RESULT/score.png",
		&g_pTextureCombo[0]);

	coleff = 1.0f;
	coleff2 = 0.0f;

	//初期化
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		g_aCombo[nCntCombo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポス
		g_aCombo[nCntCombo].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ムーブ
		g_aCombo[nCntCombo].nLife = 0;//ライフ
		g_aCombo[nCntCombo].bUse = false;//使ってるか
		g_aCombo[nCntCombo].moveset = false;
		g_aCombo[nCntCombo].moveOn = false;
		g_aCombo[nCntCombo].Trigger = 0;   //種類
		g_aCombo[nCntCombo].nType = 0;//タイプ
		g_aCombo[nCntCombo].fSiz = 0.0f; //サイズ
		g_aCombo[nCntCombo].Move2 = 0;

	}

	//頂点バッファ
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_COMBO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&g_pVtxBuffCombo,
		NULL);

	VERTEX_2D*pVtx; //頂点へのポインタ
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);


		//RHWの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	g_pVtxBuffCombo->Unlock();

}

//==================
//終了処理
//==================
void UninitCombo(void)
{
	int nCntCombo;
	for (nCntCombo = 0; nCntCombo < NUR_COMBO; nCntCombo++)
	{
		//テクスチャの破棄
		if (g_pTextureCombo[nCntCombo] != NULL)
		{
			g_pTextureCombo[nCntCombo]->Release();
			g_pTextureCombo[nCntCombo] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffCombo != NULL)
	{
		g_pVtxBuffCombo->Release();
		g_pVtxBuffCombo = NULL;
	}

}

//==================
//更新処理
//==================
void UpdateCombo(void)
{
	int nCntCombo;
	

	VERTEX_2D*pVtx; //頂点へのポインタ
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{


		g_aCombo[nCntCombo].nLife--;
		//位置更新
		g_aCombo[nCntCombo].pos += g_aCombo[nCntCombo].move;
		g_aCombo[nCntCombo].moveset = true;

		g_aCombo[nCntCombo].col.a -= 1.0f / g_aCombo[nCntCombo].nMaxLife;

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = g_aCombo[nCntCombo].col;
		pVtx[1].col = g_aCombo[nCntCombo].col;
		pVtx[2].col = g_aCombo[nCntCombo].col;
		pVtx[3].col = g_aCombo[nCntCombo].col;

		if (g_aCombo[nCntCombo].nLife == 0)
		{

			g_aCombo[nCntCombo].bUse = false;

		}
		pVtx += 4;//頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	g_pVtxBuffCombo->Unlock();
}

//==================
//弾の描画処理
//==================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntCombo;

	pDevice = GetDevice();		//代入

								//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCombo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCombo[g_aCombo[nCntCombo].nType]);

		if (g_aCombo[nCntCombo].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntCombo * 4,
				2);
		}
	}
}

//==================
//弾の設定
//==================
void SetCombo(D3DXVECTOR3 pos, int nLife, int nType, float fSiz,int number)
{
	int nCntCombo;
	float X = 0.1f;
	VERTEX_2D*pVtx; //頂点へのポインタ

					//ロック
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		if (g_aCombo[nCntCombo].bUse == false)
		{
			//弾が使用されてない場合
			g_aCombo[nCntCombo].pos.x = pos.x;
			g_aCombo[nCntCombo].pos.y = pos.y;
			g_aCombo[nCntCombo].pos.z = pos.z;
			g_aCombo[nCntCombo].kill = 0;
			g_aCombo[nCntCombo].fSiz = fSiz;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - fSiz, g_aCombo[nCntCombo].pos.y - fSiz, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + fSiz, g_aCombo[nCntCombo].pos.y - fSiz, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - fSiz, g_aCombo[nCntCombo].pos.y + fSiz, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + fSiz, g_aCombo[nCntCombo].pos.y + fSiz, 0.0f);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(X*number, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(X*number+ X, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(X*number, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(X*number+ X, 1.0f);

			g_aCombo[nCntCombo].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aCombo[nCntCombo].nLife = nLife;
			g_aCombo[nCntCombo].nMaxLife = nLife;
			g_aCombo[nCntCombo].bUse = true;
			g_aCombo[nCntCombo].nType = nType;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffCombo->Unlock();

}


