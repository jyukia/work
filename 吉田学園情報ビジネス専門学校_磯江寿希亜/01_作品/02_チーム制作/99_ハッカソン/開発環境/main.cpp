//============================
//
// �A�N�V�����Q�[�����`
// Author:Teruto Sato
//
//============================

//------------------------
// �C���N���[�h
//------------------------
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "texture.h"
#include "ranking.h"
#include"score.h"
#include "gameover.h"
#include "tutorial.h"

//------------------------
// �}�N����`
//------------------------
#define CLASS_NAME	"WindowClass"	//�E�C���h�E�N���X�̖��O
#define	WINDOW_NAME	"�n�b�J�\��"	//�E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define MAX_NAME (5)

//------------------------
// �v���g�^�C�v�錾
//------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//------------------------
// �O���[�o���ϐ�
//------------------------
LPDIRECT3D9					g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;	//���݂̃��[�h

//========================
// ���C���֐�
//========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInsetancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�̃X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�t�@�C���̃A�C�R��
	};

	HWND hWnd;		//�E�C���h�E�n���h��(���ʎq)
	MSG msg;		//���b�Z�[�W���i�[����ϐ�

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,						//�g���E�C���h�E�X�^�C��
						  CLASS_NAME,				//�E�C���h�E�N���X�̖��O
						  WINDOW_NAME,				//�E�C���h�E�̖��O
						  WS_OVERLAPPEDWINDOW,		//�E�C���h�E�X�^�C��
						  CW_USEDEFAULT,			//�E�C���h�E�̍���X���W
						  CW_USEDEFAULT,			//�E�C���h�E�̍���Y���W
						  SCREEN_WIDTH,				//�E�C���h�E�̕�
						  SCREEN_HEIGHT,			//�E�C���h�E�̍���
						  NULL,						//�e�E�C���h�E�̃n���h��
						  NULL,						//���j���[�n���h���܂��͎q�E�C���h�EID
						  hInstance,				//�C���X�^���X�n���h��
						  NULL);					//�E�C���h�E�쐬�f�[�^

	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//���݂ɏ�����������

	//����������

	if (FAILED(Init(hInstance, hWnd, FALSE)))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();		//���ݎ������擾

			if ((dwCurrentTime - dwExecLastTime) >= (100 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	//����\��߂�
	timeEndPeriod(1);
	Uninit();

	//�E�C���h�E�N���X�̓o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//========================
// ����������
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�Q�[�����(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;		//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;		//�f�v�X�o�b�t�@�ƃX�e���V�o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;					//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V���V�[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h�̏���������
	InitSound(hWnd);

	//�e�N�X�`���̓ǂݍ���
	LoadTexture();

	//���[�h�̐ݒ�
	SetMode(g_mode);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}


//========================
// �I������
//========================
void Uninit(void)
{
	//�^�C�g����ʂ̏I��
	UninitTitle();

	//�Q�[����ʂ̏I��
	UninitGame();

	//���U���g��ʂ̏I��
	UninitResult();

	//�T�E���h�̏I������
	UninitSound();

	//�e�N�X�`���̏I��
	UninitTexture();

	// ���͏����̏I��
	UninitInput();

	UninitTutorial();

	UninitGameOver();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================
// �X�V����
//========================
void Update(void)
{
	// ���͏����̍X�V
	UpdateInput();

	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̍X�V
		UpdateTitle();
		break;
	case MODE_GAME:
		//�Q�[���̍X�V
		UpdateGame();
		break;
	case MODE_RESULT:
		//���U���g�̍X�V
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;
	case MODE_GAMEOVER:
		UpdateGameOver();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//========================
// �`�揈��
//========================
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̎擾

	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		switch (g_mode)
		{
		case MODE_TITLE:
			//�^�C�g���̕`��
			DrawTitle();
			break;
		case MODE_GAME:
			//�Q�[���̕`��
			DrawGame();
			break;
		case MODE_RESULT:
			//���U���g�̕`��
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();
			break;
		case MODE_GAMEOVER:
			DrawGameOver();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();
		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@��Z�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================
// ���[�h�̐ݒ�
//========================
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̏I��
		UninitTitle();
		break;
	case MODE_GAME:
		//�Q�[���̏I������
		UninitGame();
		break;
	case MODE_RESULT:
		//���U���g�̏I������
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;
	case MODE_GAMEOVER:
		UninitGameOver();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	}

	//�V�������[�h�̏�����
	switch (mode)
	{
	case MODE_TITLE:
		//�^�C�g���̏���������
		InitTitle();
		break;
	case MODE_GAME:
		//�Q�[���̏���������
		InitGame();
		break;
	case MODE_RESULT:
		//���U���g�̏���������
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();
		int pScore;
		pScore = GetScore();
		SetRanking(pScore);
		break;
	case MODE_GAMEOVER:
		InitGameOver();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	}

	g_mode = mode;	//���݂̉��(���[�h)��؂�ւ���*/
}

//========================
// ���[�h���擾
//========================
MODE GetMode(void)
{
	return g_mode;
}

//========================
// �E�C���h�E�v���V�[�W��
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//int nID;

	switch (uMsg)
	{
	case WM_DESTROY:		//�E�C���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//ESS�L�[�������ꂽ
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//����̏�����Ԃ�
}

//========================
// �f�o�C�X�̎擾
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void Settex(VERTEX_2D *pVtx, float left, float right, float top, float down)
{
	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}
//---------------------------------------
//�Z�b�g�|�X(2d)
//---------------------------------------
void SetNormalpos(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW)
{
	pVtx[0].pos = D3DXVECTOR3(XUP, YUP, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(XDW, YUP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(XUP, YDW, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(XDW, YDW, 0.0f);
}

