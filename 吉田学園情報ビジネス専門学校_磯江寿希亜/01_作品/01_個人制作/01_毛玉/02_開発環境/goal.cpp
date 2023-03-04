#include <assert.h>
#include "application.h"
#include "goal.h"
#include "shadow.h"
#include "game.h"
#include"DebugProc.h"
#include "player.h"
#include "fade.h"
#include "Particle.h"

bool CGoal::GoalFlg;
bool CGoal::flg;

CFade *m_pFade;

CGoal::CGoal(int nPriority)
{

}

CGoal::~CGoal()
{
}

HRESULT CGoal::Init()
{	
	{
		Cnt = 0;
		flg = false;
	}
	//objectx��pos��rot
	D3DXVECTOR3 pos = CObjectX::GetPos();

	D3DXVECTOR3 size = CObjectX::GetSize();

	D3DXVECTOR3 rot = CObjectX::GetRot();

	//�I�u�W�F�N�g�̏�����
	CObjectX::Init();

	//�e�̐���
	CShadow::Create(pos, size, CObject::PRIORITY_LEVEL3);

	Goal = CObject2D::Create("GOALUI", D3DXVECTOR3(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), PRIORITY_LEVEL4);
	Goal->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

void CGoal::Update()
{
	if (CApplication::Getinstnce()->GetpMode()->GetPlayer() != nullptr)
	{
		//�v���C���[���
		D3DXVECTOR3 pPlayerPos = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPos();
		D3DXVECTOR3 pPlayerPosOld = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetPosOld();
		D3DXVECTOR3 pSize = CApplication::Getinstnce()->GetpMode()->GetPlayer()->GetSize();
		// ���W�擾
		D3DXVECTOR3 pos = GetPos();

		//�S�[���\���ׂ̈̃p�[�e�B�N��
		//CParticle* particle = CParticle::Create("Data/TEXTURE/effect000.jpg", D3DXVECTOR3(pos), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CObject::PRIORITY_LEVEL3);
		//particle->SetBillboard(true);

		// �|�C���^�錾
		CObject *pObject = CObject::GetTop(PRIORITY_LEVEL3);
		// �v���C���[�ƃ��f���̓����蔻��
		while (pObject != nullptr)
		{
			if (pObject == this)
			{
				pObject = pObject->GetNext();
				continue;
			}
			//�ϐ��錾
			CObject::EObjType objType;

			//�I�u�W�F�N�g�̃^�C�v���擾
			objType = pObject->GetObjType();

			if (objType == OBJTYPE_PLAYER)	//�ڐG���v���C���[�̎�
			{
				CObjectX *pObjectX = (CObjectX*)pObject;

				D3DXVECTOR3 size = 	D3DXVECTOR3(200,100,200);
				GoalFlg = Collision(&pPlayerPos, &pPlayerPosOld, &size, false);
			}
			//�|�C���^�����ɐi�߂�
			pObject = pObject->GetNext();
		}
		//�S�[���ƃv���C���[���G�ꂽ��
		if (GoalFlg)
		{
			flg = true;
		}
	}
	if (flg)	//�S�[���ƃv���C���[���G�ꂽ��
	{
		Goal->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		Cnt++;
		if (Cnt >= 480)
		{
			if (m_pFade->GetFade() == CFade::FADE_NONE)
			{
				// �J��
				CFade::SetFade(CApplication::MODE_RANKING);
			}
		}
		if (Cnt >= 720)
		{
			flg = false;
		}

		CDebugProc::Print("\n GOAL %d", Cnt);
	}
}
//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CGoal::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion)
{
	// �ϐ��錾
	bool bIsLanding = false;

	// ���W�擾
	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 Min = GetMinVtx();
	
	D3DXVECTOR3 Max = GetMaxVtx();

	if (bQuaternion)
	{
		// ���f���̍��������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x + pSize->x / 2.0f <= pos.x + Min.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Min.x - (pSize->x / 2.0f);
		}
		// ���f���̉E�������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x - pSize->x / 2.0f >= pos.x + Max.x) &&
			(pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Max.x + (pSize->x / 2.0f);
		}
		// ���f���̉��������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z - pSize->z / 2.0f >= pos.z + Max.z) &&
			(pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Max.z + (pSize->z / 2.0f);
		}
		// ���f���̎�O�������蔻��(�N�H�[�^�j�I��Ver)
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z + pSize->z / 2.0f <= pos.z + Min.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Min.z - (pSize->z / 2.0f);
		}
	}
	else
	{
		// ���f���̍��������蔻��
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x + pSize->x / 2.0f <= pos.x + Min.x / 2.0f) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Min.x / 2.0f - pSize->x / 2.0f;
		}
		// ���f���̉E�������蔻��
		if ((pPos->z - pSize->z / 2.0f < pos.z + Max.z) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z) &&
			(pPosOld->x - pSize->x / 2.0f >= pos.x + Max.x / 2.0f) &&
			(pPos->x - pSize->x / 2.0f < pos.x + Max.x / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->x = pos.x + Max.x / 2.0f + pSize->x / 2.0f;
		}
		// ���f���̉��������蔻��
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z - pSize->z / 2.0f >= pos.z + Max.z / 2.0f) &&
			(pPos->z - pSize->z / 2.0f < pos.z + Max.z / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Max.z / 2.0f + pSize->z / 2.0f;
		}
		// ���f���̎�O�������蔻��
		if ((pPos->x - pSize->x / 2.0f < pos.x + Max.x) &&
			(pPos->x + pSize->x / 2.0f > pos.x + Min.x) &&
			(pPosOld->z + pSize->z / 2.0f <= pos.z + Min.z / 2.0f) &&
			(pPos->z + pSize->z / 2.0f > pos.z + Min.z / 2.0f) &&
			(pPos->y + pSize->y > pos.y) &&
			(pPos->y < pos.y + Max.y))
		{
			bIsLanding = true;
			pPos->z = pos.z + Min.z / 2.0f - pSize->z / 2.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}
//=============================================================================
// ��������
//=============================================================================
CGoal * CGoal::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CGoal *pGoal = new CGoal(nPriority);

	if (pGoal != nullptr)
	{
		pGoal->Init();
		pGoal->SetPos(pos);
		pGoal->m_shadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.5f, pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), CObject::PRIORITY_LEVEL3);
		//pGoal->SetLine(pos);
	}
	else
	{
		assert(false);
	}

	return pGoal;
}
