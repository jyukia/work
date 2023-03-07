//============================
//
// �G�̏���
// Author:Teruto Sato
//
//============================

//------------------------
// �C���N���[�h
//------------------------
#include "enemy.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "texture.h"
#include "Life.h"

#include <stdlib.h>
#include <time.h>


//------------------------
// �X�^�e�B�b�N�ϐ�
//------------------------
static	TEXTURE		s_pTexture[MAX_TEXTURE];				//�e�N�X�`���ւ̃|�C���^
static	LPDIRECT3DVERTEXBUFFER9		s_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
static Life *pLife = GetLife();		//���C�t���̎擾

//�\����
static	Enemy s_Enemy[MAX_ENEMY];					//�G�̍\����

//�l
static float s_fLength = sqrtf((WIDTH * WIDTH) + (HEIGHT * HEIGHT));	//�Ίp���̒������Z�o����
static float s_fRareLength = sqrtf((RARE_WIDTH * RARE_WIDTH) + (RARE_HEIGHT * RARE_HEIGHT));	//�Ίp���̒������Z�o����
static float s_fAngle = atan2f(WIDTH, HEIGHT);		//�Ίp���̊p�x���Z�o
static float fAngle;	//�p�x

//========================
// �G�̏���������
//========================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̎擾

	//------------------------
	// �e�N�X�`���̓ǂݍ���
	//------------------------
	s_pTexture[0] = TEXTURE_1t;
	s_pTexture[1] = TEXTURE_3t;
	s_pTexture[2] = TEXTURE_FOX_UFO;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&s_pVtxBuff,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// �G�̍\���̂̏�����
	//------------------------
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		enemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		enemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		enemy->nPlace = 0;		//�o���ꏊ
		enemy->bUse = false;	//�g�p���Ă��邩
	}

	//------------------------
	// �����_���Ȓl�̐���
	//------------------------
	//���������Ƃɂ��������_���Ȓl�𐶐�
	srand((unsigned int)time(NULL));

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		if (enemy->nType == 0 || enemy->nType == 1)
		{
			int nMax = (int)(SCREEN_WIDTH - (WIDTH * 4));	//�ő�l
			int nMin = (int)(WIDTH * 4);					//�ŏ��l

			enemy->nPlace = rand() % nMax + nMin;	//�G�̏o���ꏊ�̐ݒ�
		}
		else if (enemy->nType == 2)
		{
			int nMax = (int)(SCREEN_WIDTH - (WIDTH * 2));	//�ő�l
			int nMin = 1000;								//�ŏ��l

			enemy->nPlace = rand() % nMax + nMin;	//�G�̏o���ꏊ�̐ݒ�
		}
	}

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		//���_���W�̐ݒ�
		pVtx[0].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
		pVtx[0].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
		pVtx[1].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
		pVtx[2].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
		pVtx[3].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_BGM002);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//========================
// �G�̏I������
//========================
void UninitEnemy(void)
{
	//�T�E���h�̒�~
	//StopSound();

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//========================
// �G�̍X�V����
//========================
void UpdateEnemy(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		if (enemy->bUse == true)
		{//�G���g�p����Ă���Ȃ�

			if (enemy->nType == 0 || enemy->nType == 1)
			{//���D
				//------------------------
				// �G�̐i�s�����̉�]
				//------------------------
				fAngle += ADD_ANGLE;

				enemy->pos.x += sinf(fAngle + D3DX_PI * 0.5f) * 3.0f;
			}
			else if (enemy->nType == 2)
			{//����
				enemy->pos.x -= 2.0f;
			}

			//------------------------
			// ��ʒ[�̏���
			//------------------------
			if (enemy->pos.y - HEIGHT >= SCREEN_HEIGHT
				|| enemy->pos.x + WIDTH <= 0.0f
				|| enemy->pos.x - WIDTH >= SCREEN_WIDTH)
			{//�G���n�ʂ̉��ɍs����
				enemy->bUse = false;	//�G������
			}

			//�ʒu�̍X�V
			enemy->pos += enemy->move;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
			pVtx[0].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
			pVtx[1].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
			pVtx[2].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
			pVtx[3].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//========================
// �G�̕`�揈��
//========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//----------------
	// �G�̕`��
	//----------------
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		if (enemy->bUse == true)
		{//�G���g�p����Ă���Ȃ�
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, GetTexture(s_pTexture[enemy->nType]));

			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCnt * 4,				//�`�悷��ŏ��̒��_�C���f�b�N�X
								   2);						//�`�悷��v���~�e�B�u��
		}
	}
}

//========================
// �G�̐ݒ菈��
//========================
void SetEnemy(int nType)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		Enemy *enemy = s_Enemy + nCnt;

		if (enemy->bUse == false)
		{//�G���g�p����Ă��Ȃ��Ȃ�
			enemy->nType = nType;

			if (enemy->nType == 0)
			{
				enemy->pos = D3DXVECTOR3((float)enemy->nPlace, 0.0f - HEIGHT, 0.0f);		//�ʒu
				enemy->move = D3DXVECTOR3(0.0f, FALL_SPEED, 0.0f);	//�ړ���
			}
			else if (enemy->nType == 1)
			{
				enemy->pos = D3DXVECTOR3((float)enemy->nPlace, 0.0f - HEIGHT, 0.0f);		//�ʒu
				enemy->move = D3DXVECTOR3(0.0f, FALL_SPEED * 2.0f, 0.0f);	//�ړ���
			}
			else if (enemy->nType == 2)
			{
				enemy->pos = D3DXVECTOR3(1000.0f,0.0f - HEIGHT, 0.0f);		//�ʒu
				enemy->move = D3DXVECTOR3(0.0f, FALL_SPEED * 2.0f, 0.0f);	//�ړ���
			}
			enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
			enemy->bUse = true;		//�g�p���Ă��邩

			//���_���W�̐ݒ�
			pVtx[0].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
			pVtx[0].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = enemy->pos.x + sinf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
			pVtx[1].pos.y = enemy->pos.y + cosf(enemy->rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
			pVtx[2].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 + s_fAngle)) * s_fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = enemy->pos.x + sinf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
			pVtx[3].pos.y = enemy->pos.y + cosf(enemy->rot.z - (0 - s_fAngle)) * s_fLength;
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//========================
// �G���̎擾
//========================
Enemy *GetEnemy(int a)
{
	return &s_Enemy[a];
}