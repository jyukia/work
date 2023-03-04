#ifndef _GOAL_H_
#define _GOAL_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"

//=============================================================================
// �O����`
//=============================================================================
class CShadow;
class CFade;
class CObject2D;
class CGoal : public CObjectX
{
public:
	
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CGoal(int nPriority = PRIORITY_LEVEL3);
	~CGoal() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Update() override;				// �X�V����
	bool Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion);

	static CGoal *Create(const D3DXVECTOR3 pos, int nPriority);    // ��������

	static bool GetGoalFlg(void) { return GoalFlg; }

	static bool Getflg(void) { return flg; }
	static void Setflg(bool goalflg) { flg = goalflg; }
private:
	CShadow *m_shadow;					// �e�̃|�C���^
	CFade *m_pFade;

	static bool GoalFlg;

	int Cnt;
	static bool flg;

	CObject2D* Goal;
};


#endif