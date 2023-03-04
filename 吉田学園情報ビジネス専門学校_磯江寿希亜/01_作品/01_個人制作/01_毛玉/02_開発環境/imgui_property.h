////**************************************************
//// 
//// imugi_property.h
//// Author  : katsuki mizuki
//// Author  : Yuda Kaito
//// 
////**************************************************
//#ifndef _IMGUI_PROPERTY_H_	// ���̃}�N������`����ĂȂ�������
//#define _IMGUI_PROPERTY_H_	// 2�d�C���N���[�h�h�~�̃}�N����`
//
////==================================================
//// �C���N���[�h
////==================================================
//#include "imgui.h"
//#include <d3dx9.h>
//
////--------------------------------------------------
//// ���͌��m
////--------------------------------------------------
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
////--------------------------------------------------
//// imgui�\���N���X
////--------------------------------------------------
//class CImguiProperty
//{
//private:	// ��`
//	static const char* FontPath;			// �g�p����t�H���g
//	static const float FontSize;			// �t�H���g�T�C�Y
//	static const ImVec4 TitleBarColor;		// �^�C�g���o�[�̐F
//	static const ImVec4 SliderBarColor;		// �X���C�_�[�o�[�̐F
//	static const ImVec4 CheckMarkColor;		// �`�F�b�N�}�[�N�̐F
//	static const ImVec4 ScrollBarColor;		// �X�N���[���o�[�̐F
//	static const ImVec4 HeaderColor;		// �w�b�_�[�̊�{�F
//	static const ImVec4 HeaderHoveredColor;	// �w�b�_�[�Ƀ}�E�X�J�[�\�������킹�����̐F
//	static const ImVec4 HeaderActiveColor;	// �w�b�_�[�N���b�N���̐F
//
//	//static const int	MAX_TEXT;		// �e�L�X�g�̍ő啶����
//	static const char*	WINDOW_NAME;	// �E�C���h�E�̖��O (�L���v�V�����ɕ\��)
//public:
//	CImguiProperty();
//	~CImguiProperty();
//
//	virtual HWND Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
//	virtual void Uninit(HWND hWnd, WNDCLASSEX wcex);
//	virtual bool Update();
//	virtual void Draw();
//
//	char* GetFileName();
//	void SetFileName(char*FileStringData);
//
//protected:
//	// �J���[�p���b�g
//	bool ColorPalette4(const char* label, float col[4]);
//	bool ColorPalette(float color[4], float backup_color[4], ImGuiColorEditFlags flags);
//
//	// �^�̕ϊ�
//	ImVec4 ColorToImVec4(const D3DXCOLOR& color);
//	D3DXCOLOR ImVec4ToColor(const ImVec4& vec);
//
//protected:
//	bool s_window = false;	// �E�C���h�E���g�p���邩�ǂ���
//	bool m_isUpdatePass;
//private:
//	char FileString[MAX_PATH * 256];	// �t�@�C����
//};
//
//#endif // !_IMGUI_PROPERTY_H_
