//**************************************************
//
// 制作 ( timer )
// Author  :
//
//**************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

#include"main.h"

#define	MAX_TIMER	(2)

//プロトタイプ宣言
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void SetTimer(int nTimer);
void AddTimer(int nValue);
int GetTimer(void);

void SetNorotpos(VERTEX_2D *pVtx, float left, float right, float top, float down);


#endif
