//**************************************************
// 
// FPG���� ( texture.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

#include <assert.h>

//==================================================
// �萔
//==================================================
namespace
{
const char *s_FileName[] =
{// �e�N�X�`���̃p�X
	//�^�C�g�����
	"data\\TEXTURE\\TITLE\\Title_BG.png",		// �^�C�g����ʂ̔w�i
	"data\\TEXTURE\\TITLE\\Title_Logo.png",		// �^�C�g�����S
	"data\\TEXTURE\\TITLE\\Tutorial.png",		// �`���[�g���A�����

	//�Q�[�����
	"data\\TEXTURE\\GAME\\Game_BG.png",			// �Q�[����ʂ̔w�i
	"data\\TEXTURE\\GAME\\Bom.png",				// ���e
	"data\\TEXTURE\\GAME\\BalloonBom.png",		// ���D�t�����e
	"data\\TEXTURE\\GAME\\Flower.png",			// ��
	"data\\TEXTURE\\GAME\\Fox_UFO.png",			// UFO in ����
	"data\\TEXTURE\\GAME\\Light_Bright.png",	// ���邢�X��
	"data\\TEXTURE\\GAME\\Light_Dark.png",		// �Â��X��
	"data\\TEXTURE\\GAME\\1t.png",				// 1t
	"data\\TEXTURE\\GAME\\3t.png",				// 3t

	//���U���g���
	"data\\TEXTURE\\RESULT\\GameClear.png",		// �Q�[���N���A��ʂ̔w�i
	"data\\TEXTURE\\RESULT\\GameOver.png",		// �Q�[���I�[�o�[��ʂ̔w�i

    /*�� �G�t�F�N�g ��*/
    "data/TEXTURE/EFFECT/fire.png",				// ���̃G�t�F�N�g
    "data/TEXTURE/EFFECT/spin.png",				// �f�B�X�N�̃G�t�F�N�g
    "data/TEXTURE/EFFECT/tackle.png",			// �^�b�N���̃G�t�F�N�g
    "data/TEXTURE/EFFECT/Goal.png",				// �S�[���̃G�t�F�N�g
    "data/TEXTURE/EFFECT/spark.png",			// �ǂ̉Ή�
};
}// namespace�͂����܂�

static_assert(sizeof(s_FileName) / sizeof(s_FileName[0]) == TEXTURE_MAX, "aho");

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];
}// namespace�͂����܂�

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture)
{
	if (texture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return NULL;
	}

	assert(texture >= 0 && texture < TEXTURE_MAX);

	return s_pTexture[texture];
}
