#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjPRO : public CObj
{
public:
	CObjPRO() {};
	~CObjPRO() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:

	int m_time;	//�e���b�v�o���p
	int PR;		//�v�����[�O�p�ϐ�
};
