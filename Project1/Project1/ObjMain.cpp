//�g�p����w�b�_�[�t�@�C��
#include <stdio.h>

#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjMain.h"
#include "ObjText.h"
#include "UtilityModule.h"



//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMain::CObjMain(int map[ROOM_X][ROOM_Y])
{
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));
}





//�C�j�V�����C�Y
void CObjMain::Init()
{
	m_scroll_x = -64.0f*7;
	m_scroll_y = -64.0f*7;

	room_chg_stop = false;

	map_chg = 0;
	room_chg = 0;
	stop_flg = true;
	spawn_pointX[7] = NULL;
	spawn_pointY[7] = NULL;
	room_in = true;
	delete_flg = false;
	first_stop = true;

	m_ani_time = 4;
	m_ani_max_time = 4;

	switch_flg = true;

	pepepe = false;
	pepepe_2 = false;
	room_chg_stop = false;

	nothing_flg = false;
	open_flg = false;
	m_time = 0;

	//�����}�b�v�f�[�^
	r[ROOM_1] = Save::ExternalDataOpen(L"�����U�E�T�N��.csv", &size);
	r[ROOM_2] = Save::ExternalDataOpen(L"�����Q�E�T�N��.csv", &size);
	r[ROOM_3] = Save::ExternalDataOpen(L"�����R�E�T�N��.csv", &size);
	r[ROOM_4] = Save::ExternalDataOpen(L"�����S�E�T�N��.csv", &size);
	r[ROOM_5] = Save::ExternalDataOpen(L"�����T�E�T�N��.csv", &size);
	r[ROOM_6] = Save::ExternalDataOpen(L"�����P�E�T�N��.csv", &size);

	//�L���}�b�v�f�[�^
	p[FLOOR8] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��8�K.csv", &size);
	p[FLOOR7] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��7�K.csv", &size);
	p[FLOOR6] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��6�K.csv", &size);
	p[FLOOR5] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��5�K.csv", &size);
    p[FLOOR4] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��4�K.csv", &size);
	p[FLOOR3] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��3�K.csv", &size);
    p[FLOOR2] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��2�K.csv", &size);
	p[FLOOR1] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��1�K.csv", &size);
	p[FLOOR_NULL] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��1�K.csv", &size);

}

