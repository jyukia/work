//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// ゲーム
	SOUND_LABEL_BGM001,			// タイトル
	SOUND_LABEL_BGM002,			// リザルト
	SOUND_LABEL_BGM003,			// まけまけ
	SOUND_LABEL_BGM004,			// チュートリアル
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_NEXT,		// 決定音
	SOUND_LABEL_SE_EXP,		// 敵の爆発
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
