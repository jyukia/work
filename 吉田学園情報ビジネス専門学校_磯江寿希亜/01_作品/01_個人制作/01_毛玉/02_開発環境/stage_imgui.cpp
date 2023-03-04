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
//// コンストラクタ
////-----------------------------------------------------------------------------
//CStageImgui::CStageImgui() :
//	sliderIntmodel(0),
//	sliderIntmesh(0)
//{
//}
//
////-----------------------------------------------------------------------------
//// デストラクタ
////-----------------------------------------------------------------------------
//CStageImgui::~CStageImgui()
//{
//}
//
////-----------------------------------------------------------------------------
//// 初期化
////-----------------------------------------------------------------------------
//HWND CStageImgui::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
//{
//	// 初期化
//	HWND outWnd = CImguiProperty::Init(hWnd, pDevice);
//
//	for (int nCnt = 0; nCnt < 3; nCnt++)
//	{// 初期化
//		m_fMeshPos[nCnt] = 0;
//	}
//
//	return outWnd;
//}
//
////-----------------------------------------------------------------------------
//// 終了
////-----------------------------------------------------------------------------
//void CStageImgui::Uninit(HWND hWnd, WNDCLASSEX wcex)
//{
//	CImguiProperty::Uninit(hWnd, wcex);
//}
//
////-----------------------------------------------------------------------------
//// 更新
////-----------------------------------------------------------------------------
//bool CStageImgui::Update()
//{
//#ifdef _DEBUG
//
//	HWND wnd = CApplication::Getinstnce()->GetHWnd();
//
//	CImguiProperty::Update();
//
//	// テキスト表示
//	ImGui::Text("FPS  : %.2f", ImGui::GetIO().Framerate);
//	ImGui::Separator();
//
//	//TaskBarUpdate();	// タスクバーの更新
//	//ImGui::SliderFloat3(u8"ロット", &sliderRot.x, -3.14f, 3.14f);
//	//ImGui::Separator();
//
//	static bool checkBox = true;
//
//	int AnimationKeySet;
//
//	// メッシュのposス変更
//	ImGui::DragFloat3("pos", &m_fMeshPos[0], 10.0f, 10000.0f, 0.5f);
//	//CGame::GetPlayer()->SetPos(D3DXVECTOR3(m_fMeshPos[0], m_fMeshPos[1], m_fMeshPos[2]));
//
//	ImGui::Separator();
//	ImGui::SliderInt(u8"キーフレーム数", &AnimationKeySet, 1, 1000);
//
//	if (ImGui::Button(u8"メッシュの生成"))
//	{// ボタンが押された
//		checkBox = !checkBox;
//	}
//	if (ImGui::Button(u8"マップの保存"))
//	{// ボタンが押された
//		funcFileLoad(wnd);
//	}
//	ImGui::End();
//#endif // _DEBUG
//	return false;
//
//}
//
////--------------------------------------------------
//// 描画
////--------------------------------------------------
//void CStageImgui::Draw()
//{
//	CImguiProperty::Draw();
//}
//
////--------------------------------------------------
//// ポスのセット
////--------------------------------------------------
//void CStageImgui::SetMeshPos(float x, float y, float z)
//{
//	m_fMeshPos[0] = x;
//	m_fMeshPos[1] = y;
//	m_fMeshPos[2] = z;
//}
//
////--------------------------------------------------
//// タスクバーの更新
////--------------------------------------------------
////void CStageImgui::TaskBarUpdate(void)
////{
////	//if (!ImGui::BeginMenuBar())
////	//{//タスクバー
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
////	//			//MessageBox(Wnd, "セーブしますか？", "今消したら保存されてないよ！", MB_OK);
////	//			//CGame::GetStage()->SavefileMesh(path);
////	//		}
////	//		else if (ImGui::MenuItem("Load"))
////	//		{
////	//			//MessageBox(Wnd, "ロードしますか？", "今消したら保存されてないよ！", MB_OK);
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
////	//			MessageBox(Wnd, "セーブしますか？", "今消したら保存されてないよ！", MB_OK);
////	//			CGame::GetStage()->Savefile(path);
////	//		}
////	//		else if (ImGui::MenuItem("Load"))
////	//		{
////	//			MessageBox(Wnd, "ロードしますか？", "今消したら保存されてないよ！", MB_OK);
////	//			CGame::GetStage()->Loadfile(path);
////	//		}
////
////	//		ImGui::EndMenu();
////	//	}
////	//};
////	//SaveLoad(u8"メッシュ", "data\\testmesh.json");
////	//SaveLoadModel(u8"モデル", "data\\testBil.json");
////
////	//ImGui::EndMenuBar();
////}
//
////========================
////ウィンドウだしてやるやつ
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
//		ofn.lpstrInitialDir = szPath;    // 初期フォルダ位置
//		ofn.lpstrFile = szFile;            // 選択ファイル格納
//		ofn.nMaxFile = MAX_PATH;
//		ofn.lpstrDefExt = TEXT(".json");
//		ofn.lpstrFilter = TEXT("jsonファイル(.json)\0.json\0");
//		ofn.lpstrTitle = TEXT("テキストファイル読み込む。");
//		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
//	}
//	if (GetSaveFileName(&ofn)) {
//		MessageBox(hWnd, szFile, TEXT("これを読み込むぞぉ"), MB_OK);
//	}
//
//	if (szFile[0] != '\0')
//	{
//		CLoadStage::SaveAll(szFile);
//	}
//}