//�A�N�V����
void CObjMain::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (Input::GetVKey('R') == true)
	{
		if (map_chg > 0)
		{
			spawn_pointX[map_chg] = SpawnChangerX(map_chg);
			spawn_pointY[map_chg] = SpawnChangerY(map_chg);
			m_scroll_x = -spawn_pointX[map_chg];
			m_scroll_y = -spawn_pointY[map_chg];
		}
		else
		{
			hero->SetX(0.0f);
			hero->SetY(BLOCK_SIZE_Y * 4);
			m_scroll_x = 0.0f;
			m_scroll_y = 0.0f;
		}
	}
	
	searchpoint_font_flg = false;
	//�X�e�[�W�����ړ��R�}���h
	if (Input::GetVKey(VK_SPACE) == true)
	{
		//�L���}�b�v�����̘L���}�b�v
		if (switch_flg == true&&room_in==false)
		{
			stop_flg = true;
			stop_flg2 = true;
			first_stop = true;
			
			nothing_flg = false;
			map_chg++;
			if (map_chg == GAME_CLEAR)
			{
				Scene::SetScene(new CSceneEPI);
			}
			switch_flg = false;
		}
		//�����}�b�v���L���}�b�v
		else if (switch_flg == true && room_in == true)
		{
			room_in = false;
			stop_flg = true;

			switch_flg = false;
		}
	
	}
	//���͏d���j�~�t���O
	else
	{
		switch_flg = true;
	}
	//�����}�b�v���U��񂵂���Z�[�u�����}�b�v�ւ̃��[�h�ɐ؂�ւ���
	if (room_chg >= ROOM_LIMIT)
	{
		room_chg = ROOM_1;
		room_chg_stop = true;
	}
	//�W�K�̃}�b�v�̏���
	if (map_chg == FLOOR8)
	{
		//�L���}�b�v���狳���}�b�v�ւ̐؂�ւ�����
		if (room_chg >= ROOM_1 && room_in == true && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(4, L"4������SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(4);

			//��l���̏����ʒu��ύX
			
			hero->SetX(ROOM_SPAWN_X*BLOCK_SIZE_X);
			hero->SetY(ROOM_SPAWN_Y*BLOCK_SIZE_Y);
			m_scroll_x = ROOM_SPAWN_SCROLL_X * BLOCK_SIZE_X;
			m_scroll_y = ROOM_SPAWN_SCROLL_Y * BLOCK_SIZE_Y;

			//�V�K�Ƀ}�b�v�����[�h���鏈���ƃZ�[�u�����}�b�v�����[�h���鏈���̐؂�ւ�
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

					}
				}

			}
		}
		//�����̋�������L���ւ̃}�b�v�؂�ւ��i�P�x�����񂳂Ȃ��j
		if (room_in == false && stop_flg == true && first_stop == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			//�}�b�v�؂�ւ��֐����Ăяo��
			MapChanger(map_chg, m_map, p);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(0.0f);
			hero->SetY(BLOCK_SIZE_Y * 4);
			m_scroll_x = 0.0f;
			m_scroll_y = 0.0f;

			


			first_stop = false;
		}
		else if (room_in == false && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			
		}

	}
	//�V�K�ȍ~�̃}�b�v�̏���
	if (map_chg >= FLOOR7)
	{
		if (map_chg >=1 && stop_flg == true&&first_stop==true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);
			
			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//�}�b�v�؂�ւ��֐����Ăяo��
			MapChanger(map_chg, m_map, p);
			
			hero->SetFlug(false);
	
			//��l���̏����ʒu�̒l���֐��Ŏw�肷��
			spawn_pointX[map_chg] = SpawnChangerX(map_chg);
			spawn_pointY[map_chg] = SpawnChangerY(map_chg);
			
			
			m_scroll_x = -spawn_pointX[map_chg];
			m_scroll_y = -spawn_pointY[map_chg];

			first_stop = false;
		}
		else if(stop_flg==true&&room_in==false)
		{
			memcpy(m_map, save_map, sizeof(int)*(MAP_X*MAP_Y));
		}
		//�L���}�b�v����}�b�v�ւ̐؂�ւ�����
		else if (room_chg >= 1 && room_in == true && stop_flg == true)
		{
			//���y���̓ǂݍ���
   			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(ROOM_SPAWN_X*BLOCK_SIZE_X);
			hero->SetY(ROOM_SPAWN_Y*BLOCK_SIZE_Y);
			m_scroll_x = ROOM_SPAWN_SCROLL_X * BLOCK_SIZE_X;
			m_scroll_y = ROOM_SPAWN_SCROLL_Y * BLOCK_SIZE_Y;
			//�V�K�Ƀ}�b�v�����[�h���鏈���ƃZ�[�u�����}�b�v�����[�h���鏈���̐؂�ւ�
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

					}
				}
			}
		}


	}


	
	float hx = hero->GetX();
	float hy = hero->GetY();

	//����X�N���[�����C��
	if (hx < SCROLL_RIGHT)
	{
		hero->SetX(SCROLL_RIGHT);
		m_scroll_x -= hero->GetVX();
	}
	//�O���X�N���[�����C��
	if (hx > SCROLL_LEFT)
	{
		hero->SetX(SCROLL_LEFT);
		m_scroll_x -= hero->GetVX();
	}
	//����X�N���[�����C��
	if (hy < SCROLL_UP)
	{
		hero->SetY(SCROLL_UP);
		m_scroll_y -= hero->GetVY();
	}

	//�����X�N���[�����C��
	if (hy > SCROLL_DOWN)
	{
		hero->SetY(SCROLL_DOWN);
		m_scroll_y -= hero->GetVY();


	}

	//�M�~�b�N�̃q�b�g�{�b�N�X���}�b�v���ƂɕύX���鏈��
	if (stop_flg == true)
	{
		stop_flg2 = false;

		HitBoxChanger(map_chg, m_map, room_in, room_chg, r_map);
		EnemySpawnChanger(map_chg, m_map, room_in);

		


	}

	//�G���o������t���O�i�q�b�g�{�b�N�X�j���������F�c���C��
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (m_map[i][j] == SPAWN_ENEMY_Y)
			{
				if ((j*BLOCK_SIZE_X) + BLOCK_SIZE_X >= hero->GetX() && (j * BLOCK_SIZE_X) - BLOCK_SIZE_X <= hero->GetX())
				{

					
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * BLOCK_SIZE_X) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

					//�����|�C���g�����ɕύX
					m_map[i][j] = FLOOR_0;
				}
			}
		}
	}
	
	//�G���o������t���O�i�q�b�g�{�b�N�X�j���������F�����C��
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (m_map[i][j] == SPAWN_ENEMY_X)
			{
				if ((i*BLOCK_SIZE_Y) + BLOCK_SIZE_Y >= hero->GetY() && (i *BLOCK_SIZE_Y) - BLOCK_SIZE_Y <= hero->GetY())
				{

					
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * BLOCK_SIZE_X) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);
					//�����|�C���g�����ɕύX
					m_map[i][j] = FLOOR_0;
				}
			}
		}
	}
	//�A�C�e���u���v�̐��������F�����p
	if (stop_flg == true && room_in == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (r_map[i][j] == MAP_KEY)
				{

					
					CObjItem * obji = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(obji, OBJ_ITEM, 16);

				}
			}
		}
	}
	//�A�C�e���u���v�̐��������F�L���p
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_KEY)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjItem * objir = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objir, OBJ_ITEM, 16);




				}
			}

		}
	}
	//�A�C�e���u��v�̕\�������F�L���p
	if (room_in == false && stop_flg == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_HEAL)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}




	//�A�C�e���u��v�̕\�������F�����p
	if (stop_flg == true && room_in == true)
	{

		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_HEAL)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}
	//�A�C�e���u�o�[���̂悤�Ȃ��́v�̕\�������F�L���p
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_BAR)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}
	}
	//�A�C�e���u�o�[���̂悤�Ȃ��́v�̕\�������F�����p
	if (room_in == true && stop_flg == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_BAR)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}

	}
	//�����擾�����ۂɓG�𐶐����鏈��
	if (hero->GetEnemyFlag() == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == FAST_ENEMY)
				{


					CObjFastEnemy* objf = new CObjFastEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_FASTENEMY, 13);

					m_map[i][j] = FLOOR_0;

				}
			}
		}
	}

		stop_flg = false;
	
}
	
	



