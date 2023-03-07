//**************************************************
// 
// FPG制作 ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// 列挙型
//==================================================
typedef enum
{
	//タイトル画面
	TEXTURE_TITLE_BG,		// タイトル画面の背景
	TEXTURE_TITLE_LOGO,		// タイトルロゴ
	TEXTURE_TUTORIAL,		// チュートリアル画面

	//ゲーム画面
	TEXTURE_GAME_BG,		// ゲーム画面の背景
	TEXTURE_BOM,			//爆弾
	TEXTURE_BALLOONBOM,		//風船付き爆弾
	TEXTURE_FLOWER,			//花
	TEXTURE_FOX_UFO,		//UFO in きつね
	TEXTURE_LIGHT_BRIGHT,	//明るい街灯
	TEXTURE_LIGHT_DARK,		//暗い街灯
	TEXTURE_1t,				//1t
	TEXTURE_3t,				//3t


	//リザルト画面
	TEXTURE_RESULT_BG,		// リザルト画面の背景
	TEXTURE_GAMEOVER,		// ゲームオーバー画面の背景

	/*↓ エフェクト ↓*/
	TEXTURE_Effect_fire,	// 炎のエフェクト
	TEXTURE_Effect_spin,	// ディスクのエフェクト
	TEXTURE_Effect_tackle,	// タックルのエフェクト
	TEXTURE_Effect_goal,	// ゴールのエフェクト
	TEXTURE_Effect_spark,	// 壁のエフェクト

	TEXTURE_MAX,
	TEXTURE_NONE,
}TEXTURE;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void LoadTexture(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTexture(void);

//--------------------------------------------------
// 取得
// 引数  : TEXTURE texture / 列挙型 種類
// 返値  : LPDIRECT3DTEXTURE9 / テクスチャ
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture);

#endif // !_TEXTURE_H_
