//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include"DebugProc.h"
#include "application.h"
#include "renderer.h"

LPD3DXFONT CDebugProc::m_pFont = nullptr;			// フォント情報
TCHAR CDebugProc::m_aStr[0xfff] = {};				// 登録文字列

void CDebugProc::Print(const char *pFormat, ...)
{
	// 変数
	char aStrCpy[0xfff] = {};

	// リストの作成
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
{// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Getinstnce()->GetRenderer()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
}

void CDebugProc::Uninit()
{
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, 1280, 720 };

	// テキスト描画
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	m_aStr[0] = '\0';
}