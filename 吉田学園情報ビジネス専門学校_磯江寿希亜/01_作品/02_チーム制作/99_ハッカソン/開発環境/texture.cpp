//**************************************************
// 
// FPG制作 ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定数
//==================================================
namespace
{
const char *s_FileName[] =
{// テクスチャのパス
	//タイトル画面
	"data\\TEXTURE\\TITLE\\Title_BG.png",		// タイトル画面の背景
	"data\\TEXTURE\\TITLE\\Title_Logo.png",		// タイトルロゴ
	"data\\TEXTURE\\TITLE\\Tutorial.png",		// チュートリアル画面

	//ゲーム画面
	"data\\TEXTURE\\GAME\\Game_BG.png",			// ゲーム画面の背景
	"data\\TEXTURE\\GAME\\Bom.png",				// 爆弾
	"data\\TEXTURE\\GAME\\BalloonBom.png",		// 風船付き爆弾
	"data\\TEXTURE\\GAME\\Flower.png",			// 花
	"data\\TEXTURE\\GAME\\Fox_UFO.png",			// UFO in きつね
	"data\\TEXTURE\\GAME\\Light_Bright.png",	// 明るい街灯
	"data\\TEXTURE\\GAME\\Light_Dark.png",		// 暗い街灯
	"data\\TEXTURE\\GAME\\1t.png",				// 1t
	"data\\TEXTURE\\GAME\\3t.png",				// 3t

	//リザルト画面
	"data\\TEXTURE\\RESULT\\GameClear.png",		// ゲームクリア画面の背景
	"data\\TEXTURE\\RESULT\\GameOver.png",		// ゲームオーバー画面の背景

    /*↓ エフェクト ↓*/
    "data/TEXTURE/EFFECT/fire.png",				// 炎のエフェクト
    "data/TEXTURE/EFFECT/spin.png",				// ディスクのエフェクト
    "data/TEXTURE/EFFECT/tackle.png",			// タックルのエフェクト
    "data/TEXTURE/EFFECT/Goal.png",				// ゴールのエフェクト
    "data/TEXTURE/EFFECT/spark.png",			// 壁の火花
};
}// namespaceはここまで

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// スタティック変数
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespaceはここまで

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void LoadTexture(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture)
{
	if (texture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return NULL;
	}

	assert(texture >= 0 && texture < TEXTURE_MAX);

	return s_pTexture[texture];
}
