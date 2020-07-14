#include "GameHead.h"
#include "UtilityModule.h"
#include "GameL/UserData.h"   
#include <ctime>      
#include <cstdlib>     

//---UnitVec�֐�
/*�����P float* vx  ; �x�N�g����X�����̃|�C���^
�@�����Q float* vy  ; �x�N�g����Y�����̃|�C���^
  �߂�l�@bool�@�@�@; true=�v�Z�����@false=�v�Z���s
  ���e
  �����x�N�g���𐳋K�������̒l��vx,vy�ɕύX���܂��B*/
bool UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
    float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);//r�����[�g�����߂�


	//�������O���ǂ������ׂ�
	if (r == 0.0f)
	{
		//�O�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K�����s��
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);

	}

	return true;
}
//GetAtan2Angle�֐�
/*�����P�@float w   :��
�@�����Q�@float h   :����
  �߂�l�@float     :�p�x�i�O���`360���j
  ���e
  �����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�*/
float GetAtan2Angle(float w, float h)
{
	//atan2�Ŋp�x�����߂�
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180���`0����180���`360���ɕϊ�
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}


//MapChange�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�����Q�@int m_map :�؂�ւ���}�b�v�f�[�^���Ԃ����ރ��C���}�b�v�ϐ�
�߂�l�@����
�؂�ւ��p�̘L���}�b�v�����C���L���}�b�v�ϐ��ɂԂ����ފ֐�
*/
void MapChanger(int m ,int m_map[MAP_X][MAP_Y], unique_ptr<wchar_t>* p)
{
	
	int size;

	int map[MAP_X][MAP_Y];

	int count = 1;

	
	
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
				int w = 0;
				swscanf_s(&p[m].get()[count], L"%d", &w);

				map[i][j] = w;
				count += 3;

		}
	}
	memcpy(m_map, map, sizeof(int)*(MAP_X * MAP_Y));
}
//RoomMapChange�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�����Q�@int m_map :�؂�ւ���}�b�v�f�[�^���Ԃ����ރ��C���}�b�v�ϐ�
�߂�l�@����
�؂�ւ��p�̋����}�b�v�����C�������}�b�v�ϐ��ɂԂ����ފ֐�
�؂�ւ��p�̋����}�b�v�̓����_���ɑI�΂��
*/

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p)
{



	int size;

    int map[ROOM_X][ROOM_Y];

	int count = 1;

	static int random = 0;

	srand((unsigned int)time(NULL));

	random = rand() % 6 + 1;

	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			int w = 0;
			swscanf_s(&p[random].get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

		}
	}
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));

}
//SpawnChangerX�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�߂�l�@float
�X�e�[�W���Ƃ̎�l���̏����ʒu�iX���j��Ԃ��ϐ�
*/
float SpawnChangerX(int m)
{
	if (m == 1)           //7�K
	{
		return BLOCK_SIZE_X;
	}
	else if (m == 2)      //1�K
	{
		return BLOCK_SIZE_X *34.0f;
	}

}
//SpawnChangerY�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�߂�l�@float
�X�e�[�W���Ƃ̎�l���̏����ʒu�iY���j��Ԃ��ϐ�
*/
float SpawnChangerY(int m)
{
	if (m == 1)           //7�K
	{
		return BLOCK_SIZE_Y;
	}
	else if (m == 2)      //1�K
	{
		return 0.0f;
	}

}
//HitBoxChanger�֐�
/*
�����@�P�@�@�@int m�@               :�}�b�v�؂�ւ��Ǘ��p�ϐ�
�����@�Q�@�@�@int map[MAP_X][MAP_Y  :�}�b�v���
�߂�l�@����
�M�~�b�N�̃q�b�g�{�b�N�X���}�b�v���ƂɕύX����֐�
*/

void HitBoxChanger(int m, int m_map[MAP_X][MAP_Y], bool room_in, int r, int r_map[ROOM_X][ROOM_Y])
{

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (room_in == false)
	{
		if (m == 0)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == GIMMICK)
					{
						m_map[i][j] = FLOOR_0;

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick* objg = new CObjGimmick(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(objg, OBJ_GIMMICK, 11);

						CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
						gmk->SetX(i);
						gmk->SetY(j);


					}
				}

			}
		}

		if (m == 1)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == GIMMICK)
					{
						m_map[i][j] = FLOOR_0;

						//gimmick�Q�I�u�W�F�N�g�쐬
						CObjGimmick2* objg2 = new CObjGimmick2(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(objg2, OBJ_GIMMICK2, 11);

						CObjGimmick2* gmk2 = (CObjGimmick2*)Objs::GetObj(OBJ_GIMMICK2);
						gmk2->SetX(i);
						gmk2->SetY(j);


					}
				}

			}
		}

		if (m == 2)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == GIMMICK)
					{
						m_map[i][j] = FLOOR_0;

						//gimmick�R�I�u�W�F�N�g�쐬
						CObjGimmick3* objg3 = new CObjGimmick3(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(objg3, OBJ_GIMMICK3, 11);

						CObjGimmick3* gmk3 = (CObjGimmick3*)Objs::GetObj(OBJ_GIMMICK3);
						gmk3->SetX(i);
						gmk3->SetY(j);


					}
				}

			}
		}
	}
}

//EnemySpawnChanger�֐�
/*�����P�@�@int m�@�@�@�@�@�@�@�@�@�@�@�@�F���݂̃X�e�[�W���
�@�����Q    int m_map[MAP_X][MAP_Y]�@�@�@:�}�b�v���
  �����R    bool room_in�@�@�@�@�@�@�@�@�F�������O����
  �߂�l�@�@����
  �X�e�[�W���Ƃ̓G�o���p�֐�
*/

void EnemySpawnChanger(int m, int m_map[MAP_X][MAP_Y], bool room_in)
{

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (room_in == false)
	{
		if (m == 0)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == MAIN_ENEMY)
					{
						m_map[i][j] = FLOOR_0;

						//�X�e�[�W�P�̓G�I�u�W�F�N�g�쐬
						CObjEnemy* obje = new CObjEnemy(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(obje, OBJ_ENEMY, 11);



					}
				}

			}
		}
		else if (m == 1)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == MAIN_ENEMY)
					{
						m_map[i][j] = FLOOR_0;

						//�X�e�[�W�Q�̓G�I�u�W�F�N�g�쐬
						CObjEnemy2* obje2 = new CObjEnemy2(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(obje2, OBJ_ENEMY2, 11);


					}
				}

			}
		}
		else if (m == 2)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == MAIN_ENEMY)
					{

						m_map[i][j] = FLOOR_0;

						//�X�e�[�W�R�̓G�I�u�W�F�N�g�쐬
						CObjEnemy3* obje3 = new CObjEnemy3(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(obje3, OBJ_ENEMY3, 11);
					}
				}

			}
		}
	}

}


