//================================
//
// �ʂ̐ݒ�
// Author:hamada ryuuga
//
//================================

#include "ball.h"
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "combo.h"
#include "sound.h"

#define	NUR_BALL	(1)

//�O���[�o���֐�
static LPDIRECT3DTEXTURE9 g_pTextureBall[NUR_BALL] = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL; //���_�o�b�t�@�̐ݒ�
static Ball g_aBall[MAX_BALL];
static float coleff;//�G�t�F�N�g�̐F
static float coleff2;//�G�t�F�N�g�̐F

//==================
//���܂̏������ݒ�
//==================
void InitBall(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntBall;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/49-4.png",
		&g_pTextureBall[0]);

	coleff = 1.0f;
	coleff2 = 0.0f;

	//������
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		g_aBall[nCntBall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|�X
		g_aBall[nCntBall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���[�u
		g_aBall[nCntBall].nLife = 0;//���C�t
		g_aBall[nCntBall].bUse = false;//�g���Ă邩
		g_aBall[nCntBall].moveset = false;
		g_aBall[nCntBall].moveOn = false;
		g_aBall[nCntBall].Trigger = 0;   //���
		g_aBall[nCntBall].nType = 0;//�^�C�v
		g_aBall[nCntBall].fSiz = 0.0f; //�T�C�Y
		g_aBall[nCntBall].Move2 = 0;

	}

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//�������_�t�H�[�}�b�g
		&g_pVtxBuffBall,
		NULL);

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);


		//RHW�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBall->Unlock();

}

//==================
//�I������
//==================
void UninitBall(void)
{
	StopSound();

	int nCntBall;
	for (nCntBall = 0; nCntBall < NUR_BALL; nCntBall++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBall[nCntBall] != NULL)
		{
			g_pTextureBall[nCntBall]->Release();
			g_pTextureBall[nCntBall] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}

}

//==================
//�X�V����
//==================
void UpdateBall(void)
{
	int nCntBall;
	//�G���W���V�X�e��
	coleff2 += 0.1f;
	if (coleff2 >= 1.0f)
	{
		coleff2 = 0.0f;
	}
	
	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{

		if (g_aBall[nCntBall].bUse)
		{
			
		
			if (GetMousePress(MOUSE_INPUT_LEFT)&& !g_aBall[nCntBall].moveset)
			{
				D3DXVECTOR3 length = GetMouse();
				g_aBall[nCntBall].pos = length;
				//���_���W
				pVtx[0].pos = D3DXVECTOR3(length.x - g_aBall[nCntBall].fSiz, length.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(length.x + g_aBall[nCntBall].fSiz, length.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(length.x - g_aBall[nCntBall].fSiz, length.y + g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(length.x + g_aBall[nCntBall].fSiz, length.y + g_aBall[nCntBall].fSiz, 0.0f);
			}
			if (g_aBall[nCntBall].moveOn)
			{
				g_aBall[nCntBall].nLife--;
				//�ʒu�X�V
				g_aBall[nCntBall].pos += g_aBall[nCntBall].move;
				g_aBall[nCntBall].moveset = true;
				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz, g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz, 0.0f);

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					Enemy *pEnemy = GetEnemy(nCntEnemy);
					if (!pEnemy->bUse)
					{
						continue;
					}
					if (g_aBall[nCntBall].pos.x + g_aBall[nCntBall].fSiz >= pEnemy->pos.x- WIDTH
						&& g_aBall[nCntBall].pos.x - g_aBall[nCntBall].fSiz <= pEnemy->pos.x+ WIDTH
						&& g_aBall[nCntBall].pos.y + g_aBall[nCntBall].fSiz >= pEnemy->pos.y- HEIGHT
						&& g_aBall[nCntBall].pos.y - g_aBall[nCntBall].fSiz <= pEnemy->pos.y+ HEIGHT)
					{//�e���W�d�Ȃ�

							PlaySound(SOUND_LABEL_SE_EXP);


							g_aBall[nCntBall].kill++;
							SetCombo(pEnemy->pos, 150, 0, 50, g_aBall[nCntBall].kill);
							
							if (pEnemy->nType == 0)
							{
								AddScore(10 * g_aBall[nCntBall].kill);
							}
							if (pEnemy->nType == 1)
							{
								AddScore(30 * g_aBall[nCntBall].kill);
							}
							if (pEnemy->nType == 2)
							{
								AddScore(100 * g_aBall[nCntBall].kill);
							}
							
							pEnemy->bUse = false;
							// �G�t�F�N�g�̐ݒ�
							SetEffect(pEnemy->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTSTATE_GOAL_POINT5, 50, 50.0f, false);
					}

				}
			}
			if (g_aBall[nCntBall].nLife == 0)
			{

				g_aBall[nCntBall].bUse = false;

			}

		}
			pVtx += 4;//���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBall->Unlock();
}

//==================
//�e�̕`�揈��
//==================
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntBall;

	pDevice = GetDevice();		//���

								//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBall[g_aBall[nCntBall].nType]);

		if (g_aBall[nCntBall].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntBall * 4,
				2);
		}
	}
}

//==================
//�e�̐ݒ�
//==================
int SetBall(D3DXVECTOR3 pos, int nLife, int nType, float fSiz)
{
	int nCntBall;
	VERTEX_2D*pVtx; //���_�ւ̃|�C���^

					//���b�N
	g_pVtxBuffBall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBall = 0; nCntBall < MAX_BALL; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse == false)
		{
			//�e���g�p����ĂȂ��ꍇ
			g_aBall[nCntBall].pos.x = pos.x;
			g_aBall[nCntBall].pos.y = pos.y;
			g_aBall[nCntBall].pos.z = pos.z;
			g_aBall[nCntBall].kill = 0;
			g_aBall[nCntBall].fSiz = fSiz;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - fSiz, g_aBall[nCntBall].pos.y - fSiz, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + fSiz, g_aBall[nCntBall].pos.y - fSiz, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x - fSiz, g_aBall[nCntBall].pos.y + fSiz, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBall[nCntBall].pos.x + fSiz, g_aBall[nCntBall].pos.y + fSiz, 0.0f);
			g_aBall[nCntBall].nLife = nLife;
			g_aBall[nCntBall].bUse = true;
			g_aBall[nCntBall].moveset = false;
			g_aBall[nCntBall].moveOn = false;
			g_aBall[nCntBall].nType = nType;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBall->Unlock();

	return nCntBall;
}

void MoveBall(D3DXVECTOR3 move, int number)
{		
	g_aBall[number].move = move;
	g_aBall[number].moveOn = true;
}
