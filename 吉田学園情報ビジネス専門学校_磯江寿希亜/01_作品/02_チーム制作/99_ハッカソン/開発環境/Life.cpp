//**************************************************
//
// 制作 ( ライフ )
// Author  : hamada ryuuga
//
//**************************************************
#include "Life.h"
#include "enemy.h"
#include"particle.h"
#include "fade.h"
#include "sound.h"
#include "effect.h"
#define KINDS (1)	//テクスチャ種類

#define SIZ_X (50)	//サイズX
#define SIZ_Y (50)	//サイズY

static LPDIRECT3DTEXTURE9 s_TextureLife[KINDS] = {};			//テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_PvtxBuffLife = NULL;				//頂点バッファへのポインタ
static Life s_Life[MAX_Life];
static int LIFE;




void InitLife(void)
{
	LIFE = 4;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み	敵テクスチャ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/Flower.png",				//ライフ
		&s_TextureLife[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_Life,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&s_PvtxBuffLife,
		NULL);

	for (int Cnt = 0; Cnt < MAX_Life; Cnt++)
	{//初期化
		s_Life[Cnt].move = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);			//移動量
		s_Life[Cnt].pos  = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);			//位置
		s_Life[Cnt].col = D3DXCOLOR (0.0f, 0.0f, 0.0f,0.0f);

		s_Life[Cnt].nLife = 1;					//体力
		s_Life[Cnt].bUse = false;					//使用してるかどうか

	}

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_PvtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = 0; Cnt < MAX_Life; Cnt++, pVtx += 4)
	{

		////頂点座標の設定
		//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

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
		s_PvtxBuffLife->Unlock();

		
		SetLife(D3DXVECTOR3(200.0f, 600.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetLife(D3DXVECTOR3(400.0f, 600.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));								 
		SetLife(D3DXVECTOR3(900.0f, 600.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SetLife(D3DXVECTOR3(1100.0f, 600.0f, 0.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}
void UninitLife(void)
{
	StopSound();
	for (int count = 0; count < KINDS; count++)
	{
		if (s_TextureLife[count] != NULL)
		{
			s_TextureLife[count]->Release();
			s_TextureLife[count] = NULL;
		}
	}
	//頂点バッファ破棄
	if (s_PvtxBuffLife != NULL)
	{
		s_PvtxBuffLife->Release();
		s_PvtxBuffLife = NULL;
	}
}
void UpdateLife(void)
{
	Life *pLife = GetLife();
	
	for (int nCnt = 0; nCnt < MAX_Life; nCnt++)
	{
		if (s_Life[nCnt].bUse)
		{
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
						Enemy *pEnemy = GetEnemy(nCntEnemy);
						if (pEnemy->bUse)
						{
							if (s_Life[nCnt].pos.x + 70 >= pEnemy->pos.x
								&& s_Life[nCnt].pos.x - 70 <= pEnemy->pos.x
								&& s_Life[nCnt].pos.y + 70 >= pEnemy->pos.y
								&& s_Life[nCnt].pos.y - 70 <= pEnemy->pos.y)
							{//弾座標重なり
								HitLife(1, nCnt);
								pEnemy->bUse = false;
								SetEffect(s_Life[nCnt].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_SHOOT, 150, 200.0f, false);
								//サウンド開始
								PlaySound(SOUND_LABEL_SE_EXPLOSION);
							}
						}
						
			}
		}

	}
}
void DrawLife(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_PvtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_Life; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_TextureLife[0]);

		if (s_Life[nCnt].bUse)
		{
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
}
void SetLife(D3DXVECTOR3 pos, D3DXCOLOR col)
{

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_PvtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int Cnt = 0; Cnt < MAX_Life; Cnt++)
	{
		if (!s_Life[Cnt].bUse)
		{
			s_Life[Cnt].pos = pos;

			//頂点座標の設定
			pVtx[0].pos.x = s_Life[Cnt].pos.x - SIZ_X;
			pVtx[0].pos.y = s_Life[Cnt].pos.y - SIZ_Y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = s_Life[Cnt].pos.x + SIZ_X;
			pVtx[1].pos.y = s_Life[Cnt].pos.y - SIZ_Y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = s_Life[Cnt].pos.x - SIZ_X;
			pVtx[2].pos.y = s_Life[Cnt].pos.y + SIZ_Y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = s_Life[Cnt].pos.x + SIZ_X;
			pVtx[3].pos.y = s_Life[Cnt].pos.y + SIZ_Y;
			pVtx[3].pos.z = 0.0f;

			s_Life[Cnt].col = col;
			s_Life[Cnt].bUse = true;
			break;
		}
		pVtx += 4;	//頂点座標データのポインタを４つ分進める
	}
	//頂点をアンロックする
	s_PvtxBuffLife->Unlock();
}

void HitLife(int nDamage,int number)
{

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	s_PvtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		
		s_Life[number].nLife -= nDamage;

		if (s_Life[number].nLife <= 0)					//---------------プレイヤーが死んだら---------------
		{
			s_Life[number].bUse = false;
			LIFE--;
			if (LIFE <= 0 )
			{
				SetFade(MODE_GAMEOVER);
			}
		}
	

	//頂点をアンロックする
	s_PvtxBuffLife->Unlock();
}

Life *GetLife(void)
{
	return &s_Life[0];
}
