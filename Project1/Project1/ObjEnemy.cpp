//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "SceneMain.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjEnemy::CObjEnemy(float x,float y)
{
	m_ex = x;
	m_ey = y;
}
//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 0.0f;
	m_vy = 0.0f;
	

	
	m_flg = 0;

	m_id = CHAR_ENEMY;
	k_id = 1;
	m_time = 0;
	damage_time = 0.0f;

	boost_flag = false;

	
	
	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ex, m_ey, 76,76, ELEMENT_ENEMY, OBJ_ENEMY, 1);

	m_ani_frame = 0;

	m_ani_time = M_ANI_TIME;

	m_ani_max_time = M_ANI_MAX_TIME;
}

//�A�N�V����
void CObjEnemy::Action()
{

	//�}�b�v���̎擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));

	
	if (main->MapChangeData() != 0)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	else if (main->RoomFlag() == false && main->GetFlug() == true)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_ex, m_ey, 76, 76, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	}
	

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	float scrollx = main->GetScrollX();
	float scrolly = main->GetScrollY();
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));

	//��ʓ��ɓ���Ǝ�l����Ǐ]����
	if     (m_ex<(WINDOW_MAX_X + -(scrollx)) && m_ex>(WINDOW_MIN_X + -(scrollx)) &&
		    m_ey<(WINDOW_MAX_Y + -(scrolly)) && m_ey>(WINDOW_MIN_Y + -(scrolly)))
	{
		if (hx - m_ex > hy - m_ey&&m_hit_left||
			hx - m_ex > hy - m_ey && m_hit_right)
		{
			m_vx = (hx + -(scrollx)-m_ex);
		}
		else
		{
			m_vy = (hy + -(scrolly)-m_ey);
		}
		m_ani_time++;
	}
	//��ʊO�ɐ��b���邩��l�����J�M�������Ă���Ǝ�l���̋߂��Ƀ��[�v����
	else
	{
		m_time++;
		gx = (hx + -(scrollx)+(BLOCK_SIZE_X * 5)) / BLOCK_SIZE_X;
		gy = (hy + -(scrolly)+(BLOCK_SIZE_Y * 5)) / BLOCK_SIZE_Y;
		

		if (m_time > 300&& m_map[gy][gx]==1&&hero->GetKeyID()==ITEM_KEY)
		{
			m_time = 0;
			
			m_ex = gx*64.0f;
			m_ey = gy*64.0f;
			m_ani_time++;
		}
	}


	//�A�j���[�V�����̃��Z�b�g
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�A�j���[�V�����t���[���̃��Z�b�g
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}
	//�ړ��x�N�g���̐��K��
	UnitVec(&m_vy, &m_vx);

	m_ex += m_vx* ENEMY_VECTOR_X;
	m_ey += m_vy* ENEMY_VECTOR_Y;

	
	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�}�b�v�̓����蔻�菈��
	main->MapHit(&m_ex, &m_ey, false, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d, &m_id, &k_id);
	
	//���g��hitbox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	if (hit != nullptr)
	{
		//hitbox�̈ʒu�̕ύX
		hit->SetPos(m_ex + main->GetScrollX(), m_ey + main->GetScrollY());
	}

	if (main->RoomFlag()==true)
	{
		Hits::DeleteHitBox(this);
	}

	

	if (main->RoomFlag() == true)
	{
		Hits::DeleteHitBox(this);
	}
}

//�h���[
void CObjEnemy::Draw()
{
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (main->RoomFlag() == false)
	{
		//�A�j���[�V�����f�[�^
		int AniData[4] =
		{
			0,1,1,0,

		};
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src; //�`�挳�؂���ʒu
		RECT_F dst; //�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 16.0f;
		src.m_left = 84.0f + AniData[m_ani_frame] *ENEMY_SIZE;
		src.m_right = 480.0 + AniData[m_ani_frame] * ENEMY_SIZE;
		src.m_bottom = 496.0f;


		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_ey + main->GetScrollY();
		dst.m_left = (ENEMY_DISPLAY) + m_ex + main->GetScrollX();
		dst.m_right = (ENEMY_DISPLAY - ENEMY_DISPLAY) + m_ex + main->GetScrollX();
		dst.m_bottom = ENEMY_DISPLAY + m_ey + main->GetScrollY();

		//3�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
		Draw::Draw(49, &src, &dst, c, 0.0f);
	}
}