/*���ϊ֐�
�@����1,2 float   ax  ,  ay  :A�x�N�g��
  ����3,4 float   bx  ,  by  :B�x�N�g��
  �߂�l�@float   �F�ˉe
  ���e�@A�x�N�g����B�x�N�g���ē��ς��s���ˉe�����߂�*/
float CObjMain::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}

/*�O�ϊ֐�
�@����1,2 float   ax  ,  ay  :A�x�N�g��
  ����3,4 float   bx  ,  by  :B�x�N�g��
  �߂�l�@float   �F�ˉe
  ���e�@A�x�N�g����B�x�N�g���ē��ς��s���ˉe�����߂�*/
float CObjMain::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//���������߂�}�N��
#define SGN(x) 1-(x<=0)-(x<0)

/*���Ɛ��̌�������֐�
  �����@float 1, 2  a1_x,a1y            :���x�N�g��A�̎n�_
  �����@float 3, 4  a2x,a2y             :���x�N�g��A�̏I�_
  �����@float 5, 6  b1x,b1y             :���x�N�g��A�̎n�_
  �����@float 7, 8  b2x,b2y             :���x�N�g��A�̎n�_
  �����@float 9, 10  out_px,out_py      :���x�N�g��A�̎n�_
  �߂�l�@bool  :true=��_�L��@false=��_����
  ���e�F������A�EB�x�N�g���̌�_�������Aout_px��out_py�̕Ԃ�*/
bool CObjMain::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//�G���[�R�[�h
	*out_px = -99999.0f; *out_py = -99999.0f;

	//A�x�N�g���쐬(a2��a1)
	float ax = a2x - a1x;  float ay = a2y - a1y;

	//B�x�N�g���쐬(b2��b1)
	float bx = b2x - b1x;  float by = b2y - b1y;

	//C�x�N�g���쐬(b1��a1)
	float cx = b1x - a1x;  float cy = b1y - a1y;

	//D�x�N�g���쐬(b2��a1)
	float dx = b2x - a1x;  float dy = b2y - a1y;
	//A X C�̎ˉe��A X B�̎ˉe�����߂�
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);
	//���������������ɂȂ��Ă��邩�ǂ����`�F�b�N
	if (SGN(t1) == SGN(t2))
		return false;
	//�ˉe�̐�Βl��
	t1 = abs(t1);  t2 = abs(t2);

	//��_�����߂�
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//AP�x�N�g���i����a1�j
	float apx = px - a1x;  float apy = py - a1y;

	//BP�x�N�g���ip��a2)
	float bpx = px - a2x;  float bpy = py - a2y;

	//A�EAP�̎ˉe��A�EBP�̎ˉe�����߂�
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//�����`�F�b�N
	if (SGN(w1) == SGN(w2))
		return false; //��_���O

	//��_��Ԃ�
	*out_px = px; *out_py = py;

	return true;

}

/*��l���ƕǂ̌�������֐�
�@����1,2 float  x,y          :��l���̈ʒu
  ����3,4 float  vx,vy        :��l���̈ړ��x�N�g��
  ����5,6 float* out_px,out_y :Block�Ƃ̌�_
  ����7   float* out          :�ꂩ���_�܂ł̋���
  ��l���̈ʒu�{�ړ��x�N�g���Ɗe�u���b�N�̕ςōD�]�̔�����s��
  �ł��߂���_�̈ʒu�Ƌ�����Ԃ�*/
bool CObjMain::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float *out_len
)

