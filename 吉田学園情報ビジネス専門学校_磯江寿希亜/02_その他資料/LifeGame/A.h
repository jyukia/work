#ifndef _A_H_
#define _A_H_

//背景構造体の定義
typedef struct
{
	int nCounterAnim;	//カウンター
	int nPatternAnim;	//パターン番号
}A;

//プロトタイプ宣言
void InitA(void);
void MoveA(int count, int count2);
void UpdateA(void);
void DrawA(void);

#endif