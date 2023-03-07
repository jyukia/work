//**************************************************
//
// ���� ( ���C�t )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

#define MAX_Life	(8)	//���C�t�̍ő吔

typedef struct
{
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 pos;			//�ʒu
	D3DXCOLOR col;

	int nLife;					//�̗�
	bool bUse;					//�g�p���Ă邩�ǂ���	
}Life;


//�v���g�^�C�v�錾
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

Life *GetLife(void);

void SetLife(D3DXVECTOR3 pos, D3DXCOLOR col);
void HitLife(int nDamage, int number);

#endif