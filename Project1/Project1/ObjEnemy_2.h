#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define WINDOW_MAX_X (800.0f)
#define WINDOW_MIN_X (-32.0f)
#define WINDOW_MAX_Y (600.0f)
#define WINDOW_MIN_Y (-32.0f)

#define MAP_MIN   (0)
#define MAP_ERROR (-1)
#define MAP_DRAW_SIZE (64.0f)

#define BUFFER_MAX         (8)
#define BUFFER_DELETE_DATA (999)
#define BUFFER_NO_DATA     (-1)

#define SEARCH_MAX         (4)
#define SEARCH_MAP_NEXT    (1)

#define KM_MAP_MAX         (9)
#define CONNECTION_DELETE  (1)

#define LINE_LOOP          (1)
#define LINE_STEP_UP       (1)
#define LINE_STEP_X_PLUS   (0)
#define LINE_STEP_Y_PULS   (0)

//�I�u�W�F�N�g�F��l��
class CObjEnemy2 : public CObj
{
public:
	CObjEnemy2(float x, float y);
	~CObjEnemy2() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[

	float GetX() { return m_ex; }
	float GetY() { return m_ey; }

	void SetX(float x) { m_ex = x; }
	void SetY(float y) { m_ey = y; }

	float scrollY() { return escrolly; }
	float scrollX() { return escrollx; }

private:
	float m_ex;  //�I�u�W�F�N�g�̈ʒuX
	float m_ey;  //�I�u�W�F�N�g�̈ʒuY
	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y
	float m_posture; //�p��

	int m_map[MAP_X][MAP_Y];
	int m_flg;//�Ǐ]�ړ��̊Ǘ��p�t���O

	int m_time;
	int zx;
	int zy;

	float escrolly;
	float escrollx;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	int m_id;
	int k_id;

	int m_ani_frame;
	int m_ani_time;
	int m_ani_max_time;
	float damage_time;//�_���[�W�u�[�X�g�p���ԕϐ�
	bool boost_flag;//�_���[�W�u�[�X�g����񂵂����������Ȃ����߂̃t���O

	float px, py;//��_
};