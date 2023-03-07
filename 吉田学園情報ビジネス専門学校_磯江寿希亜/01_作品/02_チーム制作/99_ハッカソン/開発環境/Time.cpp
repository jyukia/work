//**************************************************
//
// ���� ( timer )
// Author  :
//
//**************************************************
#include"Time.h"
#include"game.h"
#include"fade.h"

static LPDIRECT3DTEXTURE9 s_pTextureTimer = NULL; //�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffTimer= NULL; //���_�o�b�t�@�̐ݒ�

static D3DXVECTOR3 s_pos; //�X�R�A�̈ʒu	
static int s_nTimer,nCut;

//===================
//����������
//===================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntTimer;
	s_nTimer = 0;
	nCut=0;

	s_pos = D3DXVECTOR3(1010.0f, 50.0f, 0.0f);				//�ʒu�ݒ�		�^�C������

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAME\\number001.png",
		&s_pTextureTimer);

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,//�������_�t�H�[�}�b�g
		&s_pVtxBuffTimer,
		NULL);

//-------------------------------------------------------------------------------------------


	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);	
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{

		//���_���W
		SetNorotpos(pVtx,
			s_pos.x - 30,
			s_pos.x + 30,
			s_pos.y - 30,
			s_pos.y + 30);

		s_pos += D3DXVECTOR3(54.0f, 0.0f, 0.0f);		//�^�C���̊��o
		if (nCntTimer == 2)
		{
			s_pos += D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_�̃^�C��
		}
		//RHW�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		
		//�e�N�X�`���̍��W�ݒ�
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffTimer->Unlock();

	SetTimer(90);			//30�b
}

//===================
//�j������
//===================
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	if (s_pTextureTimer != NULL)
	{
		s_pTextureTimer->Release();
		s_pTextureTimer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffTimer != NULL)
	{
		s_pVtxBuffTimer->Release();
		s_pVtxBuffTimer = NULL;
	}
}

//===================
//�X�V����
//===================
void UpdateTimer(void)
{
	bool bUse = false;

	if (nCut == 120)
	{
		AddTimer(-1);
		nCut = 0;
	}

	nCut++;

	//if (s_nTimer != 0)
	//{
	//	AddTimer(-1);		
	//}
		
}

//===================
//�`�揈��
//===================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	int nCntTimer;

	pDevice = GetDevice();		//���

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTextureTimer);

	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			nCntTimer * 4,
			2);
	}
	
}

//===================
//�Z�b�g
//===================
void SetTimer(int nTimer)
{
	int nCntTimer;
	int aPosTexU[MAX_TIMER]; //�e���̐������i�[

	s_nTimer = nTimer;
	/*aPosTexU[0] = (s_nTimer % 100000) / 10000;
	aPosTexU[1] = (s_nTimer % 10000) / 1000;
	aPosTexU[2] = (s_nTimer % 1000) / 100;*/
	aPosTexU[0] = (s_nTimer % 100) / 10;
	aPosTexU[1] = (s_nTimer % 10) / 1;

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//�e�N�X�`���̍��W�ݒ�
		Settex(pVtx, 0.1f*aPosTexU[nCntTimer], 0.1f*aPosTexU[nCntTimer] + 0.1f, 0.0f, 1.0f);
		pVtx += 4; //���_�|�C���g���l�i��
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffTimer->Unlock();

}

//===================
//���Z
//===================
void AddTimer(int nValue)
{
	int nCntTimer;
	int aPosTexU[MAX_TIMER]; //�e���̐������i�[

	s_nTimer += nValue;


	/*aPosTexU[0] = (s_nTimer % 100000) / 10000;
	aPosTexU[1] = (s_nTimer % 10000) / 1000;
	aPosTexU[2] = (s_nTimer % 1000) / 100;*/
	aPosTexU[0] = (s_nTimer % 100) / 10;
	aPosTexU[1] = (s_nTimer % 10) / 1;

	VERTEX_2D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//�e�N�X�`���̍��W�ݒ�
		Settex(pVtx, 0.1f*aPosTexU[nCntTimer], 0.1f*aPosTexU[nCntTimer] + 0.1f, 0.0f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}
	if (s_nTimer <= 0)
	{
		SetFade(MODE_RESULT);		//�Q�[����ʂɈڍs
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffTimer->Unlock();
}
int GetTimer(void)
{
	return s_nTimer;
}

void SetNorotpos(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	pVtx[0].pos = D3DXVECTOR3(left, top, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(right, top, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(left, down, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(right, down, 0.0f);
}