#ifndef _A_H_
#define _A_H_

//�w�i�\���̂̒�`
typedef struct
{
	int nCounterAnim;	//�J�E���^�[
	int nPatternAnim;	//�p�^�[���ԍ�
}A;

//�v���g�^�C�v�錾
void InitA(void);
void MoveA(int count, int count2);
void UpdateA(void);
void DrawA(void);

#endif