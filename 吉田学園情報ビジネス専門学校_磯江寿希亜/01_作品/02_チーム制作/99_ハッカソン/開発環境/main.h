//============================
//
// ���C���w�b�_�[
// Author:Teruto Sato
//
//============================
#ifndef _MAIN_H_	//���̃}�N������`����ĂȂ�������
#define _MAIN_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include <windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)		//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"		//���͏����ɕK�v
#include "Xinput.h"		//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�Ɏg�p
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾���ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define	SCREEN_WIDTH	(1280)		//�E�C���h�E�̕�
#define	SCREEN_HEIGHT	(720)		//�E�C���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g�����
	MODE_GAME,			//�Q�[�����
	MODE_RESULT,		//���U���g���
	MODE_FADE,			//�t�F�[�h���
	MODE_RANKING,		//�����L���O���
	MODE_GAMEOVER,
	MODE_TUTORIAL,
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9	GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);



//���_���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`���ւ̃|�C���^
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`���ւ̃|�C���^
}VERTEX_3D;


void SetNormalpos(VERTEX_2D *pVtx, float XUP, float XDW, float YUP, float YDW);
void Settex(VERTEX_2D *pVtx, float left, float right, float top, float down);
#endif