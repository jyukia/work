//**************************************************
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _RANKING_H_
#define _RANKING_H_
//------------------------------------
//�}�N����`
//------------------------------------
#define MAX_RANK	(5)	//�����N��
#define MAX_RANKSCORE	(8)	//����
#define FILE_NAME	"data/txt/ranking.txt"

//------------------------------------
//�v���g�^�C�v�錾
//------------------------------------
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SaveRanking(void);
void SetRanking(int nScore);


#endif 