{
	
	bool pb = false;      //��_�m�F�p
	float len = 99999.0f; //��_�Ƃ̋���
	//�u���b�N�̕Ӄx�N�g��
	float edge[4][4] =
	{
		{ 0, 0,64, 0},
		{64, 0,64,64},
		{64,64, 0,64},
		{ 0,64, 0, 0},
	};

	//m_map�̑S�v�f�ɃA�N�Z�X
	//�L���p
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
				{
					//�u���b�N�̂S�ӂ����_��T��
					for (int k = 0; k < 4; k++)
					{
						//��_��T��
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//��_�`�F�b�N
						if (b == true)
						{
							//��_�Ƃ̋��������߂�
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//��������_�̒��ōł��������Z�����̂�T��
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	//�����p
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{
					//�u���b�N�̂S�ӂ����_��T��
					for (int k = 0; k < 4; k++)
					{
						//��_��T��
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],&px, &py);

						//��_�`�F�b�N
						if (b == true)
						{
							//��_�Ƃ̋��������߂�
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//��������_�̒��ōł��������Z�����̂�T��
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	*out_len = len;
	return pb;


}
/*BlockHit�֐�
  �����P�@�@float* x             :������s��object��X�ʒu
  �����Q�@�@float* y             :������s��object��Y�ʒu
  �����R�@�@bool  scroll_on_x    :������s��object�̓X�N���[���ɉe����^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
  �����T�@�@bool* up             :�㉺���E����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
  �����U�@�@bool* down           :�㉺���E����̉������ɂ������Ă��邩�ǂ�����Ԃ�
  �����V�@�@bool* left           :�㉺���E����̍������ɂ������Ă��邩�ǂ�����Ԃ�
  �����W�@�@bool* right          :�㉺���E����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
  �����X�@�@float* vx            :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
  �����P�O�@�@float* vy            :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
  �����P�P�@int* bt            �@:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
  �����P�Q�@int *c_id            :���莞�ɓ������Ă���L�����N�^�[��ID
  �����P�Q�@int *k_id            :���莞�ɓ������Ă���L�����N�^�[�̃A�C�e���i���j��ID
  ��{�����@������s��object�ƃu���b�N64*64����ŁA�����蔻��Ə㉺���E������s��
  ���̌��ʂ͈����S�`�P�O�ɕԂ��B�i�L���}�b�v�p�Ƌ����}�b�v�p�̓��ށj
  
  ���p�����@�����̔��i�㉺���E�j�ɐڐG������E�L�[���������ۂɘL���}�b�v���狳���}�b�v�����}�b�v����L���}�b�v�ɐ؂�ւ���
  �܂�����Ȕ��i�A�C�e�����g��Ȃ��ƊJ���Ȃ����j�ɐڐG������l�����A�C�e���i�K�т��o�[���̂悤�Ȃ��́j�������Ă��邩�ǂ������ʂ��A
  �����Ă���ΊJ�������o���o�Ēʏ�̔��Ɠ��l�ɏo�邱�Ƃ��ł���B

  �K�i�i�㉺���E�j�ڐG������l�����J�M��҂��Ă��邩���ʂ������Ă���Ύ��̊K�w�֐i�ނ��Ƃ��ł���B
  �����Ă��Ȃ���΁A�������X���[����B

  �A�C�e����{�A�{�I�̏Փ˔�������A���ׂ�y�ю擾�ł���t���O�𗧂Ă�

  */

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt, int *c_id, int *k_id
)
{
	

	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���u���b�N�̎�ނ̏�����
	*bt = 0;

	//�֐����Ŏg���I�u�W�F�N�g�A�h���X�ꗗ
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	CObjItem* item = (CObjItem*)Objs::GetObj(OBJ_ITEM);
	CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
	CObjGameUI* UI = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
	CObjClickTitle* Title = (CObjClickTitle*)Objs::GetObj(OBJ_CLICK_TITLE);
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//m=map�̑S�v�f�ɃA�N�Z�X
	//�L���p
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{


				if (m_map[i][j] <= MAP_NULL && m_map[i][j] >=STAIRS&&m_map[i][j]!=MAP_KEY && m_map[i][j] != MAIN_ENEMY &&
					m_map[i][j] != GIMMICK && m_map[i][j] != FLOOR_5 && m_map[i][j] != FLOOR_6 && m_map[i][j] != FLOOR_7 
					)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;



					//�X�N���[���̉e��
     				float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;

					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) <= bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) &&( *y + (-scroll_y) < by + BLOCK_SIZE_Y))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if(r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 88.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								*vx = -(*vx)*0.1f;//-VX*�����W��
								//�K�i
								if (m_map[i][j] == STAIRS && *c_id == CHAR_HERO && *k_id == ITEM_KEY && Input::GetVKey('E')==true)
								{
									map_chg++;
									if (map_chg == GAME_CLEAR)
									{
										Scene::SetScene(new CSceneEPI);
									}
									stop_flg = true;
									
									stop_flg2 = true;
									first_stop = true;
									room_chg_stop = false;
									*k_id = ITEM_NULL;
									hero->SetUseItem(true);
									UI->Settakeflag(false);
									
									nothing_flg = false;


								

								
									
								}
								//��
								else if (m_map[i][j] == DOOR_LEFT  && *c_id == CHAR_HERO && Input::GetVKey('E') == true)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//item->SetFlag(true);
										
										room_chg++;
								
									
										searchpoint_font_flg = true;


										save_x[map_chg][0] = hero->GetX()+BLOCK_SIZE_X;
										save_y[map_chg][0] = hero->GetY()+ BLOCK_SIZE_Y;
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								
								
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - BLOCK_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								*vy = 0.0f;//-VX*�����W��
								
								//�K�i
								if (m_map[i][j] == STAIRS && *c_id == CHAR_HERO && *k_id == ITEM_KEY && Input::GetVKey('E') == true)
								{
									map_chg++;

									if (map_chg == GAME_CLEAR)
									{
										Scene::SetScene(new CSceneEPI);
									}

									
									
									*k_id = ITEM_NULL;
									hero->SetUseItem(true);
									UI->Settakeflag(false);

									stop_flg = true;
									stop_flg2 = true;
									first_stop = true;
									room_chg_stop = false;
									nothing_flg = false;
									
									
								}
							    //��
								else if (m_map[i][j] == DOOR_DOWN  && *c_id == CHAR_HERO&&Input::GetVKey('E'))
								{
									if (room_in == false)
									{
										searchpoint_font_flg = true;

										keepout_font_flg = true;
									}

								}
								
							
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								*vx = -(*vx)*0.1f;//-VX*�����W��
								//�K�i
								if (m_map[i][j] == STAIRS && *c_id == CHAR_HERO && *k_id == ITEM_KEY && Input::GetVKey('E') == true)
								{
									map_chg++;

									if (map_chg == GAME_CLEAR)
									{
										Scene::SetScene(new CSceneEPI);
									}

									stop_flg = true;
									stop_flg2 = true;
									first_stop = true;
									nothing_flg = false;

									room_chg_stop = false;
									*k_id = ITEM_NULL;
									hero->SetUseItem(true);
									UI->Settakeflag(false);

									
									

									

									
								}
								//��
								else if (m_map[i][j] == DOOR_RIGHT&& *c_id == CHAR_HERO && Input::GetVKey('E') == true)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										room_chg++;
										searchpoint_font_flg = true;
									
										save_x[map_chg][0] = hero->GetX() - BLOCK_SIZE_X;
										save_y[map_chg][0] = hero->GetY() + BLOCK_SIZE_Y;
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y =by + BLOCK_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l����
								//�����W��
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								//�K�i
								if (m_map[i][j] == STAIRS && *c_id == CHAR_HERO && *k_id == ITEM_KEY && Input::GetVKey('E') == true)
								{

									map_chg++;

									if (map_chg == GAME_CLEAR)
									{
										Scene::SetScene(new CSceneEPI);
									}

									stop_flg = true;
									stop_flg2 = true;
									first_stop = true;
									room_chg_stop = false;
									nothing_flg = false;

									searchpoint_font_flg = true;
									
									*k_id = ITEM_NULL;

									hero->SetUseItem(true);
									UI->Settakeflag(false);

									

									
									
								}
							    //��
								else if (m_map[i][j] == DOOR_UP && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{
									if (room_in == false)
									{
										keepout_font_flg = true;

									}

								}
								

							}
							if (m_map[i][j] == DOOR_UP || m_map[i][j] == DOOR_DOWN || m_map[i][j] == DOOR_LEFT || m_map[i][j] == DOOR_RIGHT)
							{
								searchpoint_font_flg = true;
							}
						}
					}

				}
			}
		}
	}
	//�����p
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{


				if (r_map[i][j] <= MAP_NULL && r_map[i][j] > FLOOR_0 && r_map[i][j] != GIMMICK && r_map[i][j] != FLOOR_7 && r_map[i][j] != CHAIR)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) < bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) <= by + BLOCK_SIZE_Y))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 87.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r > 0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								*vx = -(*vx)*0.1f;//-VX*�����W��
								
								//�{���J�������{���J������
								if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(12, L"12��̎�LSE.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(12);

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//�ʏ�̔�
								else if (r_map[i][j] == DOOR_LEFT && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{

									if (room_in == true && room_chg >= ROOM_1)
									{
										room_in = false;
										stop_flg = true;

										searchpoint_font_flg = true;
										//��l�������ɓ��������u�Ԃɕۑ����Ă����ʒu�ƃX�N���[������������B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										
										for (int i = 0; i < ROOM_X; i++)
										{
											for (int j = 0; j < ROOM_Y; j++)
											{
												save_room_map[i][j][room_chg] = r_map[i][j];
											}
										}
										
									}
									//�o�[�����g��Ȃ��ƊJ���Ȃ���
									else if (room_in == true && room_chg == ROOM_0)
									{
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										if (hero->Getflag_3() == true && Input::GetVKey('E'))
										{
											searchpoint_font_flg = true;
											CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
											hero->SetFlug_3(false);
											hero->SetUseItem(true);

											gui->SetID(ITEM_NULL);
											gui->Settakeflag_3(false);

											hero->SetBarID(ITEM_NULL);

											room_in = false;
											stop_flg = true;


										}
									}
								}
								

							}
						}

						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
							*y = by - BLOCK_SIZE_X + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;	//�����W��

							
							//�{���J������
							if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
							{
								searchpoint_font_flg = true;

								//���y���̓ǂݍ���
								Audio::LoadAudio(12, L"12��̎�LSE.wav", SOUND_TYPE::EFFECT);

								//���y�X�^�[�g
								Audio::Start(12);

								CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
								font_story_flg = true;
								hero->SetHeroStop(true);
							}
							//�ʏ�̔�
							else if (r_map[i][j] == DOOR_DOWN && *c_id == CHAR_HERO && Input::GetVKey('E'))
							{
								if (room_in == true && room_chg >= ROOM_1)
								{
									searchpoint_font_flg = true;

									room_in = false;
									stop_flg = true;

									//��l�������ɓ��������u�Ԃɕۑ����Ă����ʒu�ƃX�N���[������������B
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									hero->SetX(save_x[map_chg][0] + hero->GetVX());
									hero->SetY(save_y[map_chg][0] + hero->GetVY());
									main->SetScrollX(save_scroll_x[map_chg][0]);
									main->SetScrollY(save_scroll_y[map_chg][0]);

									if (room_chg >= 1)
									{
										for (int i = 0; i < ROOM_X; i++)
										{
											for (int j = 0; j < ROOM_Y; j++)
											{
												save_room_map[i][j][room_chg] = r_map[i][j];
											}
										}
									}
								}
								
							}
							
						}
							if (r > 135 && r < 225 )
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�]
								*vx = -(*vx)*0.1f;//-VX*�����W��
								
								//�{���J������
								if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(12, L"12��̎�LSE.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(12);

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//�ʏ�̎�
								else if (r_map[i][j] == DOOR_RIGHT && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{
									if (room_in == true && open_flg==true)
									{
										

										room_in = false;
										stop_flg = true;

										//��l�������ɓ��������u�Ԃɕۑ����Ă����ʒu�ƃX�N���[������������B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
									else if (room_in == true && open_flg == false)
									{
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										
										if (hero->Getflag_3() == true && Input::GetVKey('E'))
										{
											searchpoint_font_flg = true;
											//���y���̓ǂݍ���
											Audio::LoadAudio(11, L"11�h�A�j��.wav", SOUND_TYPE::EFFECT);

											//���y�X�^�[�g
											Audio::Start(11);

											CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
											hero->SetFlug_3(false);
											hero->SetUseItem(true);
											gui->SetID(ITEM_NULL);
											gui->Settakeflag_3(false);

											hero->SetBarID(ITEM_NULL);

											

											open_flg = true;
											font_open_flg = true;

											hero->SetHeroStop(true);
										}
										else if (Input::GetVKey('E') == true)
										{
											font_close_flg = true;
										}
									    
									}

								}
								

							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + BLOCK_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							    if (*vy < 0)
								{
									*vy = 0.0f;
								}

								//�{�I���献����鏈��
								if (r_map[i][j] == BOOK_SHELF && Input::GetVKey('E') == true&&nothing_flg==false)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = ITEM_KEY;

									searchpoint_font_flg = true;
									
									hero->SetFlug(true);

									font_key_flg = true;

									nothing_flg = true;
								}
								else if (r_map[i][j] == BOOK_SHELF && Input::GetVKey(VK_RETURN) == true && nothing_flg == true)
								{
									font_nothing_flg = true;
								}
								//�{���J������
								else if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(12, L"12��̎�LSE.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(12);

									searchpoint_font_flg = true;

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}

								//�ʏ�̎�
								else if (r_map[i][j] == DOOR_UP && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{
									if (room_in == true)
									{
										searchpoint_font_flg = true;
										room_in = false;
										stop_flg = true;

										//��l�������ɓ��������u�Ԃɕۑ����Ă����ʒu�ƃX�N���[������������B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										if (room_chg >= ROOM_1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
									
								}
							
								
							}
							//����A�C�e���Ȃǂ̒��ׂ邱�Ƃ��ł�����̂ɓ��������ۂɎ�l���̓���Ƀt�H���g��\������
							if (r_map[i][j] == BOOK || r_map[i][j] == DOOR_UP || r_map[i][j] == DOOR_DOWN || r_map[i][j] == DOOR_LEFT || r_map[i][j] == DOOR_RIGHT || r_map[i][j] == BOOK_SHELF)
							{
								searchpoint_font_flg = true;
							}
						
					}
				}
			}
		}
	}
}

