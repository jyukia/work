//
//�t�@�C���w�b�_�[�R�����g
//
#ifndef _Number_H_
#define _Number_H_

#include "renderer.h"
#include"application.h"
#include"object2D.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************


//*****************************************************************************
//�}�N����`
//*****************************************************************************

class CNumber : public CObject2D
{
public:
	//�R���X�g���N�^
	explicit CNumber(int nPriority);

	//�f�X�g���N�^
	~CNumber() override;

	//������
	HRESULT Init() override;

	static CNumber* Create(const char *aFileName, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nPriority);

private:

};
#endif