//**************************************************
// 
// FPG���� ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �񋓌^
//==================================================
typedef enum
{
	//�^�C�g�����
	TEXTURE_TITLE_BG,		// �^�C�g����ʂ̔w�i
	TEXTURE_TITLE_LOGO,		// �^�C�g�����S
	TEXTURE_TUTORIAL,		// �`���[�g���A�����

	//�Q�[�����
	TEXTURE_GAME_BG,		// �Q�[����ʂ̔w�i
	TEXTURE_BOM,			//���e
	TEXTURE_BALLOONBOM,		//���D�t�����e
	TEXTURE_FLOWER,			//��
	TEXTURE_FOX_UFO,		//UFO in ����
	TEXTURE_LIGHT_BRIGHT,	//���邢�X��
	TEXTURE_LIGHT_DARK,		//�Â��X��
	TEXTURE_1t,				//1t
	TEXTURE_3t,				//3t


	//���U���g���
	TEXTURE_RESULT_BG,		// ���U���g��ʂ̔w�i
	TEXTURE_GAMEOVER,		// �Q�[���I�[�o�[��ʂ̔w�i

	/*�� �G�t�F�N�g ��*/
	TEXTURE_Effect_fire,	// ���̃G�t�F�N�g
	TEXTURE_Effect_spin,	// �f�B�X�N�̃G�t�F�N�g
	TEXTURE_Effect_tackle,	// �^�b�N���̃G�t�F�N�g
	TEXTURE_Effect_goal,	// �S�[���̃G�t�F�N�g
	TEXTURE_Effect_spark,	// �ǂ̃G�t�F�N�g

	TEXTURE_MAX,
	TEXTURE_NONE,
}TEXTURE;

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void LoadTexture(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTexture(void);

//--------------------------------------------------
// �擾
// ����  : TEXTURE texture / �񋓌^ ���
// �Ԓl  : LPDIRECT3DTEXTURE9 / �e�N�X�`��
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture);

#endif // !_TEXTURE_H_
