#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"

//=============================================================================
// �O����`
//=============================================================================
class CShadow;
class CItem : public CObjectX
{
public:
	enum TypeItem
	{
		ITEM_NONE = 0,

		ITEM_MOVE_SPEED_UP,
		ITEM_GAMETIME_UP,
		ITEM_SCORE_UP,

		ITEM_MAX
	};


	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CItem(int nPriority = PRIORITY_LEVEL3);
	~CItem() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Update() override;				// �X�V����

	void Uninit() override;				// �I������
	bool Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, bool bQuaternion);

	void SetType(TypeItem type) { typeItem = type; }

	static CItem *Create(const D3DXVECTOR3 pos, int nPriority, TypeItem type);    // ��������

	 bool GetHitFlg(void) { return HitFlg; }

	 bool GetMoveSpeedUpflg(void) { return MoveSpeedUp; }
	 static bool GetSizdownflg(void) { return MoveLifeUpflg; }
	static void SetSizdownflg(bool flg) { MoveLifeUpflg = flg; }

	 bool GetScoreUpflg(void) { return ScoreUpflg; }

private:
	CShadow *m_shadow;					// �e�̃|�C���^

	TypeItem typeItem;

	int Cnt;

	 bool HitFlg;

	 bool MoveSpeedUp;
	static bool MoveLifeUpflg;
	 bool ScoreUpflg;
};


#endif