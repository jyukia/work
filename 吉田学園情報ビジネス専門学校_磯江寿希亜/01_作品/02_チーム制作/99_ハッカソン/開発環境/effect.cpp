//**************************************************
//
// 制作 ( effect.cpp )
// Author  : hamada ryuuga
//
//**************************************************
#include"effect.h"
#include"texture.h"

#include <assert.h>

#define NUR_EFFECT (4)

//スタティック
static Effect s_aEffect[MAX_EFFECT];
static TEXTURE s_aTexture[EFFECTSTATE_MAX];
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = NULL; //頂点バッファの設定
static bool Particle;
static int timer;
static D3DXVECTOR3 Log;
static bool setmirror;
EFFECTSTATE settex;
//==================================
//初期化
//==================================
void InitEffect(void)
{
	s_aTexture[EFFECTSTATE_SPIN] = TEXTURE_Effect_spin;
	s_aTexture[EFFECTSTATE_SHOOT] = TEXTURE_Effect_fire;
	s_aTexture[EFFECTSTATE_TACKLE] = TEXTURE_Effect_tackle;
	s_aTexture[EFFECTSTATE_GOAL_POINT3] = TEXTURE_Effect_goal;
	s_aTexture[EFFECTSTATE_GOAL_POINT5] = TEXTURE_Effect_goal;
	s_aTexture[EFFECTSTATE_SPARK] = TEXTURE_Effect_spark;
	timer = 0;
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//初期化忘れない
		s_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aEffect[nCntEffect].nLife = 0;
		s_aEffect[nCntEffect].bUse = false;
	}

	LPDIRECT3DDEVICE9  pDevice;


	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファ
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&g_pVtxBuff,
		NULL);


}

//==================================
//破棄
//==================================
void UninitEffect(void)
{
	//頂点バッファの破壊
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
	
}

//==================================
//更新
//==================================
void UpdateEffect(void)
{
	int nCntEffect;

	if (Particle)
	{
		timer++;
		
		SetEffect(D3DXVECTOR3(Log.x, Log.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), settex, 100, 50.0f, setmirror);
	
		if (timer >= 30)
		{
			Particle = false;
			timer = 0;
		}
	}
	
	VERTEX_2D*pVtx; //頂点へのポインタ


					//頂点バッファをアンロック
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse)
		{
	

			s_aEffect[nCntEffect].pos += s_aEffect[nCntEffect].move;

			SetNormalpos2d(pVtx, s_aEffect[nCntEffect].pos.x - s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.x + s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.y - s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.y + s_aEffect[nCntEffect].fRadeius);

			s_aEffect[nCntEffect].col.a -= 1.0f / s_aEffect[nCntEffect].nMaxLife;

			if (s_aEffect[nCntEffect].col.a <=0.0f)
			{
				s_aEffect[nCntEffect].bUse = false;
			}

			// テクスチャの設定
			SetVtxAnimTex(pVtx, &s_aEffect[nCntEffect].AnimTex);
			
			SetTex2d(pVtx, (1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionX)*s_aEffect[nCntEffect].AnimTex.nPatternX
				, (1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionX)* (s_aEffect[nCntEffect].AnimTex.nPatternX + 1)
				, 1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionY*s_aEffect[nCntEffect].AnimTex.nPatternY
				, 1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionY*(s_aEffect[nCntEffect].AnimTex.nPatternY + 1), s_aEffect[nCntEffect].mirror);

			//頂点カラーの設定
			pVtx[0].col = s_aEffect[nCntEffect].col;
			pVtx[1].col = s_aEffect[nCntEffect].col;
			pVtx[2].col = s_aEffect[nCntEffect].col;
			pVtx[3].col = s_aEffect[nCntEffect].col;


		
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuff->Unlock();
	
}
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCnt;

	pDevice = GetDevice();		//代入

								//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, GetTexture(s_aTexture[s_aEffect[nCnt].nType]));

		if (s_aEffect[nCnt].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==================================
//セット　引数　座標、色、使いたいタイプ、寿命、サイズ
//==================================
void SetEffect(D3DXVECTOR3 pos,  D3DXCOLOR col, EFFECTSTATE nType, int life, float size, bool mirror)
{
	assert(nType >= 0 && nType < EFFECTSTATE_MAX);

	int nCntEffect;
	VERTEX_2D*pVtx; //頂点へのポインタ


	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (!s_aEffect[nCntEffect].bUse)
		{
			//敵が使用されてない場合
			s_aEffect[nCntEffect].mirror = mirror;
			s_aEffect[nCntEffect].fRadeius = size;
			s_aEffect[nCntEffect].pos.x = pos.x;
			s_aEffect[nCntEffect].pos.y = pos.y;
			s_aEffect[nCntEffect].pos.z = pos.z;


			//頂点バッファをアンロック
			g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

													//頂点座標
			SetNormalpos2d(pVtx, s_aEffect[nCntEffect].pos.x - s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.x + s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.y - s_aEffect[nCntEffect].fRadeius,
				s_aEffect[nCntEffect].pos.y + s_aEffect[nCntEffect].fRadeius);

			s_aEffect[nCntEffect].nType = nType;
			s_aEffect[nCntEffect].nLife = life;
			s_aEffect[nCntEffect].bUse = true;
			s_aEffect[nCntEffect].col = col;
			s_aEffect[nCntEffect].nMaxLife = life;
			setmirror = mirror; 
			s_aEffect[nCntEffect].move.x = 0.0f;
			s_aEffect[nCntEffect].move.y = 0.0f;
			switch (nType)
			{
			case EFFECTSTATE_SHOOT:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 10;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 1;
				break;
			case EFFECTSTATE_SPIN:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 5;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 3;
				break;
			case EFFECTSTATE_TACKLE:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 1;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 7;
				break;
			case EFFECTSTATE_GOAL_POINT5:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 5;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 3;
				Particle = true;
				Log = pos;
				settex = EFFECTSTATE_GOAL_POINT5;
				if (mirror)
				{
					s_aEffect[nCntEffect].move.x = sinf((float)(rand() % 629 - 314) / 100.0f)*7;
					s_aEffect[nCntEffect].move.y = sinf((float)(rand() % 629 - 314) / 100.0f)*5;
				}
				else
				{
					s_aEffect[nCntEffect].move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 7;
					s_aEffect[nCntEffect].move.y = sinf((float)(rand() % 629 - 314) / 100.0f) * 5;
				}
				break;
			case EFFECTSTATE_GOAL_POINT3:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 5;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 3;
				Particle = true;
				Log = pos;
				settex = EFFECTSTATE_GOAL_POINT3;
				if (mirror)
				{
					s_aEffect[nCntEffect].move.x = -5.0f;
					s_aEffect[nCntEffect].move.y = sinf((float)(rand() % 629 - 314) / 100.0f);
				}
				else
				{
					s_aEffect[nCntEffect].move.x = 5.0f;
					s_aEffect[nCntEffect].move.y = sinf((float)(rand() % 629 - 314) / 100.0f);
				}
				break;
			case EFFECTSTATE_SPARK:
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 8;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 1;
				break;
			default:
				assert(false);
				s_aEffect[nCntEffect].AnimTex.nDivisionX = 1;
				s_aEffect[nCntEffect].AnimTex.nDivisionY = 1;
				break;
			}

			SetTex2d(pVtx, (1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionX)*s_aEffect[nCntEffect].AnimTex.nPatternX
				, (1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionX)* (s_aEffect[nCntEffect].AnimTex.nPatternX + 1)
				, 1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionY*s_aEffect[nCntEffect].AnimTex.nPatternY
				, 1.0f / s_aEffect[nCntEffect].AnimTex.nDivisionY*(s_aEffect[nCntEffect].AnimTex.nPatternY + 1), s_aEffect[nCntEffect].mirror);

			//頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			//頂点バッファをアンロック
			g_pVtxBuff->Unlock();

			break;
		}
	}
}

