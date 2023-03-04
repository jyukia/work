//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include"DebugProc.h"
#include "application.h"
#include "renderer.h"

LPD3DXFONT CDebugProc::m_pFont = nullptr;			// �t�H���g���
TCHAR CDebugProc::m_aStr[0xfff] = {};				// �o�^������

void CDebugProc::Print(const char *pFormat, ...)
{
	// �ϐ�
	char aStrCpy[0xfff] = {};

	// ���X�g�̍쐬
	va_list args;
	va_start(args, pFormat);
	vsprintf(&aStrCpy[0], pFormat, args);
	va_end(args);

#ifdef _DEBUG
	strcat(&m_aStr[0], &aStrCpy[0]);
#endif // DEBUG
}



CDebugProc::CDebugProc()
{

}

CDebugProc::~CDebugProc()
{

}

void CDebugProc::Init()
{// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
}

void CDebugProc::Uninit()
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, 1280, 720 };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	m_aStr[0] = '\0';
}