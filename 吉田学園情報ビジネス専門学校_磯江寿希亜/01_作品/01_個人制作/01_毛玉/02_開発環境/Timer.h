//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _Timer_H_
#define _Timer_H_

#include"Number.h"
#include "renderer.h"
#include"application.h"
#include"mode.h"
#include"player.h"
//�O���錾
class CNumber;
class CFade;

class CTimer : public CObject2D
{
public:
	//�R���X�g���N�^
	explicit CTimer(int nPriority);
	//�f�X�g���N�^
	~CTimer() override;

	//������
	HRESULT Init() override;
	//�I��
	void Uninit() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	void Addlife(int nValue);

	void Sublife(int nDecrease);

	void Setlife(int nLife);

	static CTimer* Create(D3DXVECTOR3 pos, int nPriority);

private:
	CFade *m_pFadeTime;

	CMeshLine *m_meshline;

	CNumber* pNumber[2];
	int m_Time;	//���ۑ�

	bool flg = CApplication::Getinstnce()->GetpMode()->GetPlayer()->Getbredycheck();

	int TimeCnt;	//���Ԏ擾
	bool returnflg;
	int cnt;

};

#endif