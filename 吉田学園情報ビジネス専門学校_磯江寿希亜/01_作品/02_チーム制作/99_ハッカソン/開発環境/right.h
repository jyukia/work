//**************************************************
//
// 制作 ( Right )
// Author  : 
//
//**************************************************
#ifndef _RIGHT_H_
#define _RIGHT_H_

#include "main.h"

#define MAX_RIGHT	(8)	//最大数

typedef enum
{
	TYPERIGHT_BOWLING,
	TYPERIGHT_DREAM,
	TYPERIGHT_LOVE,

	TYPERIGHT_MAX,
} TYPERIGHT;

typedef struct
{
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 pos;			//位置
	D3DXCOLOR col;
	TYPERIGHT nType;			//種類

	int nLife;					//体力
	bool bUse;					//使用してるかどうか	
}RIGHT;

//プロトタイプ宣言
void InitRight(void);
void UninitRight(void);
void UpdateRight(void);
void DrawRight(void);

void SetRight(D3DXVECTOR3 pos, D3DXCOLOR col, TYPERIGHT Type, int SIZ_X, int SIZ_Y);

void FalseSet(void);
void TrueSet(void);


#endif