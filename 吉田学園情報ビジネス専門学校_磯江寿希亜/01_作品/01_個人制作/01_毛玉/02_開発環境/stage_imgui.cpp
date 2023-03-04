////**************************************************
////
//// Hackathon ( imgui_property.cpp )
//// Author  : katsuki mizuki
//// Author  : Tanaka Kouta
//// Author  : Hamada Ryuga
//// Author  : Yuda Kaito
////
//////**************************************************
//
////-----------------------------------------------------------------------------
//// include
////-----------------------------------------------------------------------------
//#include "stage_imgui.h"
//#include"load_stage.h"
////-----------------------------------------------------------------------------
//// imgui
////-----------------------------------------------------------------------------
//#define IMGUI_DEFINE_MATH_OPERATORS
////#include "imgui_internal.h"
////#include <implot.h>
//
////-----------------------------------------------------------------------------
//// json
////-----------------------------------------------------------------------------
//#include <fstream>
//
////-----------------------------------------------------------------------------
//// stage
////-----------------------------------------------------------------------------
//#include "main.h"
//#include "application.h"
//#include "texture.h"
//#include "object.h"
//#include "camera.h"
//#include "meshfield.h"
//
//#include"game.h"
//#include"Player.h"
////-----------------------------------------------------------------------------
//// �R���X�g���N�^
////-----------------------------------------------------------------------------
//CStageImgui::CStageImgui() :
//	sliderIntmodel(0),
//	sliderIntmesh(0)
//{
//}
//
////-----------------------------------------------------------------------------
//// �f�X�g���N�^
////-----------------------------------------------------------------------------
//CStageImgui::~CStageImgui()
//{
//}
//
////-----------------------------------------------------------------------------
//// ������
////-----------------------------------------------------------------------------
//HWND CStageImgui::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
//{
//	// ������
//	HWND outWnd = CImguiProperty::Init(hWnd, pDevice);
//
//	for (int nCnt = 0; nCnt < 3; nCnt++)
//	{// ������
//		m_fMeshPos[nCnt] = 0;
//	}
//
//	return outWnd;
//}
//
////-----------------------------------------------------------------------------
//// �I��
////-----------------------------------------------------------------------------
//void CStageImgui::Uninit(HWND hWnd, WNDCLASSEX wcex)
//{
//	CImguiProperty::Uninit(hWnd, wcex);
//}
//
////-----------------------------------------------------------------------------
//// �X�V
////-----------------------------------------------------------------------------
//bool CStageImgui::Update()
//{
//#ifdef _DEBUG
//
//	HWND wnd = CApplication::Getinstnce()->GetHWnd();
//
//	CImguiProperty::Update();
//
//	// �e�L�X�g�\��
//	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);
//	ImGui::Separator();
//
//	//TaskBarUpdate();	// �^�X�N�o�[�̍X�V
//	//ImGui::SliderFloat3(u8"���b�g", &sliderRot.x, -3.14f, 3.14f);
//	//ImGui::Separator();
//
//	static bool checkBox = true;
//
//	int AnimationKeySet;
//
//	// ���b�V����pos�X�ύX
//	ImGui::DragFloat3("pos", &m_fMeshPos[0], 10.0f, 10000.0f, 0.5f);
//	//CGame::GetPlayer()->SetPos(D3DXVECTOR3(m_fMeshPos[0], m_fMeshPos[1], m_fMeshPos[2]));
//
//	ImGui::Separator();
//	ImGui::SliderInt(u8"�L�[�t���[����", &AnimationKeySet, 1, 1000);
//
//	if (ImGui::Button(u8"���b�V���̐���"))
//	{// �{�^���������ꂽ
//		checkBox = !checkBox;
//	}
//	if (ImGui::Button(u8"�}�b�v�̕ۑ�"))
//	{// �{�^���������ꂽ
//		funcFileLoad(wnd);
//	}
//	ImGui::End();
//#endif // _DEBUG
//	return false;
//
//}
//
////--------------------------------------------------
//// �`��
////--------------------------------------------------
//void CStageImgui::Draw()
//{
//	CImguiProperty::Draw();
//}
//
////--------------------------------------------------
//// �|�X�̃Z�b�g
////--------------------------------------------------
//void CStageImgui::SetMeshPos(float x, float y, float z)
//{
//	m_fMeshPos[0] = x;
//	m_fMeshPos[1] = y;
//	m_fMeshPos[2] = z;
//}
//
////--------------------------------------------------
//// �^�X�N�o�[�̍X�V
////--------------------------------------------------
////void CStageImgui::TaskBarUpdate(void)
////{
////	//if (!ImGui::BeginMenuBar())
////	//{//�^�X�N�o�[
////	//	return;
////	//}
////
////	//auto SaveLoad = [](const char* name,const char* path)
////	//{
////	//	if (ImGui::BeginMenu(name))
////	//	{
////	//		//HWND Wnd = GetWnd();
////	//		if (ImGui::MenuItem("Save"))
////	//		{
////	//			//MessageBox(Wnd, "�Z�[�u���܂����H", "����������ۑ�����ĂȂ���I", MB_OK);
////	//			//CGame::GetStage()->SavefileMesh(path);
////	//		}
////	//		else if (ImGui::MenuItem("Load"))
////	//		{
////	//			//MessageBox(Wnd, "���[�h���܂����H", "����������ۑ�����ĂȂ���I", MB_OK);
////	//			//CGame::GetStage()->LoadfileMesh(path);
////	//		}
////
////	//		ImGui::EndMenu();
////	//	}
////	//};
////
////	//auto SaveLoadModel = [](const char* name, const char* path)
////	//{
////	//	if (ImGui::BeginMenu(name))
////	//	{
////	//		HWND Wnd = GetWnd();
////	//		if (ImGui::MenuItem("Save"))
////	//		{
////	//			MessageBox(Wnd, "�Z�[�u���܂����H", "����������ۑ�����ĂȂ���I", MB_OK);
////	//			CGame::GetStage()->Savefile(path);
////	//		}
////	//		else if (ImGui::MenuItem("Load"))
////	//		{
////	//			MessageBox(Wnd, "���[�h���܂����H", "����������ۑ�����ĂȂ���I", MB_OK);
////	//			CGame::GetStage()->Loadfile(path);
////	//		}
////
////	//		ImGui::EndMenu();
////	//	}
////	//};
////	//SaveLoad(u8"���b�V��", "data\\testmesh.json");
////	//SaveLoadModel(u8"���f��", "data\\testBil.json");
////
////	//ImGui::EndMenuBar();
////}
//
////========================
////�E�B���h�E�����Ă����
////========================
//void CStageImgui::funcFileLoad(HWND hWnd)
//{
//	static OPENFILENAME     ofn;
//	static TCHAR            szPath[MAX_PATH];
//	static TCHAR            szFile[MAX_PATH];
//
//	if (szPath[0] == TEXT('\0')) {
//		GetCurrentDirectory(MAX_PATH, szPath);
//	}
//	if (ofn.lStructSize == 0) {
//		ofn.lStructSize = sizeof(OPENFILENAME);
//		ofn.hwndOwner = hWnd;
//		ofn.lpstrInitialDir = szPath;    // �����t�H���_�ʒu
//		ofn.lpstrFile = szFile;            // �I���t�@�C���i�[
//		ofn.nMaxFile = MAX_PATH;
//		ofn.lpstrDefExt = TEXT(".json");
//		ofn.lpstrFilter = TEXT("json�t�@�C��(.json)\0.json\0");
//		ofn.lpstrTitle = TEXT("�e�L�X�g�t�@�C���ǂݍ��ށB");
//		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
//	}
//	if (GetSaveFileName(&ofn)) {
//		MessageBox(hWnd, szFile, TEXT("�����ǂݍ��ނ���"), MB_OK);
//	}
//
//	if (szFile[0] != '\0')
//	{
//		CLoadStage::SaveAll(szFile);
//	}
//}