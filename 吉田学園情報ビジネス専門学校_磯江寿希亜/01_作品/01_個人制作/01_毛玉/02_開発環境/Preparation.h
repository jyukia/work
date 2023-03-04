//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _Preparation_H_
#define _Preparation_H_

#include"object2D.h"
#include "renderer.h"
#include"application.h"

//�O���錾


class Cpreparation : public CObject2D
{
public:
	//�R���X�g���N�^
	Cpreparation(int nPriority);
	//�f�X�g���N�^
	~Cpreparation() override;

	//������
	HRESULT Init() override;
	//�X�V
	void Update() override;

	static Cpreparation* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriority);


private:

	int ChangeCount;
	int count;
};

#endif