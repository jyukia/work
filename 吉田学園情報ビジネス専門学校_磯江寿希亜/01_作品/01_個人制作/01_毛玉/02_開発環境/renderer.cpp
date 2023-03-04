//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "application.h"
#include"DebugProc.h"
#include "camera.h"
//#include"stage_imgui.h"
#include"Mapcamera.h"
#include"game.h"
#include"game1.h"
#include"pause.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define WIREFRAME ( 0 )	//0�g�p�Ȃ��@1�g�p

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


#if WIREFRAME
	//���C���[�t���[���̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
#else
#endif

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	//�t�H�O�̐ݒ�
	//SetFog(true, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f));

	//�J�����̐���
	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		m_pCamera[Cnt] = CCamera::Create();	//�v���C���[�J����
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRenderer::Uninit()
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		//�J�����̉���E�폜
		if (m_pCamera[Cnt] != nullptr)
		{
			m_pCamera[Cnt]->Uninit();
			delete m_pCamera[Cnt];
			m_pCamera[Cnt] = nullptr;
		}
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CRenderer::Update()
{
	//�|�[�Y�̏���
	CPause* pPause = CGame::GetPause();

	if (pPause == nullptr)
	{
		for (int Cnt = 0; Cnt < 2; Cnt++)
		{
			//�J�����̍X�V����
			if (m_pCamera[Cnt] != nullptr)
			{
				m_pCamera[Cnt]->Update();
			}
		}
		//�S�ẴI�u�W�F�N�g�̍X�V����
		CObject::UpdateAll();
	}
	else
	{
		if (pPause->GetPauseFlg())
		{
			pPause->Update();
		}
		else
		{
			for (int Cnt = 0; Cnt < 2; Cnt++)
			{
				//�J�����̍X�V����
				if (m_pCamera[Cnt] != nullptr)
				{
					m_pCamera[Cnt]->Update();
				}
			}
			//�S�ẴI�u�W�F�N�g�̍X�V����
			CObject::UpdateAll();
		}
	}

}

//=============================================================================
// �`��
//=============================================================================
void CRenderer::Draw()
{
	for (int Cnt = 0; Cnt < 2; Cnt++)
	{
		if (m_pCamera[Cnt] != nullptr)		//�v���C���[�J����
		{
			if (Cnt == 0)//���C���J����
			{
				if (m_pCamera[0] != nullptr)
				{
					m_pCamera[0]->SetCamera(true, true);		//����1 �J�����ړ�(true �Œ�,false �t���[) ����2 ���e���@(true �ʏ퓊�e,false ���s���e)
				}
				D3DVIEWPORT9 gameview = m_pCamera[0]->GetViewPort();	//�r���[�|�[�g�̐ݒ�

				//�r���[�|�[�g�\���̕ۑ�
				gameview.X = 0;
				gameview.Y = 0;
				gameview.Width = 1280;
				gameview.Height = 720;
				gameview.MaxZ = 1.0f;
				gameview.MinZ = 0.0f;
				m_pCamera[0]->SetViewPort(gameview);

				int mode = CApplication::Getinstnce()->GetMode();
				if (mode == CApplication::MODE_RANKING)
				{
					D3DXVECTOR3 CamV = m_pCamera[0]->GetPosV();
					CamV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);	//�}�b�v�ォ�猩���낷���ߍ��߂ɐݒ�
					m_pCamera[0]->SetPosV(CamV);

					D3DXVECTOR3 Rot = m_pCamera[0]->GetRot();
					Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_pCamera[0]->SetRot(Rot);
				}
				else
				{
					m_pCamera[0]->SetPosV(D3DXVECTOR3(0.0f, 100.0f, -200.0f));	//���̒l������
				}
			}

			if (Cnt == 1)//�}�b�v�J����
			{
				if (m_pCamera[1] != nullptr)
				{
					m_pCamera[1]->SetCamera(true, true);		//����1 �J�����ړ�(true �Œ�,false �t���[) ����2 ���e���@(true �ʏ퓊�e,false ���s���e)
				}
				D3DVIEWPORT9 mapview = m_pCamera[1]->GetViewPort();		//�r���[�|�[�g�̐ݒ�

				if (CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME || CApplication::Getinstnce()->GetMode() == CApplication::MODE_GAME1)
				{
					//�r���[�|�[�g�\���̕ۑ�
					mapview.X = 1020;
					mapview.Y = 25;
					mapview.Width = 240;
					mapview.Height = 200;
					mapview.MaxZ = 1.0f;
					mapview.MinZ = 0.0f;
					m_pCamera[1]->SetViewPort(mapview);

					D3DXVECTOR3 MapCamV = m_pCamera[1]->GetPosV();
					MapCamV = D3DXVECTOR3(0.0f, 500.0f, -10.0f);	//�}�b�v�ォ�猩���낷���ߍ��߂ɐݒ�
					m_pCamera[1]->SetPosV(MapCamV);
				}
				else
				{
					//�r���[�|�[�g�\���̕ۑ�
					mapview.X = 1020;
					mapview.Y = 25;
					mapview.Width = 0;
					mapview.Height = 0;
					mapview.MaxZ = 1.0f;
					mapview.MinZ = 0.0f;
					m_pCamera[1]->SetViewPort(mapview);
				}
			}

		// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		// Direct3D�ɂ��`��̊J�n
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
				//�S�ẴI�u�W�F�N�g�̕`�揈��
				CObject::DrawAll();
#ifdef _DEBUG
				// FPS�\��
				DrawFPS();

				// �f�o�b�N�\��
				CDebugProc::Draw();
#endif // _DEBUG

			}
			//CApplication::Getinstnce()->GetImgui()->Draw();

			// Direct3D�ɂ��`��̏I��
			m_pD3DDevice->EndScene();
		}
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �t�H�O�ݒ菈��
//=============================================================================
void CRenderer::SetFog(bool bFlag, D3DXCOLOR col)
{
	// �t�H�O�̗L���ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, bFlag);

	// �t�H�O�J���[�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, col);

	// �t�H�O���[�h ������(�͈͎w�� : D3DFOG_LINEAR, ���x�w�� : D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	// �͈͎w��(��LINEAR���Ɏw��)
	float fFogStartPos = 100;
	float fFogEndPos = 1000; 
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// ���x�w��(��EXP���Ɏw��)
	float fFogDensity = 0.001f;

	m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}

//=============================================================================
// �f�o�C�X���擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}
#endif // _DEBUG