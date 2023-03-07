//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************
#include <stdio.h>
#include "ranking.h"
#include "score.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include"sound.h"

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
	bool hikari;
}RankScore;

//グローバル変数
static LPDIRECT3DTEXTURE9 s_pTextureRank = NULL;			//テクスチャへのポインタ
static LPDIRECT3DTEXTURE9 s_pTextureRankScore = NULL;		//テクスチャへのポインタ
static LPDIRECT3DTEXTURE9 s_pTextureRankBG = NULL;		    //テクスチャへのポインタ

static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRank = NULL;		//頂点バッファへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankScore = NULL;	//頂点バッファへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankBG = NULL;	//頂点バッファへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankBG2 = NULL;	//頂点バッファへのポインタ＜-ランキングみやくするやつ

static RankScore s_aRankScore[MAX_RANK];	//ランキングスコア情報
static int s_nRankUpdate = -1;				//更新ランクNo.
static int s_nTimerRanking;				//ランキング画面表示タイマー
static int nTimesekand;                    //二個目のタイマー
static bool nTimesekand2;					//タイマー
static D3DXCOLOR nTimecol;	                //色

//==============
//初期化処理
//==============
void InitRanking(void)
{


	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	int nCntRank;
	int nCntScore;
	nTimesekand2 = false;
	s_nTimerRanking = 0;
	nTimesekand = 0;
	nTimecol = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/ranking_rank1.png",
		&s_pTextureRank);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/score.png",
		&s_pTextureRankScore);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/yoru2.png",
		&s_pTextureRankBG);

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		s_aRankScore[nCntRank].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
		s_aRankScore[nCntRank].hikari = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRank,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankScore,
		NULL);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankBG,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankBG2,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = s_aRankScore[nCntRank].pos.x - 50.0f;
		pVtx[0].pos.y = s_aRankScore[nCntRank].pos.y - 50.0f + nCntRank * 100;
		pVtx[0].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[1].pos.x = s_aRankScore[nCntRank].pos.x + 50.0f;
		pVtx[1].pos.y = s_aRankScore[nCntRank].pos.y - 50.0f + nCntRank * 100;
		pVtx[1].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[2].pos.x = s_aRankScore[nCntRank].pos.x - 50.0f;
		pVtx[2].pos.y = s_aRankScore[nCntRank].pos.y + 50.0f + nCntRank * 100;
		pVtx[2].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[3].pos.x = s_aRankScore[nCntRank].pos.x + 50.0f;
		pVtx[3].pos.y = s_aRankScore[nCntRank].pos.y + 50.0f + nCntRank * 100;
		pVtx[3].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.2f * nCntRank);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.2f * nCntRank);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + 0.2f * nCntRank);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + 0.2f * nCntRank);

		pVtx += 4;

	}
	//頂点バッファをアンロックする
	s_pVtxBuffRank->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		s_aRankScore[nCntRank].pos.x += 100;	//スコア表示場所へ移動
		for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{
			pVtx[0].pos.x = s_aRankScore[nCntRank].pos.x - 30.0f + nCntScore * 50;
			pVtx[0].pos.y = s_aRankScore[nCntRank].pos.y - 30.0f + nCntRank * 100;
			pVtx[0].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[1].pos.x = s_aRankScore[nCntRank].pos.x + 30.0f + nCntScore * 50;
			pVtx[1].pos.y = s_aRankScore[nCntRank].pos.y - 30.0f + nCntRank * 100;
			pVtx[1].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[2].pos.x = s_aRankScore[nCntRank].pos.x - 30.0f + nCntScore * 50;
			pVtx[2].pos.y = s_aRankScore[nCntRank].pos.y + 30.0f + nCntRank * 100;
			pVtx[2].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[3].pos.x = s_aRankScore[nCntRank].pos.x + 30.0f + nCntScore * 50;
			pVtx[3].pos.y = s_aRankScore[nCntRank].pos.y + 30.0f + nCntRank * 100;
			pVtx[3].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;

		}
	}
	//頂点バッファをアンロックする
	s_pVtxBuffRankScore->Unlock();
	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffRankBG2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(600.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(600.0f, 550.0f, 0.0f);

	//RHWの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 200);

	//頂点バッファをアンロックする
	s_pVtxBuffRankBG2->Unlock();

	s_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//RHWの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	s_pVtxBuffRankBG->Unlock();
	//サウンド開始
	PlaySound(SOUND_LABEL_BGM001);
}

//=========================================
//ランキングの終了処理
//=========================================
void UninitRanking(void)
{
	//サウンド停止
	StopSound();
	//テクスチャの破棄
	if (s_pTextureRank != NULL)
	{
		s_pTextureRank->Release();
		s_pTextureRank = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuffRank != NULL)
	{
		s_pVtxBuffRank->Release();
		s_pVtxBuffRank = NULL;
	}
	//テクスチャの破棄
	if (s_pTextureRankBG != NULL)
	{
		s_pTextureRankBG->Release();
		s_pTextureRankBG = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuffRankBG != NULL)
	{
		s_pVtxBuffRankBG->Release();
		s_pVtxBuffRankBG = NULL;
	}
	//頂点バッファの破棄
	if (s_pVtxBuffRankBG2 != NULL)
	{
		s_pVtxBuffRankBG2->Release();
		s_pVtxBuffRankBG2 = NULL;
	}

	//テクスチャの破棄
	if (s_pTextureRankScore != NULL)
	{
		s_pTextureRankScore->Release();
		s_pTextureRankScore = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuffRankScore != NULL)
	{
		s_pVtxBuffRankScore->Release();
		s_pVtxBuffRankScore = NULL;
	}
}

