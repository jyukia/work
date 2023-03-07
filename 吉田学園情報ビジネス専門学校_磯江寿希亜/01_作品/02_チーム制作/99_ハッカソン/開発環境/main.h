//============================
//
// メインヘッダー
// Author:Teruto Sato
//
//============================
#ifndef _MAIN_H_	//このマクロが定義されてなかったら
#define _MAIN_H_	//2重インクルード防止のマクロ定義

#include <windows.h>
#include "d3dx9.h"		//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)		//ビルド時の警告対処用マクロ
#include "dinput.h"		//入力処理に必要
#include "Xinput.h"		//ジョイパッド処理に必要
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント(部品)に使用
#pragma comment(lib,"winmm.lib")	//システム時刻取得時に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要

//マクロ定義
#define	SCREEN_WIDTH	(1280)		//ウインドウの幅
#define	SCREEN_HEIGHT	(720)		//ウインドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,		//タイトル画面
	MODE_GAME,			//ゲーム画面
	MODE_RESULT,		//リザルト画面
	MODE_FADE,			//フェード画面
	MODE_RANKING,		//ランキング画面
	MODE_GAMEOVER,
	MODE_TUTORIAL,
	MODE_MAX
}MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9	GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);



//頂点情報構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換用係数(1.0fで固定)
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャへのポインタ
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャへのポインタ
}VERTEX_3D;


void SetNormalpos(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW);
void Settex(VERTEX_2D *pVtx, float left, float right, float top, float down);
#endif