//=================================
//
// ゲームオーバー画面のヘッダー
// Author:Teruto Sato
//
//=================================
#ifndef _GAMEOVER_H_		//このマクロが定義されてなかったら
#define _GAMEOVER_H_		//2重インクルード防止のマクロ定義

//------------------------
// プロトタイプ宣言
//------------------------
void InitGameOver(void);
void UninitGameOver(void);
void UpdateGameOver(void);
void DrawGameOver(void);

#endif