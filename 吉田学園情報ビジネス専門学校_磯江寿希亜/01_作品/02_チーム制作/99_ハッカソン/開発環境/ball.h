
#ifndef _BALL_H_
#define _BALL_H_

#include"main.h"

#define	MAX_BALL	(256)
#define	MAX_RECIPE	(5)

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nLife;			//寿命
	bool bUse;		//使用してるかどうか
	int Trigger;   //種類
	int nType;
	int kill;
	float fSiz; //サイズ
	int Move2;
	bool moveset;
	bool moveOn;

}Ball;

//プロトタイプ宣言
void InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);
int SetBall(D3DXVECTOR3 pos,int nLife, int nType, float fSiz);
void MoveBall(D3DXVECTOR3 move,int number);

#endif #pragma once
