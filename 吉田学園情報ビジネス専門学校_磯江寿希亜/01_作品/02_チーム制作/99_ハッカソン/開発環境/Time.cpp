//**************************************************
//
// 制作 ( timer )
// Author  :
//
//**************************************************
#include"Time.h"
#include"game.h"
#include"fade.h"

static LPDIRECT3DTEXTURE9 s_pTextureTimer = NULL; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffTimer= NULL; //頂点バッファの設定

static D3DXVECTOR3 s_pos; //スコアの位置	
static int s_nTimer,nCut;

//===================
//初期化処理
//===================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntTimer;
	s_nTimer = 0;
	nCut=0;

	s_pos = D3DXVECTOR3(1010.0f, 50.0f, 0.0f);				//位置設定		タイム自体

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\number001.png",
		&s_pTextureTimer);

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&s_pVtxBuffTimer,
		NULL);

//-------------------------------------------------------------------------------------------


	VERTEX_2D*pVtx; //頂点へのポインタ
	//頂点バッファをロックし頂点情報へのポインタを取得
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);	
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{

		//頂点座標
		SetNorotpos(pVtx,
			s_pos.x - 30,
			s_pos.x + 30,
			s_pos.y - 30,
			s_pos.y + 30);

		s_pos += D3DXVECTOR3(54.0f, 0.0f, 0.0f);		//タイムの感覚
		if (nCntTimer == 2)
		{
			s_pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//小数点のタイム
		}
		//RHWの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		
		//テクスチャの座標設定
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	s_pVtxBuffTimer->Unlock();

	SetTimer(90);			//30秒
}

//===================
//破棄処理
//===================
void UninitTimer(void)
{
	//テクスチャの破棄
	if (s_pTextureTimer != NULL)
	{
		s_pTextureTimer->Release();
		s_pTextureTimer = NULL;
	}
	//頂点バッファの破棄
	if (s_pVtxBuffTimer != NULL)
	{
		s_pVtxBuffTimer->Release();
		s_pVtxBuffTimer = NULL;
	}
}

//===================
//更新処理
//===================
void UpdateTimer(void)
{
	bool bUse = false;

	if (nCut == 120)
	{
		AddTimer(-1);
		nCut = 0;
	}

	nCut++;

	//if (s_nTimer != 0)
	//{
	//	AddTimer(-1);		
	//}
		
}

//===================
//描画処理
//===================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	int nCntTimer;

	pDevice = GetDevice();		//代入

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			nCntTimer * 4,
			2);
	}
	
}

//===================
//セット
//===================
void SetTimer(int nTimer)
{
	int nCntTimer;
	int aPosTexU[MAX_TIMER]; //各桁の数字を格納

	s_nTimer = nTimer;
	/*aPosTexU[0] = (s_nTimer % 100000) / 10000;
	aPosTexU[1] = (s_nTimer % 10000) / 1000;
	aPosTexU[2] = (s_nTimer % 1000) / 100;*/
	aPosTexU[0] = (s_nTimer % 100) / 10;
	aPosTexU[1] = (s_nTimer % 10) / 1;

	VERTEX_2D*pVtx; //頂点へのポインタ
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//テクスチャの座標設定
		Settex(pVtx, 0.1f*aPosTexU[nCntTimer], 0.1f*aPosTexU[nCntTimer] + 0.1f, 0.0f, 1.0f);
		pVtx += 4; //頂点ポイントを四つ進む
	}
	//頂点バッファをアンロック
	s_pVtxBuffTimer->Unlock();

}

//===================
//加算
//===================
void AddTimer(int nValue)
{
	int nCntTimer;
	int aPosTexU[MAX_TIMER]; //各桁の数字を格納

	s_nTimer += nValue;


	/*aPosTexU[0] = (s_nTimer % 100000) / 10000;
	aPosTexU[1] = (s_nTimer % 10000) / 1000;
	aPosTexU[2] = (s_nTimer % 1000) / 100;*/
	aPosTexU[0] = (s_nTimer % 100) / 10;
	aPosTexU[1] = (s_nTimer % 10) / 1;

	VERTEX_2D*pVtx; //頂点へのポインタ
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点バッファをロックし頂点情報へのポインタを取得
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//テクスチャの座標設定
		Settex(pVtx, 0.1f*aPosTexU[nCntTimer], 0.1f*aPosTexU[nCntTimer] + 0.1f, 0.0f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}
	if (s_nTimer <= 0)
	{
		SetFade(MODE_RESULT);		//ゲーム画面に移行
	}
	//頂点バッファをアンロック
	s_pVtxBuffTimer->Unlock();
}
int GetTimer(void)
{
	return s_nTimer;
}

void SetNorotpos(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	pVtx[0].pos = D3DXVECTOR3(left, top, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(right, top, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(left, down, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(right, down, 0.0f);
}