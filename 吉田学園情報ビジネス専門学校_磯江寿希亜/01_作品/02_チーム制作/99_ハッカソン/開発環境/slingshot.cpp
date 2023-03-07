//**************************************************
//
// 制作 ( スリリング )
// Author  : hamada ryuga
//
//**************************************************

#include "game.h"
#include "slingshot.h"
#include "input.h"
#include "ball.h"
#include "sound.h"

#define MAX_SIZE_Y (30.0f)
#define MAX_SIZE_X (220.0f)

static LPDIRECT3DTEXTURE9 s_pTextureSlingshotleft = NULL; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffSlingshotleft = NULL; //頂点バッファの設定
static D3DXVECTOR3 s_posSlingshotleft; //左の初期位置
static LPDIRECT3DTEXTURE9 s_pTextureSlingshotlight = NULL; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffSlingshotlight = NULL; //頂点バッファの設定
static D3DXVECTOR3 s_posSlingshotlight; //右の初期位置
static int s_nSlingshot, nCounterAnim, nPatternAnim;
static D3DXVECTOR3 clickpoint;
static D3DXVECTOR3 move;
static D3DXVECTOR3 length;
static bool press;
static int number;

//===================
//初期化処理
//===================
void InitSlingshot(void)
{
	number = 0;
	press = false;
	LPDIRECT3DDEVICE9  pDevice;
	clickpoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//s_nSlingshot = 0;
	s_posSlingshotleft = D3DXVECTOR3(SCREEN_WIDTH/2-200.0f, 350.0f, 0.0f);
	//デバイスの取得
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/asi.png",
		&s_pTextureSlingshotleft);

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&s_pVtxBuffSlingshotleft,
		NULL);

	VERTEX_2D*pVtx; //頂点へのポインタ
					//頂点バッファをロックし頂点情報へのポインタを取得
	s_pVtxBuffSlingshotleft->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(s_posSlingshotleft.x - 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(s_posSlingshotleft.x + 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(s_posSlingshotleft.x - 20, s_posSlingshotleft.y + MAX_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(s_posSlingshotleft.x + 20, s_posSlingshotleft.y + MAX_SIZE_Y, 0.0f);
	
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

	//頂点バッファをアンロック
	s_pVtxBuffSlingshotleft->Unlock();


	//---------------------
	//みぎの設定
	//---------------------
	s_posSlingshotlight = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 350.0f, 0.0f);
	
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/asi.png",
		&s_pTextureSlingshotlight);

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&s_pVtxBuffSlingshotlight,
		NULL);

	//VERTEX_2D*pVtx; //頂点へのポインタ
	//頂点バッファをロックし頂点情報へのポインタを取得
	s_pVtxBuffSlingshotlight->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(s_posSlingshotlight.x - 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(s_posSlingshotlight.x + 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(s_posSlingshotlight.x - 20, s_posSlingshotlight.y + MAX_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(s_posSlingshotlight.x + 20, s_posSlingshotlight.y + MAX_SIZE_Y, 0.0f);
	
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

	//頂点バッファをアンロック
	s_pVtxBuffSlingshotlight->Unlock();


}

//===================
//破棄処理
//===================
void UninitSlingshot(void)
{
	StopSound();

	//テクスチャの破棄
	if (s_pTextureSlingshotleft != NULL)
	{
		s_pTextureSlingshotleft->Release();
		s_pTextureSlingshotleft = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuffSlingshotleft != NULL)
	{
		s_pVtxBuffSlingshotleft->Release();
		s_pVtxBuffSlingshotleft = NULL;
	}

	//テクスチャの破棄
	if (s_pTextureSlingshotlight != NULL)
	{
		s_pTextureSlingshotlight->Release();
		s_pTextureSlingshotlight = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuffSlingshotlight != NULL)
	{
		s_pVtxBuffSlingshotlight->Release();
		s_pVtxBuffSlingshotlight = NULL;
	}


}

//===================
//更新処理
//===================
void UpdateSlingshot(void)
{

	if (GetMousePress(MOUSE_INPUT_LEFT))
	{
		
		length = GetMouse();	

		VERTEX_2D*pVtx; //頂点へのポインタ
						//頂点バッファをロックし頂点情報へのポインタを取得
		s_pVtxBuffSlingshotleft->Lock(0, 0, (void**)&pVtx, 0);

		if (length.y < s_posSlingshotleft.y - MAX_SIZE_Y)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(length.x - 20, length.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(length.x + 20, length.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(s_posSlingshotleft.x - 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(s_posSlingshotleft.x + 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
		}
		else
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(s_posSlingshotleft.x - 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(s_posSlingshotleft.x + 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(length.x	- 20 , length.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( length.x + 20 , length.y, 0.0f);
		}
		//頂点バッファをアンロック
		s_pVtxBuffSlingshotleft->Unlock();

		//頂点バッファをロックし頂点情報へのポインタを取得
		s_pVtxBuffSlingshotlight->Lock(0, 0, (void**)&pVtx, 0);


		if (length.y < s_posSlingshotlight.y - MAX_SIZE_Y)
		{
			pVtx[0].pos = D3DXVECTOR3(length.x - 20, length.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(length.x + 20, length.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(s_posSlingshotlight.x - 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(s_posSlingshotlight.x + 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
		}
		else
		{		//頂点座標
			pVtx[0].pos = D3DXVECTOR3(s_posSlingshotlight.x - 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(s_posSlingshotlight.x + 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(length.x - 20, length.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(length.x + 20, length.y, 0.0f);
		}
		//頂点バッファをアンロック
		s_pVtxBuffSlingshotlight->Unlock();
	
	}
	else if (press)
	{
		move = D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f) - length;
		press = false;
		move /= 50.0f;

		PlaySound(SOUND_LABEL_SE_SHOT);

		MoveBall(move, number);
	}
	else
	{
		VERTEX_2D*pVtx; //頂点へのポインタ
		//頂点バッファをロックし頂点情報へのポインタを取得
		s_pVtxBuffSlingshotleft->Lock(0, 0, (void**)&pVtx, 0);
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(s_posSlingshotleft.x - 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_posSlingshotleft.x + 20, s_posSlingshotleft.y - MAX_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(s_posSlingshotleft.x + MAX_SIZE_X - 40.0f, s_posSlingshotleft.y + MAX_SIZE_Y*2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_posSlingshotleft.x + MAX_SIZE_X, s_posSlingshotleft.y + MAX_SIZE_Y*2, 0.0f);


		//頂点バッファをアンロック
		s_pVtxBuffSlingshotleft->Unlock();

		//頂点バッファをロックし頂点情報へのポインタを取得
		s_pVtxBuffSlingshotlight->Lock(0, 0, (void**)&pVtx, 0);
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(s_posSlingshotlight.x - 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_posSlingshotlight.x + 20, s_posSlingshotlight.y - MAX_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(s_posSlingshotlight.x - MAX_SIZE_X, s_posSlingshotlight.y + MAX_SIZE_Y*2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_posSlingshotlight.x - MAX_SIZE_X+40.0f, s_posSlingshotlight.y + MAX_SIZE_Y * 2, 0.0f);

		//頂点バッファをアンロック
		s_pVtxBuffSlingshotlight->Unlock();
	}
	if (GetMouseTrigger(MOUSE_INPUT_LEFT))
	{
		press = true;
		clickpoint = GetMouse();
		number = SetBall(length, 150, 0, 30.0f);
	}
}

//===================
//描画処理
//===================
void DrawSlingshot(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
//	int nCntSlingshot;


	pDevice = GetDevice();		//代入

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffSlingshotleft, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureSlingshotleft);

	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	//---------------------
	//みぎの設定
	//---------------------
	pDevice = GetDevice();		//代入

								//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuffSlingshotlight, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureSlingshotlight);

	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

}

