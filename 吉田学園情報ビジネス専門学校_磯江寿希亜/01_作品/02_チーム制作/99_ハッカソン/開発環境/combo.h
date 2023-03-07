
#ifndef _COMBO_H_
#define _COMBO_H_

#include"main.h"

#define	MAX_COMBO	(256)
#define	MAX_RECIPE	(5)

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		 //カラー
	int nMaxLife;		//ライフの最大
	int nLife;			//寿命
	bool bUse;		//使用してるかどうか
	int Trigger;   //種類
	int nType;
	int kill;
	float fSiz; //サイズ
	int Move2;
	bool moveset;
	bool moveOn;

}Combo;

//プロトタイプ宣言
void InitCombo(void);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(D3DXVECTOR3 pos, int nLife, int nType, float fSiz, int number);

#endif
