#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjClickTitle : public CObj
{
public:
	CObjClickTitle() {};
	~CObjClickTitle() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[

	int Save_Data() { return save_data; }
	void Stage_Data(int s) { stage_data = s; }
private:
	float m_yj;	    //���ړ��ϐ�
	bool m_f;	    //��󐧌�p
	int save_data;  //�ĊJ����Ƃ��̃X�e�[�W�̃Z�[�u�f�[�^
	int stage_data; //�X�e�[�W�̐i�s��
};