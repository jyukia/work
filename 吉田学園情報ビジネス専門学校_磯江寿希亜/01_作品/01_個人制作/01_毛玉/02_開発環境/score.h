//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _Score_H_
#define _Score_H_

#include"Number.h"
#include "renderer.h"
#include"application.h"

//�O���錾
class CNumber;

class CScore : public CObject2D
{
public:
	//�R���X�g���N�^
	explicit CScore(int nPriority);
	//�f�X�g���N�^
	~CScore() override;
	
	//������
	HRESULT Init() override;
	//�I��
	void Uninit() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	void AddScore(int nValue);

	void SubScore(int nscore);

	void SetScore(int nScore);

	static CScore* Create(D3DXVECTOR3 pos);

	static int GetScore() {return m_Score;}

private:

	CNumber* pNumber[10];
	static int m_Score;	//���ۑ�
	int m_Remaining;	//���ۑ�

};

#endif