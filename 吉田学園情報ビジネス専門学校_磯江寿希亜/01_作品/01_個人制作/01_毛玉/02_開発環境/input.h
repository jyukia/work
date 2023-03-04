
#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "inputkeydata.h"
#include "DirectInput.h"
#include <vector>

//----------------------------------------------------------------------------
//�O���錾
//----------------------------------------------------------------------------
class CInputKeyboard;
class CInputJoyPad;

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInput
{
public:

	CInput();
	~CInput();

	//*�A�v���P�[�V���������ɏ������
	static CInput *Create();							//���͏����n�̃N���G�C�g�AInit�̑O�ɏ���
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
	void Uninit();										//���͏����S���̏I������
	void Update();										//���͏����S���̍X�V����
	//*

	//*�C���v�b�g���K�v�Ȏ��Ăяo��
	static CInput *GetKey() { return m_pInput; }		//�v���C��g���K�[�Ȃǂ̃A�h���X�̎擾

	// �S�Ẵf�o�C�X
	bool Press(STAN_DART_INPUT_KEY key);				//�����v���X
	bool Trigger(STAN_DART_INPUT_KEY key);				//�����g���K�[
	bool Release(STAN_DART_INPUT_KEY key);				//���������[�X

	// ���͂��Ă���f�o�C�X���w��
	bool Press(STAN_DART_INPUT_KEY key, int nNum);		//�����v���X
	bool Trigger(STAN_DART_INPUT_KEY key, int nNum);	//�����g���K�[
	bool Release(STAN_DART_INPUT_KEY key, int nNum);	//���������[�X

	// ���͂��Ă���f�o�C�X��Ԃ�
	std::vector<int> PressDevice(STAN_DART_INPUT_KEY key);		// �����v���X
	std::vector<int> TriggerDevice(STAN_DART_INPUT_KEY key);	// �����g���K�[
	std::vector<int> ReleaseDevice(STAN_DART_INPUT_KEY key);	// ���������[�X

	bool Press(int nKey);								// �L�[�{�[�h�v���X
	bool Trigger(int nkey);								// �L�[�{�[�h�g���K�[
	bool Release(int nkey);								// �L�[�{�[�h�����[�X
	bool Press(DirectJoypad key, int nNum = 0);			// �W���C�p�b�g�v���X
	bool Trigger(DirectJoypad key, int nNum = 0);		// �W���C�p�b�g�g���K�[
	bool Release(DirectJoypad key, int nNum = 0);		// �W���C�p�b�h�����[�X
	bool PressAll(DirectJoypad key);					// �W���C�p�b�g�v���X
	bool TriggerAll(DirectJoypad key);					// �W���C�p�b�g�g���K�[
	bool ReleaseAll(DirectJoypad key);					// �W���C�p�b�h�����[�X

	D3DXVECTOR3 VectorMoveKey();								//�\���L�[���̃x�N�g���擾
	D3DXVECTOR3 VectorMoveJoyStick(int nNum = 0, bool bleftandright = false); //�W���C�X�e�B�b�N�̃x�N�g���擾
	//*
	
	// Getter
	int GetAcceptJoyPadCount();

private:

	CInputKeyboard *m_pKeyboard;	//�L�[�{�[�h�̏��
	CInputJoyPad *m_pJoyPad;		//�W���C�p�b�h�̏��
	static CInput *m_pInput;		//���̃N���X�̏��
};

#endif

