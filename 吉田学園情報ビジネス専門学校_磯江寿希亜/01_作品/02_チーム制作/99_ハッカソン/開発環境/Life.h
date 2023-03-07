//**************************************************
//
// 制作 ( ライフ )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

#define MAX_Life	(8)	//ライフの最大数

typedef struct
{
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 pos;			//位置
	D3DXCOLOR col;

	int nLife;					//体力
	bool bUse;					//使用してるかどうか	
}Life;


//プロトタイプ宣言
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

Life *GetLife(void);

void SetLife(D3DXVECTOR3 pos, D3DXCOLOR col);
void HitLife(int nDamage, int number);

#endif