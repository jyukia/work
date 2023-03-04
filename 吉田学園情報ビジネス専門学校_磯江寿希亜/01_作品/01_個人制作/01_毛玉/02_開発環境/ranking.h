#ifndef _RANKING_H_
#define _RANKING_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
// �O����`
//=============================================================================
class CObject2D;
class CFade;
class CNumber;
class CLight;
class CGoal;
class CMovelife;
//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_RANKING        (5)        //�����L���O�̌���
#define MAX_RANKINGRANK    (5)        //�����L���O�̏��ʕ�
#define MAX_TEXTURE        (4)        //�e�N�X�`���̐�

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CRanking : public CMode
{
public:
	CRanking();
	~CRanking();

	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Load(void);
	void Save(void);

	void Load1(void);
	void Save1(void);


	static void SetRankingScore();
	static void GetRanking(int Ranking);

	static void SetRankingScore1();
	static void GetRanking1(int Ranking);

	static CRanking * Create();

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE] = {};
	CObject2D * m_pObject2D[3];

	static CMovelife *m_pMovelife[MAX_RANKING];			//�X�R�A�ɂȂ镨
	static CMovelife *m_pMovelife1[MAX_RANKING];			//�X�R�A�ɂȂ镨


	static int m_nRanking1;
	static int m_nRanking;

	static int aData[MAX_RANKINGRANK];
	static int bData[MAX_RANKINGRANK];

	static CLight *m_pLight;				// ���C�g�̃|�C���^
	static CGoal *m_pGoal;				//�S�[���|�C���^
	static CMeshfield *m_pMeshField;		// ���b�V���t�B�[���h�̃|�C���^	

	bool m_bmodeflg;
	CFade *m_pFade;
};
#endif