//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "load_stage.h"
#include "file.h"
#include "objectX_group.h"
#include"object.h"
#include"objectX.h"
#include "goal.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLoadStage::CLoadStage()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLoadStage::~CLoadStage()
{
}

//-----------------------------------------------------------------------------
// �X�e�[�W�̓Ǎ���
//-----------------------------------------------------------------------------
void CLoadStage::LoadAll(const D3DXVECTOR3& inPos)
{
	nlohmann::json list = LoadJsonStage(L"Data/FILE/stage.json");

	int size = (int)list["STAGE"].size();

	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(list["STAGE"][i]["POS"][0], list["STAGE"][i]["POS"][1], list["STAGE"][i]["POS"][2]);
		pos += inPos;
		CObjectX* objectX = CObjectX::Create(pos, CObject::PRIORITY_LEVEL3);

		// �p�x�̐ݒ�
		D3DXVECTOR3 rot = D3DXVECTOR3(list["STAGE"][i]["ROT"][0], list["STAGE"][i]["ROT"][1], list["STAGE"][i]["ROT"][2]);
		objectX->SetRot(rot);

		bool collision = list["STAGE"][i]["COLLISION"] == "TRUE";
		objectX->SetCollisionFlag(collision);

		// ���f���̐ݒ�
		std::string tag = list["STAGE"][i]["MODEL"];
		objectX->LoadModel(tag.c_str());

		// �ʒu�̍Čv�Z
		objectX->CalculationVtx();
	}
}

void CLoadStage::SaveAll(std::string file)
{
	int nIndex = 0;
	nlohmann::json list;

	for (int maxObje =0; maxObje <= CObject::PRIORITY_LEVELMAX; maxObje++)
	{
		CObject* pObje = CObject::GetTop(maxObje);

		while (pObje != nullptr)
		{
			if (pObje->GetObjType() == CObject::OBJTYPE_MODEL)
			{
				CObjectX* pObjeX = dynamic_cast<CObjectX*>(pObje);  // �_�E���L���X�g

				std::string name = "OBJECTX";
				std::string Number = std::to_string(nIndex);
				name += Number;

				list[name] = {
					{ "POS",{
						{ "X", pObjeX->GetPos().x } ,
						{ "Y", pObjeX->GetPos().y } ,
						{ "Z", pObjeX->GetPos().z } } }, 

					{ "ROT",{
						{ "X", pObjeX->GetRot().x } ,
						{ "Y", pObjeX->GetRot().y } ,
						{ "Z", pObjeX->GetRot().z } } },

					{ "NAME", pObjeX->Getstring().c_str()}
				};
				nIndex++;
			}
			//pObject��pObject��pNext����
			pObje = pObje->GetNext();
		}
	}

	list["INDEX"] = nIndex;

	auto jobj = list.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = file.c_str();
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

//�֐��ǂݍ���
void CLoadStage::LoadAllTest(int select_stage)
{
	//nlohmann::json list = LoadJsonStage(L"Data/FILE/Save.json");

	nlohmann::json list;

	switch (select_stage)
	{
	case 0:	//�}�b�v1
			list = LoadJsonStage(L"Data/testmap.json");
			break;
	default:
		break;
	}

	int nIndex = list["INDEX"];

	CGoal* pGoal;				//�S�[���|�C���^

	for (int Count = 0;Count < nIndex;Count++)
	{
		std::string name = "OBJECTX";
		std::string Number = std::to_string(Count);
		name += Number;
	
		//���W�̐ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(list[name]["POS"]["X"], list[name]["POS"]["Y"], list[name]["POS"]["Z"]);
		//objectX->SetPos(pos);

		//��]���W�ݒ�
		D3DXVECTOR3 rot = D3DXVECTOR3(list[name]["ROT"]["X"], list[name]["ROT"]["Y"], list[name]["ROT"]["Z"]);
		//objectX->SetRot(rot);

		std::string modelname = list[name]["NAME"];

		if (modelname == "GOAL")
		{
			pGoal = CGoal::Create(D3DXVECTOR3(1100.0f, 6000.0f, -600.0f), CObject::PRIORITY_LEVEL3);
			pGoal->LoadModel("Kedama");
			//pGoal->Setstring("GOAL");
		}
		else
		{
			CObjectX* model = CObjectX::Create(modelname.c_str(), rot, pos, 3);
		}
	}
}