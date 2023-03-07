//============================
//
// �t�F�[�h��ʂ̃w�b�_�[
// Author:Teruto Sato
//
//============================
#ifndef _FADE_H_		//���̃}�N������`����ĂȂ�������
#define _FADE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,	//�������Ă��Ȃ����
	FADE_IN,		//�t�F�[�h�C�����
	FADE_OUT,		//�t�F�[�h�A�E�g���
	FADE_MAX
}FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif