//**************************************************
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//**************************************************
#include <stdio.h>
#include "ranking.h"
#include "score.h"
#include "main.h"
#include "fade.h"
#include "input.h"
#include"sound.h"

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
	bool hikari;
}RankScore;

//�O���[�o���ϐ�
static LPDIRECT3DTEXTURE9 s_pTextureRank = NULL;			//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureRankScore = NULL;		//�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureRankBG = NULL;		    //�e�N�X�`���ւ̃|�C���^

static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRank = NULL;		//���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffRankBG2 = NULL;	//���_�o�b�t�@�ւ̃|�C���^��-�����L���O�݂₭������

static RankScore s_aRankScore[MAX_RANK];	//�����L���O�X�R�A���
static int s_nRankUpdate = -1;				//�X�V�����NNo.
static int s_nTimerRanking;				//�����L���O��ʕ\���^�C�}�[
static int nTimesekand;                    //��ڂ̃^�C�}�[
static bool nTimesekand2;					//�^�C�}�[
static D3DXCOLOR nTimecol;	                //�F

//==============
//����������
//==============
void InitRanking(void)
{


	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	int nCntRank;
	int nCntScore;
	nTimesekand2 = false;
	s_nTimerRanking = 0;
	nTimesekand = 0;
	nTimecol = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/ranking_rank1.png",
		&s_pTextureRank);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/score.png",
		&s_pTextureRankScore);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/yoru2.png",
		&s_pTextureRankBG);

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		s_aRankScore[nCntRank].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
		s_aRankScore[nCntRank].hikari = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankScore,
		NULL);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankBG,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuffRankBG2,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = s_aRankScore[nCntRank].pos.x - 50.0f;
		pVtx[0].pos.y = s_aRankScore[nCntRank].pos.y - 50.0f + nCntRank * 100;
		pVtx[0].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[1].pos.x = s_aRankScore[nCntRank].pos.x + 50.0f;
		pVtx[1].pos.y = s_aRankScore[nCntRank].pos.y - 50.0f + nCntRank * 100;
		pVtx[1].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[2].pos.x = s_aRankScore[nCntRank].pos.x - 50.0f;
		pVtx[2].pos.y = s_aRankScore[nCntRank].pos.y + 50.0f + nCntRank * 100;
		pVtx[2].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		pVtx[3].pos.x = s_aRankScore[nCntRank].pos.x + 50.0f;
		pVtx[3].pos.y = s_aRankScore[nCntRank].pos.y + 50.0f + nCntRank * 100;
		pVtx[3].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.2f * nCntRank);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.2f * nCntRank);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.2f + 0.2f * nCntRank);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.2f + 0.2f * nCntRank);

		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRank->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		s_aRankScore[nCntRank].pos.x += 100;	//�X�R�A�\���ꏊ�ֈړ�
		for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{
			pVtx[0].pos.x = s_aRankScore[nCntRank].pos.x - 30.0f + nCntScore * 50;
			pVtx[0].pos.y = s_aRankScore[nCntRank].pos.y - 30.0f + nCntRank * 100;
			pVtx[0].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[1].pos.x = s_aRankScore[nCntRank].pos.x + 30.0f + nCntScore * 50;
			pVtx[1].pos.y = s_aRankScore[nCntRank].pos.y - 30.0f + nCntRank * 100;
			pVtx[1].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[2].pos.x = s_aRankScore[nCntRank].pos.x - 30.0f + nCntScore * 50;
			pVtx[2].pos.y = s_aRankScore[nCntRank].pos.y + 30.0f + nCntRank * 100;
			pVtx[2].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

			pVtx[3].pos.x = s_aRankScore[nCntRank].pos.x + 30.0f + nCntScore * 50;
			pVtx[3].pos.y = s_aRankScore[nCntRank].pos.y + 30.0f + nCntRank * 100;
			pVtx[3].pos.z = s_aRankScore[nCntRank].pos.z + 0.0f;

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;

		}
	}
	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRankScore->Unlock();
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffRankBG2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(600.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(600.0f, 550.0f, 0.0f);

	//RHW�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 255, 200);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRankBG2->Unlock();

	s_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//RHW�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRankBG->Unlock();
	//�T�E���h�J�n
	PlaySound(SOUND_LABEL_BGM001);
}

//=========================================
//�����L���O�̏I������
//=========================================
void UninitRanking(void)
{
	//�T�E���h��~
	StopSound();
	//�e�N�X�`���̔j��
	if (s_pTextureRank != NULL)
	{
		s_pTextureRank->Release();
		s_pTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffRank != NULL)
	{
		s_pVtxBuffRank->Release();
		s_pVtxBuffRank = NULL;
	}
	//�e�N�X�`���̔j��
	if (s_pTextureRankBG != NULL)
	{
		s_pTextureRankBG->Release();
		s_pTextureRankBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffRankBG != NULL)
	{
		s_pVtxBuffRankBG->Release();
		s_pVtxBuffRankBG = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffRankBG2 != NULL)
	{
		s_pVtxBuffRankBG2->Release();
		s_pVtxBuffRankBG2 = NULL;
	}

	//�e�N�X�`���̔j��
	if (s_pTextureRankScore != NULL)
	{
		s_pTextureRankScore->Release();
		s_pTextureRankScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffRankScore != NULL)
	{
		s_pVtxBuffRankScore->Release();
		s_pVtxBuffRankScore = NULL;
	}
}

//============
//�X�V����
//============
void UpdateRanking(void)
{//�����������������鏈��
	int nCntRank01;
	nTimesekand++;
	if (nTimesekand == 1)
	{
		nTimesekand2 = false;
	}
	if (nTimesekand == 31)
	{
		nTimesekand2 = true;
	}
	if (nTimesekand == 61)
	{
		nTimesekand = 0;

	}
	for (nCntRank01 = 0; nCntRank01 < MAX_RANK; nCntRank01++)
	{
		if (nTimesekand2 == false)
		{
			nTimecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (nTimesekand2 == true)
		{
			nTimecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		}
	}


	int nCntRank;
	int nCntScore;
	VERTEX_2D *pVtx;
	//���b�N
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (s_aRankScore[nCntRank].hikari)
		{
			for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(nTimecol);
				pVtx[1].col = D3DXCOLOR(nTimecol);
				pVtx[2].col = D3DXCOLOR(nTimecol);
				pVtx[3].col = D3DXCOLOR(nTimecol);
				pVtx += 4;

			}
		}
		else
		{
			for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx += 4;

			}
		}

	}
	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRankScore->Unlock();
	FADE pFade;
	pFade = GetFade();
	s_nTimerRanking++;
	if (s_nTimerRanking == 1200)
	{
		SetFade(MODE_TITLE);
	}
	if ((GetKeyboardTrigger(DIK_RETURN) == true ||
		GetKeyboardTrigger(JOYKEY_START) == true ||
		GetKeyboardTrigger(JOYKEY_A) == true) && pFade == FADE_NONE)
	{//�G���^�[�������ꂽ�Ƃ�
		//PlaySound(SOUND_LABEL_SE_KIRA);
		SetFade(MODE_TITLE);
	}
}

//==========
//�`�揈��
//==========
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;
	int nCntScore;

	//=================================================
	//	���_�t�H�[�}�b�g�̐ݒ�t�H�[�}�b�g�Ȃǂ�
	//	���ꂼ��ŕK�v�ł�
	//�@��������������Y�ꂸ��
	//=================================================
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`��
	pDevice->SetTexture(0, s_pTextureRankBG);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffRankBG2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);



	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, s_pTextureRank);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);
	}

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//����
		for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
		{//�X�R�A
		 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTextureRankScore);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntRank * 4 * NUM_SCORE) + (nCntScore * 4), 2);
		}
	}


}

//==========
//���Z�b�g
//==========
void ResetRanking(void)
{
	FILE *pFile;	//�t�@�C���|�C���^��錾
	int nCntRank;

	s_nRankUpdate = -1;	//�X�V�����N������

						//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//�����L���O�̓ǂݍ���
			fscanf(pFile, "%d", &s_aRankScore[nCntRank].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		FADE pFade = GetFade();		//���̃t�F�[�h

		if (pFade == FADE_NONE)
		{//�������Ă��Ȃ���ԂȂ�
		 //�t�F�[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}
}

//=======
//�Z�[�u
//======
void SaveRanking(void)
{
	FILE *pFile;	//�t�@�C���|�C���^��錾
	int nCntRank;

	s_nRankUpdate = -1;	//�X�V�����NNo.�̏�����

						//�t�@�C�����J��
	pFile = fopen(FILE_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//�����L���O�̏�������
			fprintf(pFile, "%d\n", s_aRankScore[nCntRank].nScore);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		FADE pFade = GetFade();		//���̃t�F�[�h

		if (pFade == FADE_NONE)
		{//�������Ă��Ȃ���ԂȂ�
		 //�t�F�[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}

}

//=====================
//�����L���O�̐ݒ菈��
//======================
void SetRanking(int nScore)
{
	VERTEX_2D *pVtx;
	int nCntRank;
	int nCnt2Rank;
	int nCheckDataMin;

	//�����L���O�̍ŉ��ʂƍ���̃X�R�A���ׂ�
	if (nScore >= s_aRankScore[MAX_RANK - 1].nScore)
	{
		s_nRankUpdate = 5;
		//��r�������l������B
		s_aRankScore[MAX_RANK - 1].nScore = nScore;
	}

	for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
	{
		for (nCnt2Rank = nCntRank + 1; nCnt2Rank < MAX_RANK; nCnt2Rank++)
		{
			if (s_aRankScore[nCntRank].nScore <= s_aRankScore[nCnt2Rank].nScore)
			{

				nCheckDataMin = s_aRankScore[nCnt2Rank].nScore;
				s_aRankScore[nCnt2Rank].nScore = s_aRankScore[nCntRank].nScore;
				s_aRankScore[nCntRank].nScore = nCheckDataMin;
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		int aPosTexU[6];

		aPosTexU[0] = s_aRankScore[nCntRank].nScore % 1000000 / 100000;
		aPosTexU[1] = s_aRankScore[nCntRank].nScore % 100000 / 10000;
		aPosTexU[2] = s_aRankScore[nCntRank].nScore % 10000 / 1000;
		aPosTexU[3] = s_aRankScore[nCntRank].nScore % 1000 / 100;
		aPosTexU[4] = s_aRankScore[nCntRank].nScore % 100 / 10;
		aPosTexU[5] = s_aRankScore[nCntRank].nScore % 10 / 1;

		for (nCnt2Rank = 0; nCnt2Rank < NUM_SCORE; nCnt2Rank++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCnt2Rank], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCnt2Rank], 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.1f * aPosTexU[nCnt2Rank], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aPosTexU[nCnt2Rank], 1.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx += 4;
		}
	}

	SaveRanking();

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuffRankScore->Unlock();
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (s_aRankScore[nCntRank].nScore == nScore)
		{

			s_aRankScore[nCntRank].hikari = true;

		}
	}
}