//================================
//
// combo�̐ݒ�
// Author:Teruto Sato
//
//================================

#include "combo.h"
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"

#define	NUR_COMBO	(1)

//�O���[�o���֐�
static LPDIRECT3DTEXTURE9 g_pTextureCombo[NUR_COMBO] = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCombo = NULL; //���_�o�b�t�@�̐ݒ�
static Combo g_aCombo[MAX_COMBO];
static float coleff;//�G�t�F�N�g�̐F
static float coleff2;//�G�t�F�N�g�̐F

 //==================
 //���܂̏������ݒ�
 //==================
void InitCombo(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntCombo;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/RESULT/score.png",
		&g_pTextureCombo[0]);

	coleff = 1.0f;
	coleff2 = 0.0f;

	//������
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		g_aCombo[nCntCombo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|�X
		g_aCombo[nCntCombo].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���[�u
		g_aCombo[nCntCombo].nLife = 0;//���C�t
		g_aCombo[nCntCombo].bUse = false;//�g���Ă邩
		g_aCombo[nCntCombo].moveset = false;
		g_aCombo[nCntCombo].moveOn = false;
		g_aCombo[nCntCombo].Trigger = 0;   //���
		g_aCombo[nCntCombo].nType = 0;//�^�C�v
		g_aCombo[nCntCombo].fSiz = 0.0f; //�T�C�Y
		g_aCombo[nCntCombo].Move2 = 0;

	}

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_COMBO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//�������_�t�H�[�}�b�g
		&g_pVtxBuffCombo,
		NULL);

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);


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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCombo->Unlock();

}

//==================
//�I������
//==================
void UninitCombo(void)
{
	int nCntCombo;
	for (nCntCombo = 0; nCntCombo < NUR_COMBO; nCntCombo++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCombo[nCntCombo] != NULL)
		{
			g_pTextureCombo[nCntCombo]->Release();
			g_pTextureCombo[nCntCombo] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCombo != NULL)
	{
		g_pVtxBuffCombo->Release();
		g_pVtxBuffCombo = NULL;
	}

}

//==================
//�X�V����
//==================
void UpdateCombo(void)
{
	int nCntCombo;
	

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{


		g_aCombo[nCntCombo].nLife--;
		//�ʒu�X�V
		g_aCombo[nCntCombo].pos += g_aCombo[nCntCombo].move;
		g_aCombo[nCntCombo].moveset = true;

		g_aCombo[nCntCombo].col.a -= 1.0f / g_aCombo[nCntCombo].nMaxLife;

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y - g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + g_aCombo[nCntCombo].fSiz, g_aCombo[nCntCombo].pos.y + g_aCombo[nCntCombo].fSiz, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aCombo[nCntCombo].col;
		pVtx[1].col = g_aCombo[nCntCombo].col;
		pVtx[2].col = g_aCombo[nCntCombo].col;
		pVtx[3].col = g_aCombo[nCntCombo].col;

		if (g_aCombo[nCntCombo].nLife == 0)
		{

			g_aCombo[nCntCombo].bUse = false;

		}
		pVtx += 4;//���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCombo->Unlock();
}

//==================
//�e�̕`�揈��
//==================
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntCombo;

	pDevice = GetDevice();		//���

								//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCombo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCombo[g_aCombo[nCntCombo].nType]);

		if (g_aCombo[nCntCombo].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntCombo * 4,
				2);
		}
	}
}

//==================
//�e�̐ݒ�
//==================
void SetCombo(D3DXVECTOR3 pos, int nLife, int nType, float fSiz,int number)
{
	int nCntCombo;
	float X = 0.1f;
	VERTEX_2D*pVtx; //���_�ւ̃|�C���^

					//���b�N
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		if (g_aCombo[nCntCombo].bUse == false)
		{
			//�e���g�p����ĂȂ��ꍇ
			g_aCombo[nCntCombo].pos.x = pos.x;
			g_aCombo[nCntCombo].pos.y = pos.y;
			g_aCombo[nCntCombo].pos.z = pos.z;
			g_aCombo[nCntCombo].kill = 0;
			g_aCombo[nCntCombo].fSiz = fSiz;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - fSiz, g_aCombo[nCntCombo].pos.y - fSiz, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + fSiz, g_aCombo[nCntCombo].pos.y - fSiz, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - fSiz, g_aCombo[nCntCombo].pos.y + fSiz, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + fSiz, g_aCombo[nCntCombo].pos.y + fSiz, 0.0f);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(X*number, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(X*number+ X, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(X*number, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(X*number+ X, 1.0f);

			g_aCombo[nCntCombo].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aCombo[nCntCombo].nLife = nLife;
			g_aCombo[nCntCombo].nMaxLife = nLife;
			g_aCombo[nCntCombo].bUse = true;
			g_aCombo[nCntCombo].nType = nType;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCombo->Unlock();

}