/*ItemHit�֐�
  �����P�@�@float* x             :������s��object��X�ʒu
  �����Q�@�@float* y             :������s��object��Y�ʒu
  �����R�@�@bool  scroll_on_x    :������s��object�̓X�N���[���ɉe����^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
  �����T�@�@bool* up             :�㉺���E����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
  �����U�@�@bool* down           :�㉺���E����̉������ɂ������Ă��邩�ǂ�����Ԃ�
  �����V�@�@bool* left           :�㉺���E����̍������ɂ������Ă��邩�ǂ�����Ԃ�
  �����W�@�@bool* right          :�㉺���E����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
  �����X�@�@float* vx            :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
  �����P�O�@�@float* vy            :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
  �����P�P�@int* bt            �@:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
  ������s��object�ƃA�C�e��64*32����ŁA�����蔻��Ə㉺���E������s��
  ���̌��ʂ͈����S�`�P�O�ɕԂ��i�L���}�b�v�Ƌ����}�b�v�j*/

void CObjMain::ItemHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	

	//����ł���u���b�N�̎�ނ̏�����
	*bt = 0;
	
	if (room_in == false)
	{
		//m=map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_KEY || m_map[i][j] == MAP_HEAL || m_map[i][j] == MAP_BAR)
				{



					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) <= bx + ITEM_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y >= by) && (*y + (-scroll_y) <= by + ITEM_SIZE_Y))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 87.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r>=0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + ITEM_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								*vx = -(*vx)*0.1f;//-VX*�����W��
								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{

									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;
									

									delete_flg = false;
								}

								
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - BLOCK_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{

									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								*vx= -(*vx)*0.1f;//-VX*�����W��
								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{

									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + ITEM_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{

									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								

							}
							//��
							if (m_map[i][j] == MAP_KEY)
							{
								searchpoint_font_flg = true;
								map_Item = true;
							}
							else
							{
								map_Item = false;
							}
							//��
							if (m_map[i][j] == MAP_HEAL)
							{
								searchpoint_font_flg = true;
								map_Item_2 = true;
							}
							else
							{
								map_Item_2 = false;
							}
							//�o�[��
							if (m_map[i][j] == MAP_BAR)
							{
								searchpoint_font_flg = true;
								map_Item_3 = true;
							}
							else
							{
								map_Item_3 = false;
							}

						}


					}


				}

			}

		}
	}
	//�����p
	if(room_in==true)
	{
		//m=map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_KEY || r_map[i][j] == MAP_HEAL || r_map[i][j] == MAP_BAR)
				{



					//�v�f�ԍ������W�ɕύX
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

				//�X�N���[���̉e��
				float scroll_x = scroll_on_x ? m_scroll_x : 0;
				float scroll_y = scroll_on_y ? m_scroll_y : 0;
				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll_x) + BLOCK_SIZE_X > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
				{
					//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);


					 //len��������̒����̂��Z���ꍇ����ɓ���
					 if (len < 88.0f)
					 {  
					 	 //�p�x�ō��E�𔻒�
						 if ((r < 45 && r >= 0) || r > 315)
						 {
							 //�E
							 *right = true;//��l�����猩�āA���̕������Փ˂��Ă���
							 *x = bx + ITEM_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l����
							 ix = bx / BLOCK_SIZE_X;
							 iy = by / BLOCK_SIZE_Y;

							 if (delete_flg == true)
							 {
								 //���y���̓ǂݍ���
								 Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

								 //���y�X�^�[�g
								 Audio::Start(10);

								 r_map[iy][ix] = FLOOR_0;



								 delete_flg = false;
							 }
						 }

							
						if (r > 45 && r < 135)
						{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - BLOCK_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								if (delete_flg == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}

								*vy = 0.0f;
						}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - BLOCK_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								if (delete_flg == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}
							}
							
						
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
							*y = by + ITEM_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							ix = bx / BLOCK_SIZE_X;
							iy = by / BLOCK_SIZE_X;

								if (delete_flg == true)
								{
									//���y���̓ǂݍ���
									Audio::LoadAudio(10, L"10�A�C�e������.wav", SOUND_TYPE::EFFECT);

									//���y�X�^�[�g
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


						}
						//��
						if (r_map[i][j] == MAP_KEY)
						{
							searchpoint_font_flg = true;
							map_Item = true;
						}
						else
						{
							map_Item = false;
						}
						//��
						if (r_map[i][j] == MAP_HEAL)
						{
							searchpoint_font_flg = true;
							map_Item_2 = true;
						}
						else
						{
							map_Item_2 = false;
						}
						//�o�[���̂悤�Ȃ���
						if (r_map[i][j] == MAP_BAR)
						{
							searchpoint_font_flg = true;
							map_Item_3 = true;
						}
						else
						{
							map_Item_3 = false;
						}

					 }


					}


				}

			}

		}
	}
	
}


	


