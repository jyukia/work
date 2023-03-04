//============================
//
// ファイル設定
// Author:磯江寿希亜 
//
//============================
#include "file.h"
#include "letter.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"

#include"application.h"
#include <fstream>

#include"SelectStage.h"



//===============================
//ゲーム内ヘッター
//===============================
Set DataSet;
namespace nl = nlohmann;
nl::json j;//リストの生成

//============================
//ゲット関数
//============================
Set *GetStatus(void)
{
	return &DataSet;
}

//============================
// 全部出力（置くだけ）
//============================
void OutputStatus()
{
	auto JsoninD3DXVVECTOR3 = [](nl::json& jsonf, std::string a, D3DXVECTOR3 inPos, D3DXVECTOR3 inRot)
	{
		jsonf[a] = {
			{ "POS" ,{ { "X",inPos.x },{ "Y",inPos.y },{ "Z",inPos.z } } },
			{ "ROT" ,{ { "X",inRot.x },{ "Y",inRot.y },{ "Z",inRot.z } } },
		};
	};

	//
	//マップ内
	//
	{//	ハサミ
		std::string a = "FENCE";
	std::string b = std::to_string(0);
	a += b;
	//情報
	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1510.0f, 20.0f, -2270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//	ボトル(小瓶)
	//	std::string a = "BOTTLE";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(500.0f + 100 * Cnt, 600.0f, -880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//	ボトル(小瓶)
	//	std::string a = "BOTTLE_1";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(800.0f + 100 * Cnt, 600.0f, -1900.0f + 200 * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	{//	ハサミ
	//	std::string a = "SCISSORS";
	//std::string b = std::to_string(0);
	//a += b;
	////情報
	//JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1510.0f, 600.0f, -2270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for(int Count = 0; Count <2;Count++)
	//{//	ジョッキ
	//	std::string a = "BEERMUG";
	//	std::string b = std::to_string(Count);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(570.0f + 600 * Count, 600.0f, -1400.0f - 600 *Count), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	{//テ―ブル
	//	
	//	std::string a = "TABLE";
	//	std::string b = std::to_string(0);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1000.0f, 0.0f, -1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//椅子 横
	//std::string a = "CHAIRX";
	//std::string b = std::to_string(Cnt);
	//a += b;
	////情報
	//JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(-500.0f +2800 * Cnt, 0.0f, -1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//椅子 奥
	//	std::string a = "CHAIRZ";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1000.0f, 0.0f, -3000.0f + 2800 * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	float lch = -2600;
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//コップ
	//	std::string a = "CUPX";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(100.0f + 1500.0f * Cnt, 605.0f, -1700.0f + 200.0f * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//皿 X
	//	std::string a = "PLATE";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(100.0f + 1500.0f * Cnt, 605.0f, -1700.0f + 200.0f * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//皿 Z
	//	std::string a = "PLATE_Z";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1000.0f + 100.0f * Cnt, 605.0f, -2200 + 1500.0f * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	{//スプーン
	//	std::string a = "SPOON_Z";
	//	std::string b = std::to_string(0);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(0.0f, 45.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, -2300));
	//}
	//	{//スプーン
	//	std::string a = "SPOON_Z1";
	//	std::string b = std::to_string(0);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(0.0f, -45.0f, 0.0f), D3DXVECTOR3(1100.0f, 605.0f, -600));
	//}
	//	for (int Cnt = 0; Cnt < 2; Cnt++)
	//{//スプーン
	//	std::string a = "SPOON";
	//	std::string b = std::to_string(Cnt);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(0.0f + 1700.0f * Cnt, 600.0f, -1700.0f + 300.0f * Cnt), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//	{//写真立て
	//std::string a = "PHOTOSTAND";
	//std::string b = std::to_string(0);
	//a += b;
	////情報
	//JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1250.0f, 600.0f, -1100.0f));
	//}
	//	{//ティーポット
	//	std::string a = "TEAPOT";
	//	std::string b = std::to_string(0);
	//	a += b;
	//	//情報
	//	JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1500.0f, 600.0f, -1900.0f));
	//}



	//	
	//マップ外
	//	

	//	{//写真
	//		std::string a = "PICTURE";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(100.0f, 300.0f, -1650.0f + lch), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}
	//	{//宝箱
	//		std::string a = "CHEST";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(4000.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	//	}
	//	{//本棚
	//		std::string a = "BOOKSHELF";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(-1500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	//	}
	//	{//ドア
	//		std::string a = "DOOR";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(-1150.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}
	//	{//ケーキスタンド
	//		std::string a = "CAKESTAND";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(1000.0f, 600.0f, -1460.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}
	//	{//砂時計
	//		std::string a = "HOURGLASS";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(800.0f, 600.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}
	//	{//本
	//		std::string a = "BOOK";
	//		std::string b = std::to_string(0);
	//		a += b;
	//		//情報
	//		JsoninD3DXVVECTOR3(j, a, D3DXVECTOR3(280.0f, 600.0f, -1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	}


	auto jobj = j.dump();

	std::ofstream writing_fileL;
	const std::string pathToJSON = "Data/FILE/output_params.json";
	writing_fileL.open(pathToJSON, std::ios::out);
	writing_fileL << jobj << std::endl;
	writing_fileL.close();
}
//読み込み関数
void Load()
{
	std::ifstream ifs("Data/FILE/output_params.json");
	if (ifs)
	{
		ifs >> j;

		{//ロード統括
		}
		//
		//マップ1
		//

		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//小瓶
		//	std::string a = "BOTTLE";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* bottle = CObjectX::Create("BOTTLE", pos,3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//小瓶
		//	std::string a = "BOTTLE_1";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* bottle = CObjectX::Create("BOTTLE", pos, 3);
		//}
		//	{//ハサミ
		//	std::string a = "SCISSORS";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* bottle = CObjectX::Create("SCISSORS", pos, 3);
		//	}
		//	for (int Count = 0; Count <2; Count++)
		//{//ジョッキ
		//	std::string a = "BEERMUG";
		//	std::string b = std::to_string(Count);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* bottle = CObjectX::Create("BEERMUG", pos, 3);
		//}
		//	{//テーブル
		//	std::string a = "TABLE";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//右
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* table = CObjectX::Create("TABLE", pos, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//椅子
		//std::string a = "CHAIRX";
		//std::string b = std::to_string(Cnt);
		//a += b;
		////右
		//D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//CObjectX* chair = CObjectX::Create("CHAIR", pos, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//椅子
		//std::string a = "CHAIRZ";
		//std::string b = std::to_string(Cnt);
		//a += b;
		////右
		//D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//CObjectX* chair = CObjectX::Create("CHAIR", pos, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//
		//	std::string a = "CUPX";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* chair = CObjectX::Create("CUP", pos, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//
		//	std::string a = "PLATE";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* plate = CObjectX::Create("PLATE", pos, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//
		//	std::string a = "PLATE_Z";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* plate_z = CObjectX::Create("PLATE", pos, 3);
		//}
		//	{//
		//	std::string a = "SPOON_Z";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* plate_z = CObjectX::Create("SPOON", pos, rot, 3);
		//}
		//	{//
		//	std::string a = "SPOON_Z1";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* plate_z1 = CObjectX::Create("SPOON", pos, rot, 3);
		//}
		//	for (int Cnt = 0; Cnt < 2; Cnt++)
		//{//
		//	std::string a = "SPOON";
		//	std::string b = std::to_string(Cnt);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* pSpoon = CObjectX::Create("SPOON", pos, 3);
		//}
		//	{//写真立て
		//	std::string a = "PHOTOSTAND";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* pPhotostand = CObjectX::Create("PHOTOSTAND", pos, rot, 3);
		//}
		//	{//ティーポット
		//	std::string a = "TEAPOT";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* pPhotostand = CObjectX::Create("TEAPOT", pos, rot, 3);
		//}
		//	{//写真
		//	std::string a = "PICTURE";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* picture = CObjectX::Create("PICTURE", pos, 3);
		//}
		//	{//本棚
		//	std::string a = "BOOKSHELF";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* pbookshelf = CObjectX::Create("BOOKSHELF", rot, pos, 3);
		//}
		//	{//宝箱
		//	std::string a = "CHEST";
		//std::string b = std::to_string(0);
		//a += b;
		////
		//D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//CObjectX* pchest = CObjectX::Create("CHEST", rot, pos, 3);
		//}
		//	{//ドア
		//	std::string a = "DOOR";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//右
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* door = CObjectX::Create("DOOR", rot, pos, 3);
		//}
		//	{//ケーキスタンド
		//	std::string a = "CAKESTAND";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//右
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* cakestand = CObjectX::Create("CAKESTAND", rot, pos, 3);
		//}
		//	{//砂時計
		//	std::string a = "HOURGLASS";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//右
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* hourglass = CObjectX::Create("HOURGLASS", rot, pos, 3);
		//}
		//	{//本
		//	std::string a = "BOOK";
		//	std::string b = std::to_string(0);
		//	a += b;
		//	//右
		//	D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		//	D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		//	CObjectX* hourglass = CObjectX::Create("BOOK", rot, pos, 3);
		//}


		{//
		std::string a = "FENCE";
		std::string b = std::to_string(0);
		a += b;
		
		//
		D3DXVECTOR3 pos = D3DXVECTOR3(j[a]["POS"]["X"], j[a]["POS"]["Y"], j[a]["POS"]["Z"]);
		D3DXVECTOR3 rot = D3DXVECTOR3(j[a]["ROT"]["X"], j[a]["ROT"]["Y"], j[a]["ROT"]["Z"]);
		CObjectX* scissors = CObjectX::Create("FENCE", pos, 3);
		}

	}
}


//============================
// 読込み
//============================
nlohmann::json LoadJsonStage(const wchar_t* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		nlohmann::json list;	// リストの作成

		ifs >> list;
		return list;
	}

	/* ↓ファイルを開くのを失敗した場合↓ */
	return nullptr;
}
