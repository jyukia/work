//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <assert.h>
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CObject::m_nNumAll = 0;
CObject *CObject::m_pTop[PRIORITY_LEVELMAX] = {};
CObject *CObject::m_pCurrent[PRIORITY_LEVELMAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(int nPriority /* = PRIORITY_LEVEL0 */) :
	m_pNext(nullptr),
	m_pPrev(nullptr),
	m_bDeath(false),
	m_canPoseUpdate(false)
{
	//�v���C�I���e�B�̕ۑ�
	m_nPriority = nPriority;

	//�I�u�W�F�N�g(�������g)���A���X�g�ɒǉ�
	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;
	}
	else if (m_pTop[nPriority] != nullptr)
	{
		m_pCurrent[nPriority]->m_pNext = this;
		this->m_pPrev = m_pCurrent[nPriority];
	}

	m_pCurrent[nPriority] = this;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// �S�ẴC���X�^���X�̏I������
//=============================================================================
void CObject::UninitAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_LEVELMAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject)
		{
			//pNext�̕ۑ�
			CObject *pObjectNext = pObject->m_pNext;	//Update()�ō폜�����ƁApNext��������̂Ŏ��O�ɕۑ����Ă���

			pObject->Release();		// ���S��Ԃɂ���

									//pObject��pObject��pNext����
			pObject = pObjectNext;
		}

		pObject = m_pTop[nPriority];

		static int a = 0;
		while (pObject != nullptr)
		{
			a++;
			//pNext�̕ۑ�
			CObject *pObjectNext = pObject->m_pNext;	//Update()�ō폜�����ƁApNext��������̂Ŏ��O�ɕۑ����Ă���

			if (pObject->m_bDeath == true)
			{
				pObject->Death();
			}

			//pObject��pObject��pNext����
			pObject = pObjectNext;
		}
		a = 0;
	}
}

//
template<typename Func>
inline void CObject::AllProcess(Func func)
{
	for (int nPriority = 0; nPriority < PRIORITY_LEVELMAX; nPriority++)
	{
		CObject *pObject = m_pTop[nPriority];

		while (pObject != nullptr)
		{
			//pNext�̕ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			func(pObject);

			//pObject��pObject��pNext����
			pObject = pObjectNext;
		}
	}
}
//=============================================================================
// �S�ẴC���X�^���X�̍X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
	auto update = [](CObject* pObject)
	{
		bool isPause = false;
		if (pObject->m_bDeath == false)
		{
			if (pObject->GetObjType() == OBJTYPE_PAUSE)
			{
				isPause = true;
			}
			if (isPause)
			{
				if (pObject->m_canPoseUpdate)
				{
					pObject->Update();
				}
			}
			else
			{
				pObject->Update();
			}
		}
	};

	AllProcess(update);

	auto Death = [](CObject* pObject)
	{
		if (pObject->m_bDeath == true)
		{
			pObject->Death();
		}
	};

	AllProcess(Death);
}

//=============================================================================
// �S�ẴC���X�^���X�̕`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
	auto Death = [](CObject* pObject)
	{
		if (pObject->m_bDeath == false)
		{
			//�`�揈���̊֐��Ăяo��
			pObject->Draw();
		}
	};

		AllProcess(Death);
}

//=============================================================================
// �I�u�W�F�N�g�j������
//=============================================================================
void CObject::Death(void)
{
	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă���Ƃ�
	if (m_pNext != nullptr)
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//�������g��m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;

			//�������g��m_pPrev������m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�������g��m_pNext��擪�ɑ��
			m_pTop[m_nPriority] = this->m_pNext;

			//�������g��m_pPrev�����̃I�u�W�F�N�g��m_pPrev�ɑ��
			m_pNext->m_pPrev = this->m_pPrev;
		}
	}

	//�I�u�W�F�N�g�̎��ɏ�񂪓����Ă��Ȃ��Ƃ�
	else
	{
		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă���Ƃ�
		if (m_pPrev != nullptr)
		{
			//����m_pPrev��nullptr����
			m_pCurrent[m_nPriority] = this->m_pPrev;

			//����m_pNext��O�̃I�u�W�F�N�g��m_pNext�ɑ��
			m_pPrev->m_pNext = this->m_pNext;
		}

		//�I�u�W�F�N�g�̑O�ɏ�񂪓����Ă��Ȃ��Ƃ�
		else
		{
			//�擪�̃I�u�W�F�N�g��nullptr����
			m_pTop[m_nPriority] = nullptr;

			//���̃I�u�W�F�N�g��nullptr����
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//�I�u�W�F�N�g(�������g)���A�j��
	this->Uninit();		// �I������
	delete this;
}

//=============================================================================
// �C���X�^���X�̉������
//=============================================================================
void CObject::Release()
{
	m_bDeath = true;
}

//=============================================================================
// ���[�h�ȊO��������j������
//=============================================================================
void CObject::ModeRelease()
{
	auto Release = [](CObject* pObject)
	{
		if (pObject->GetObjType() != OBJTYPE_MODE)
		{
			//�I�������̊֐��Ăяo��
			pObject->Release();
		}
		else
		{
			int a = 0;
		}
	};
	
	AllProcess(Release);

	auto Death = [](CObject* pObject)
	{
		if (pObject->GetObjType() != OBJTYPE_MODE)
		{
			pObject->Death();
		}
	};

	AllProcess(Death);
}

//=============================================================================
// �I�u�W�F�N�g�̎��
//=============================================================================
void CObject::SetType(const EObjType type)
{
	m_objType = type;
}

//=============================================================================
// �I�u�W�F�N�g�̃^�C�v��Ԃ�����
//=============================================================================
CObject::EObjType CObject::GetObjType(void)
{
	return m_objType;
}