//�h���[
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//��l���I�u�W�F�N�g�̃A�h���X
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > MAP_NULL_0)
				{


					//�\���ʒu�̐ݒ�
					dst.m_top = i * DRAW_SIZE + m_scroll_y;
					dst.m_left = j * DRAW_SIZE + m_scroll_x;
					dst.m_right = dst.m_left + DRAW_SIZE;
					dst.m_bottom = dst.m_top + DRAW_SIZE;


					//���e�N�X�`��
					if (m_map[i][j] == FLOOR_0 || m_map[i][j] == FLOOR_1 || m_map[i][j] == FLOOR_2 || m_map[i][j] == FLOOR_3 || m_map[i][j] == FLOOR_4 || m_map[i][j] == FLOOR_5 || m_map[i][j] == FLOOR_6 || m_map[i][j] == FLOOR_7)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}

					
					//�K�i�e�N�X�`��
					if (m_map[i][j] == STAIRS)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					//�ǃe�N�X�`���S��
					if (m_map[i][j] == WALL_UP)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_RIGHT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_LEFT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_DOWN)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}//�ǃe�N�X�`���S��

					//���e�N�X�`���S��
					if (m_map[i][j] == DOOR_UP)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == DOOR_DOWN)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == DOOR_LEFT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == DOOR_RIGHT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//���e�N�X�`���S��
					 //�Ǌp4��
					if (m_map[i][j] == WALL_ANGLE1)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE2)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE4)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//�p��4��

					 //�Ǌp�Q�E4��
					if (m_map[i][j] == WALL_ANGLE5)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(38, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE6)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(39, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE8)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(41, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE7)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(40, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == WALL_ANGLE9)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(41, &src, &dst, c, 0.0f);
					}
					//�p�ǂQ�E5��
					if (m_map[i][j] == HOLE)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(58, &src, &dst, c, 0.0f);
					}
				}
			}

		}
	}
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > MAP_NULL_0)
				{


					//�\���ʒu�̐ݒ�
					dst.m_top = i * DRAW_SIZE + m_scroll_y;
					dst.m_left = j * DRAW_SIZE + m_scroll_x;
					dst.m_right = dst.m_left + DRAW_SIZE;
					dst.m_bottom = dst.m_top + DRAW_SIZE;


					//���e�N�X�`��
					if (r_map[i][j] >= FLOOR_0 && r_map[i][j] <= FLOOR_8 || r_map[i][j] == FLOOR_2  ||
						r_map[i][j] == FLOOR_3 ||r_map[i][j] == FLOOR_4 || r_map[i][j] == FLOOR_5 || r_map[i][j] == FLOOR_7 ||
						r_map[i][j] == FLOOR_10 || r_map[i][j] == FLOOR_11 || r_map[i][j] == FLOOR_12 || r_map[i][j] == FLOOR_13 || r_map[i][j] == FLOOR_14
						)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//���܂Ƃ�
					if (r_map[i][j] == DESK)
					{
						src.m_top = 100.0f;
						src.m_left = 350.0f;
						src.m_right = src.m_left + 200.0f;
						src.m_bottom = src.m_top + 200.0f;

						Draw::Draw(30, &src, &dst, c, 0.0f);
					}
					//�֎q�܂Ƃ�
					if (r_map[i][j] == CHAIR)
					{
						src.m_top = 50.0f;
						src.m_left = 320.0f;
						src.m_right = src.m_left + 180.0f;
						src.m_bottom = src.m_top + 180.0f;

						Draw::Draw(31, &src, &dst, c, 0.0f);
					}
					
					//�ǃe�N�X�`��4��
					if (r_map[i][j] == WALL_UP || r_map[i][j] == BOOK_SHELF)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_RIGHT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_LEFT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_DOWN)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}//�ǃe�N�X�`���S��

					//���e�N�X�`��4��
					if (r_map[i][j] == DOOR_UP)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == DOOR_DOWN)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == DOOR_LEFT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == DOOR_RIGHT)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_DOOR_SIZE;
						src.m_bottom = src.m_top + DRAW_DOOR_SIZE;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//���S��

					 //�Ǌp4��
					if (r_map[i][j] == WALL_ANGLE1)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_ANGLE2)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_ANGLE3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == WALL_ANGLE4)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_FIX_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//�p��4��2


					//�{�I
					if (r_map[i][j] == BOOK_SHELF)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(29, &src, &dst, c, 0.0f);
					}
					//�{
					if (r_map[i][j] == BOOK)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					
					//����
					if (r_map[i][j] == TEACHING_1)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(50, &src, &dst, c, 0.0f);
					}
					//����
					if (r_map[i][j] == TEACHING_2)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(51, &src, &dst, c, 0.0f);
					}
					//����
					if (r_map[i][j] == TEACHING_3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(52, &src, &dst, c, 0.0f);
					}
					//����
					if (r_map[i][j] == TEACHING_4)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(53, &src, &dst, c, 0.0f);
					}


				}
			}
		}

	}
	//�T�[�`�|�C���g�t�H���g
	if (searchpoint_font_flg == true)
	{
		Font::StrDraw(L"E", hero->GetX()+25.0f, hero->GetY()-20.0f, 23, c);

	}


	//�o�[���̂悤�Ȃ��̎����ĂȂ���Ԃœ���ȃh�A�𒲂ׂ�Əo��t�H���g
	if (font_close_flg == true && m_time <= 100)
	{

		Font::StrDraw(L"�J���Ȃ�... ��������K�v��", 270.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_close_flg == true && m_time > 100)
	{
		font_close_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}
	//�o�[���̂悤�Ȃ��̎����Ă����Ԃœ���ȃh�A�𒲂ׂ�Əo��t�H���g
	else if (font_open_flg == true && m_time <= 90)
	{

		Font::StrDraw(L"�K�т��o�[���̂悤�Ȃ��̂��g����,", 200.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_open_flg == true && m_time > 90)
	{
		font_open_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}
	//��x�{�I�Ō����擾�����ۂ̂��ɖ{�I�𒲂ׂ�Əo��t�H���g
	else if (font_nothing_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"���������Ȃ�...", 340.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_nothing_flg == true && m_time > 150)
	{
		font_nothing_flg = false;

		m_time = 0;
	}
	//�{�I���献����肵���ۂ̃e�L�X�g�̕\���ƈ�莞�Ԃ�������e�L�X�g����������
	else if (font_key_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"������肵��...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_key_flg == true && m_time > 150)
	{
		font_key_flg = false;

		m_time = 0;
	}

	//��̃A�C�e���i���j�o�[�W����
	else if (font_key_flg2 == true && m_time <= 150)
	{


		Font::StrDraw(L"������肵��...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_key_flg2 == true && m_time > 150)
	{
		font_key_flg2 = false;

		m_time = 0;
	}
	//�����Ȃ����𒲂ׂ����̃t�H���g�\��
	else if (keepout_font_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"���͌ł�������Ă���...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (keepout_font_flg == true && m_time > 150)
	{
		keepout_font_flg = false;

		m_time = 0;
	}
	//��̃A�C�e���i�K�т��o�[���̂悤�Ȃ��́j�o�[�W����
	else if (font_bar_flg == true && m_time <= 150)
	{
		Font::StrDraw(L"�K�т��o�[���̂悤�Ȃ��̂���肵��...", 230.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_bar_flg == true && m_time > 150)
	{
		font_bar_flg = false;

		m_time = 0;
	}

	//��̃A�C�e���i��j�o�[�W����
	else if (font_heal_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"�����肵��...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_heal_flg == true && m_time > 150)
	{
		font_heal_flg = false;

		m_time = 0;
	}

	//���炷����ǂ񂾍ۂ̌�̃Z���t
	else if (font_story_flg2 == true && m_time <= 200)
	{
		Font::StrDraw(L"����������E�o���Ȃ���΁I", 270.0f, 530.0f, 25, c);
		m_time++;
	}
	else if (font_story_flg2 == true && m_time <= 400)
	{
		Font::StrDraw(L"�܂��͂����̔����J���铹���T����", 250.0f, 530.0f, 25, c);
		m_time++;
	}
	else if (font_story_flg2 == true && m_time > 400)
	{
		font_story_flg2 = false;

		m_time = 0;
	}
}
	