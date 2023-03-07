//================================
//
// 玉の設定
// Author:hamada ryuuga
//
//================================

#include "ball.h"
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "combo.h"
#include "sound.h"

#define	NUR_BALL	(1)

//グローバル関数
static LPDIRECT3DTEXTURE9 g_pTextureBall[NUR_BALL] = {}; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL; //頂点バッファの設定
static Ball g_aBall[MAX_BALL];
static float coleff;//エフェクトの色
static float coleff2;//エフェクトの色

//==================
//たまの初期化設定
//==================
void InitBall(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntBall;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/49-4.png",
		&g_pTextureBall[0]);

	coleff = 1.0f;
	coleff2 = 0.0f;

	//初期化
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		g_aBall[nCntBall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ポス
		g_aBall[nCntBall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ムーブ
		g_aBall[nCntBall].nLife = 0;//ライフ
		g_aBall[nCntBall].bUse = false;//使ってるか
		g_aBall[nCntBall].moveset = false;
		g_aBall[nCntBall].moveOn = false;
		g_aBall[nCntBall].Trigger = 0;   //種類
		g_aBall[nCntBall].nType = 0;//タイプ
		g_aBall[nCntBall].fSiz = 0.0f; //サイズ
		g_aBall[nCntBall].Move2 = 0;

	}

	//頂点バッファ
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&g_pVtxBuffBall,
		NULL);

	VERTEX_2D*pVtx; //頂点へのポインタ
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);


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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	g_pVtxBuffBall->Unlock();

}

//==================
//終了処理
//==================
void UninitBall(void)
{
	StopSound();

	int nCntBall;
	for (nCntBall = 0; nCntBall < NUR_BALL; nCntBall++)
	{
		//テクスチャの破棄
		if (g_pTextureBall[nCntBall] != NULL)
		{
			g_pTextureBall[nCntBall]->Release();
			g_pTextureBall[nCntBall] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}

}

//==================
//更新処理
//==================
void UpdateBall(void)
{
	int nCntBall;
	//エンジンシステム
	coleff2 += 0.1f;
	if (coleff2 >= 1.0f)
	{
		coleff2 = 0.0f;
	}
	
	VERTEX_2D*pVtx; //頂点へのポインタ
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{

		if (g_aBall[nCntBall].bUse)
		{
			
		
			if (GetMousePress(MOUSE_INPUT_LEFT)&& !g_aBall[nCntBall].moveset)
			{
				D3DXVECTOR3 length = GetMouse();
				g_aBall[nCntBall].pos = length;
				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(length.x - g_aBall[nCntBall].fSiz, length.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(length.x + g_aBall[nCntBall].fSiz, length.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(length.x - g_aBall[nCntBall].fSiz, length.y + g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(length.x + g_aBall[nCntBall].fSiz, length.y + g_aBall[nCntBall].fSiz, 0.0f);
			}
			if (g_aBall[nCntBall].moveOn)
			{
				g_aBall[nCntBall].nLife--;
				//位置更新
				g_aBall[nCntBall].pos += g_aBall[nCntBall].move;
				g_aBall[nCntBall].moveset = true;
				//頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					Enemy *pEnemy = GetEnemy(nCntEnemy);
					if (!pEnemy->bUse)
					{
						continue;
					}
					if (g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz >= pEnemy->pos.x- WIDTH
						&& g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz <= pEnemy->pos.x+ WIDTH
						&& g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz >= pEnemy->pos.y- HEIGHT
						&& g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz <= pEnemy->pos.y+ HEIGHT)
					{//弾座標重なり

							PlaySound(SOUND_LABEL_SE_EXP);


							g_aBall[nCntBall].kill++;
							SetCombo(pEnemy->pos, 150, 0, 50, g_aBall[nCntBall].kill);
							
							if (pEnemy->nType == 0)
							{
								AddScore(10 * g_aBall[nCntBall].kill);
							}
							if (pEnemy->nType == 1)
							{
								AddScore(30 * g_aBall[nCntBall].kill);
							}
							if (pEnemy->nType == 2)
							{
								AddScore(100 * g_aBall[nCntBall].kill);
							}
							
							pEnemy->bUse = false;
							// エフェクトの設定
							SetEffect(pEnemy->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_GOAL_POINT5, 50, 50.0f, false);
					}

				}
			}
			if (g_aBall[nCntBall].nLife == 0)
			{

				g_aBall[nCntBall].bUse = false;

			}

		}
			pVtx += 4;//頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	g_pVtxBuffBall->Unlock();
}

//==================
//弾の描画処理
//==================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntBall;

	pDevice = GetDevice();		//代入

								//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBall[g_aBall[nCntBall].nType]);

		if (g_aBall[nCntBall].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntBall * 4,
				2);
		}
	}
}

//==================
//弾の設定
//==================
int SetBall(D3DXVECTOR3 pos, int nLife, int nType, float fSiz)
{
	int nCntBall;
	VERTEX_2D*pVtx; //頂点へのポインタ

					//ロック
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse == false)
		{
			//弾が使用されてない場合
			g_aBall[nCntBall].pos.x = pos.x;
			g_aBall[nCntBall].pos.y = pos.y;
			g_aBall[nCntBall].pos.z = pos.z;
			g_aBall[nCntBall].kill = 0;
			g_aBall[nCntBall].fSiz = fSiz;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - fSiz, g_aBall[nCntBall].pos.y - fSiz, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + fSiz, g_aBall[nCntBall].pos.y - fSiz, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - fSiz, g_aBall[nCntBall].pos.y + fSiz, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + fSiz, g_aBall[nCntBall].pos.y + fSiz, 0.0f);
			g_aBall[nCntBall].nLife = nLife;
			g_aBall[nCntBall].bUse = true;
			g_aBall[nCntBall].moveset = false;
			g_aBall[nCntBall].moveOn = false;
			g_aBall[nCntBall].nType = nType;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBall->Unlock();

	return nCntBall;
}

void MoveBall(D3DXVECTOR3 move, int number)
{		
	g_aBall[number].move = move;
	g_aBall[number].moveOn = true;
}
