//**************************************************
//
// 制作 ( スコア )
// Author  : 
//
//**************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//マクロ定義
#define NUM_SCORE (6)		//桁数
#define SCORE_SIZE 20
#define RESULT_SCORE	(45.0f)		//リザルトでのスコアの大きさ
#define RESULT_SCOREX	(80.0f)		//リザルトでX軸どれくらいずらすか

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValse);
void SubScore(int nValse);
int GetScore(void);

#endif