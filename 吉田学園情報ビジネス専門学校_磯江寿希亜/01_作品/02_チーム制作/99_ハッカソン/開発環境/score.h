//**************************************************
//
// ���� ( �X�R�A )
// Author  : 
//
//**************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�}�N����`
#define NUM_SCORE (6)		//����
#define SCORE_SIZE 20
#define RESULT_SCORE	(45.0f)		//���U���g�ł̃X�R�A�̑傫��
#define RESULT_SCOREX	(80.0f)		//���U���g��X���ǂꂭ�炢���炷��

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValse);
void SubScore(int nValse);
int GetScore(void);

#endif