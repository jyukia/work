
#ifndef _COMBO_H_
#define _COMBO_H_

#include"main.h"

#define	MAX_COMBO	(256)
#define	MAX_RECIPE	(5)

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		 //�J���[
	int nMaxLife;		//���C�t�̍ő�
	int nLife;			//����
	bool bUse;		//�g�p���Ă邩�ǂ���
	int Trigger;   //���
	int nType;
	int kill;
	float fSiz; //�T�C�Y
	int Move2;
	bool moveset;
	bool moveOn;

}Combo;

//�v���g�^�C�v�錾
void InitCombo(void);
void UninitCombo(void);
void UpdateCombo(void);
void DrawCombo(void);
void SetCombo(D3DXVECTOR3 pos, int nLife, int nType, float fSiz, int number);

#endif