//============
//更新処理
//============
void UpdateRanking(void)
{//文字がちかちかする処理
	int nCntRank01;
	nTimesekand++;
	if (nTimesekand == 1)
	{
		nTimesekand2 = false;
	}
	if (nTimesekand == 31)
	{
		nTimesekand2 = true;
	}
	if (nTimesekand == 61)
	{
		nTimesekand = 0;

	}
	for (nCntRank01 = 0; nCntRank01 < MAX_RANK; nCntRank01++)
	{
		if (nTimesekand2 == false)
		{
			nTimecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (nTimesekand2 == true)
		{
			nTimecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		}
	}


	int nCntRank;
	int nCntScore;
	VERTEX_2D *pVtx;
	//ロック
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (s_aRankScore[nCntRank].hikari)
		{
			for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(nTimecol);
				pVtx[1].col = D3DXCOLOR(nTimecol);
				pVtx[2].col = D3DXCOLOR(nTimecol);
				pVtx[3].col = D3DXCOLOR(nTimecol);
				pVtx += 4;

			}
		}
		else
		{
			for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx += 4;

			}
		}

	}
	//頂点バッファをアンロックする
	s_pVtxBuffRankScore->Unlock();
	FADE pFade;
	pFade = GetFade();
	s_nTimerRanking++;
	if (s_nTimerRanking == 1200)
	{
		SetFade(MODE_TITLE);
	}
	if ((GetKeyboardTrigger(DIK_RETURN) == true ||
		GetKeyboardTrigger(JOYKEY_START) == true ||
		GetKeyboardTrigger(JOYKEY_A) == true) && pFade == FADE_NONE)
	{//エンターを押されたとき
		//PlaySound(SOUND_LABEL_SE_KIRA);
		SetFade(MODE_TITLE);
	}
}

//==========
//描画処理
//==========
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;
	int nCntScore;

	//=================================================
	//	頂点フォーマットの設定フォーマットなどは
	//	それぞれで必要です
	//　たくさん作ったら忘れずに
	//=================================================
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, s_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ
	pDevice->SetTexture(0, s_pTextureRankBG);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, s_pVtxBuffRankBG2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, s_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, s_pTextureRank);

		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);
	}

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, s_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//順位
		for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{//スコア
		 //テクスチャの設定
			pDevice->SetTexture(0, s_pTextureRankScore);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntRank * 4 * NUM_SCORE) + (nCntScore * 4), 2);
		}
	}


}

//==========
//リセット
//==========
void ResetRanking(void)
{
	FILE *pFile;	//ファイルポインタを宣言
	int nCntRank;

	s_nRankUpdate = -1;	//更新ランク初期化

						//ファイルを開く
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//ランキングの読み込み
			fscanf(pFile, "%d", &s_aRankScore[nCntRank].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かない場合
		FADE pFade = GetFade();		//今のフェード

		if (pFade == FADE_NONE)
		{//何もしていない状態なら
		 //フェードの設定
			SetFade(MODE_TITLE);
		}
	}
}

//=======
//セーブ
//======
void SaveRanking(void)
{
	FILE *pFile;	//ファイルポインタを宣言
	int nCntRank;

	s_nRankUpdate = -1;	//更新ランクNo.の初期化

						//ファイルを開く
	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//ランキングの書き込み
			fprintf(pFile, "%d\n", s_aRankScore[nCntRank].nScore);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かない場合
		FADE pFade = GetFade();		//今のフェード

		if (pFade == FADE_NONE)
		{//何もしていない状態なら
		 //フェードの設定
			SetFade(MODE_TITLE);
		}
	}

}

//=====================
//ランキングの設定処理
//======================
void SetRanking(int nScore)
{
	VERTEX_2D *pVtx;
	int nCntRank;
	int nCnt2Rank;
	int nCheckDataMin;

	//ランキングの最下位と今回のスコアを比べる
	if (nScore >= s_aRankScore[MAX_RANK - 1].nScore)
	{
		s_nRankUpdate = 5;
		//比較した数値を入れる。
		s_aRankScore[MAX_RANK - 1].nScore = nScore;
	}

	for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
	{
		for (nCnt2Rank = nCntRank + 1; nCnt2Rank < MAX_RANK; nCnt2Rank++)
		{
			if (s_aRankScore[nCntRank].nScore <= s_aRankScore[nCnt2Rank].nScore)
			{

				nCheckDataMin = s_aRankScore[nCnt2Rank].nScore;
				s_aRankScore[nCnt2Rank].nScore = s_aRankScore[nCntRank].nScore;
				s_aRankScore[nCntRank].nScore = nCheckDataMin;
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		int aPosTexU[6];

		aPosTexU[0] = s_aRankScore[nCntRank].nScore % 1000000 / 100000;
		aPosTexU[1] = s_aRankScore[nCntRank].nScore % 100000 / 10000;
		aPosTexU[2] = s_aRankScore[nCntRank].nScore % 10000 / 1000;
		aPosTexU[3] = s_aRankScore[nCntRank].nScore % 1000 / 100;
		aPosTexU[4] = s_aRankScore[nCntRank].nScore % 100 / 10;
		aPosTexU[5] = s_aRankScore[nCntRank].nScore % 10 / 1;

		for (nCnt2Rank = 0; nCnt2Rank < NUM_SCORE; nCnt2Rank++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCnt2Rank], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCnt2Rank], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCnt2Rank], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCnt2Rank], 1.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx += 4;
		}
	}

	SaveRanking();

	//頂点バッファをアンロックする
	s_pVtxBuffRankScore->Unlock();
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (s_aRankScore[nCntRank].nScore == nScore)
		{

			s_aRankScore[nCntRank].hikari = true;

		}
	}
}