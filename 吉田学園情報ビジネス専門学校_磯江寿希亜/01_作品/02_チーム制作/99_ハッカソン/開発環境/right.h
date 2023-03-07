//**************************************************
//
// ���� ( Right )
// Author  : 
//
//**************************************************
#ifndef _RIGHT_H_
#define _RIGHT_H_

#include "main.h"

#define MAX_RIGHT	(8)	//�ő吔

typedef enum
{
	TYPERIGHT_BOWLING,
	TYPERIGHT_DREAM,
	TYPERIGHT_LOVE,

	TYPERIGHT_MAX,
} TYPERIGHT;

typedef struct
{
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 pos;			//�ʒu
	D3DXCOLOR col;
	TYPERIGHT nType;			//���

	int nLife;					//�̗�
	bool bUse;					//�g�p���Ă邩�ǂ���	
}RIGHT;

//�v���g�^�C�v�錾
void InitRight(void);
void UninitRight(void);
void UpdateRight(void);
void DrawRight(void);

void SetRight(D3DXVECTOR3 pos, D3DXCOLOR col, TYPERIGHT Type, int SIZ_X, int SIZ_Y);

void FalseSet(void);
void TrueSet(void);


#endif