//=========================================
// 座標設定
//Auther：hamada ryuuga
//=========================================
void SetNormalpos2d(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW)
{
	pVtx[0].pos = D3DXVECTOR3(XUP, YUP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(XDW, YUP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(XUP, YDW, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(XDW, YDW, 0.0f);
}
//---------------------------------------
//セットテクスチャ(2d)
//Auther：hamada ryuuga
//---------------------------------------
void SetTex2d(VERTEX_2D *pVtx, float left, float right, float top, float down,bool mirror)
{
	if (mirror)
	{	//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(right, top);
		pVtx[1].tex = D3DXVECTOR2(left, top);
		pVtx[2].tex = D3DXVECTOR2(right, down);
		pVtx[3].tex = D3DXVECTOR2(left, down);	
	}
	else 
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(left, top);
		pVtx[1].tex = D3DXVECTOR2(right, top);
		pVtx[2].tex = D3DXVECTOR2(left, down);
		pVtx[3].tex = D3DXVECTOR2(right, down);
	
	}

}

//---------------------------------------
//セットテクスチャ(2d)
//Auther：hamada ryuuga
//---------------------------------------
void SetTex2d(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}

//--------------------------------------------------
// テクスチャアニメーション
// Author：Hamada Ryuga
//--------------------------------------------------
void SetVtxAnimTex(VERTEX_2D* pVtx, ANIM_TEX* pAnimTex)
{
	pAnimTex->nCnt++;
	pAnimTex->nSpeed = 5;//ここで速度調整
	if ((pAnimTex->nCnt % pAnimTex->nSpeed) == 0)
	{

		pAnimTex->nPatternX++;

		if (pAnimTex->nPatternX >= pAnimTex->nDivisionX)
		{
			pAnimTex->nPatternX = 0;
			pAnimTex->nPatternY++;
		}
		if (pAnimTex->nPatternY >= pAnimTex->nDivisionY)
		{
			pAnimTex->nPatternY = 0;
		}

		SetTex2d(pVtx,
			1.0f / pAnimTex->nDivisionX * pAnimTex->nPatternX
			, 1.0f / pAnimTex->nDivisionX * pAnimTex->nPatternX + (1.0f / pAnimTex->nDivisionX)
			, 1.0f / pAnimTex->nDivisionY * pAnimTex->nPatternY
			, 1.0f / pAnimTex->nDivisionY * pAnimTex->nPatternY + 1.0f / pAnimTex->nDivisionY);
	}
}
