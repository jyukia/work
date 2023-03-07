//============================
//
// �t�F�[�h���
// Author:Teruto Sato
//
//============================

//------------------------
// �C���N���[�h
//------------------------
#include "fade.h"
#include "input.h"
#include "main.h"

//------------------------
// �X�^�e�B�b�N�ϐ�
//------------------------
static	LPDIRECT3DTEXTURE9			g_pTexture = NULL;		//�e�N�X�`���ւ̃|�C���^
static	LPDIRECT3DVERTEXBUFFER9		g_pVtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
static	FADE g_fade;			//�t�F�[�h�̏��
static	MODE g_modeNext;		//���̉��(���[�h)
static	D3DXCOLOR g_colorFade;	//�|���S��(�t�F�[�h)�̐F

//========================
// �t�F�[�h�̏���������
//========================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuff,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�񋓌^�̏�����
	g_fade = FADE_IN;		//�t�F�[�h�C�����
	g_modeNext = modeNext;	//���̉��(���[�h)��ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�����|���S��(�s����)�ɂ��Ă���

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	//���[�h�̐ݒ�
	SetMode(g_modeNext);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();
}

//========================
// �t�F�[�h�̏I������
//========================
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture != NULL)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//========================
// �t�F�[�h�̍X�V����
//========================
void UpdateFade(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade.a -= 0.08f;	//�|���S���𓧖��ɂ��Ă���

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade.a += 0.08f;	//�|���S����s�����ɂ��Ă���

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�
				SetMode(g_modeNext);
			}
		}
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();
}

//========================
// �t�F�[�h�̕`�揈��
//========================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�t�F�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
						   0,						//�`�悷��ŏ��̒��_�C���f�b�N�X
						   2);						//�`�悷��v���~�e�B�u��
}

//========================
// �t�F�[�h�̐ݒ菈��
//========================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;	//�t�F�[�h�A�E�g��Ԃ�
	g_modeNext = modeNext;	//���̉�ʂ�ݒ�
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//========================
// �t�F�[�h�̎擾
//========================
FADE GetFade(void)
{
	return g_fade;
}
