#ifndef _PRECOMPILE_H_	// このマクロ定義がされてなかったら
#define _PRECOMPILE_H_	// 二重インクルード防止のマクロ定義

#define DIRECTINPUT_VERSION (0x0800)		//ビルド時の警告対処用マクロ

#include <stdio.h>
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
#include <assert.h>
#include <time.h>
#include<vector>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//#include "imgui.h"
//#include "imgui_impl_dx9.h"
//#include "imgui_impl_win32.h"
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include <imgui_internal.h>

#include <tchar.h> // _T
#include <d3d9.h>

#include <assert.h>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <sstream>
#endif