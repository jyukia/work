#ifndef _FILE_H_			// ���̃}�N����`������ĂȂ�������
#define _FILE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//=====================================
// �C���N���[�h
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
// �v���g�^�C�v�錾
//=====================================
nlohmann::json LoadJsonStage(const wchar_t* cUrl);


//�\����
typedef struct
{
	std::wstring main_job;
	std::wstring race;
	std::wstring unionsname;
	std::wstring name;
	int nStatus;
}Set;

//=====================================
// �v���g�^�C�v�錾
//=====================================
// ����֐�
Set *GetStatus(void);//�Q�b�g
void OutputStatus();
void Load();	//�ǂݍ��݊֐�

void OutputStatusFirst();
void LoadFirst();	//�ǂݍ��݊֐�


#endif

