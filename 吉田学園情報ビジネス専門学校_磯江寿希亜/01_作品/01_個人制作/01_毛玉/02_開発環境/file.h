#ifndef _FILE_H_			// このマクロ定義がされてなかったら
#define _FILE_H_			// 二重インクルード防止のマクロ定義

//=====================================
// インクルード
//=====================================
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "nlohmann/json.hpp"

#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <sstream>

#include "nlohmann/json.hpp"

//=====================================
// プロトタイプ宣言
//=====================================
nlohmann::json LoadJsonStage(const wchar_t* cUrl);


//構造体
typedef struct
{
	std::wstring main_job;
	std::wstring race;
	std::wstring unionsname;
	std::wstring name;
	int nStatus;
}Set;

//=====================================
// プロトタイプ宣言
//=====================================
// 制御関数
Set *GetStatus(void);//ゲット
void OutputStatus();
void Load();	//読み込み関数

void OutputStatusFirst();
void LoadFirst();	//読み込み関数


#endif

