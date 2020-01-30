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
�؂�ւ��p�̃}�b�v�����C���}�b�v�ϐ��ɂԂ����ފ֐�
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
�X�e�[�W���Ƃ̎�l���̏����ʒu��Ԃ��ϐ�
*/
float SpawnChangerX(int m)
{
	if (m == 1)
	{
		return 64.0f;
	}
	else if (m == 2)
	{
		return 64.0f * 60.0f;
	}
	else if (m == 3)
	{
		return 64.0f * 60.0f;
	}
	else if (m == 4)
	{
		return 64.0f*34.0f;
	}
	else if (m == 5)
	{
		return 64.0f*30.0f;
	}
	else if (m == 6)
	{
		return 64.0f*40.0f;
	}
	else if (m == 7)
	{
		return 64.0f*33.0f;
	}

}
//SpawnChangerY�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�߂�l�@float
�X�e�[�W���Ƃ̎�l���̏����ʒu��Ԃ��ϐ�
*/
float SpawnChangerY(int m)
{
	if (m == 1)
	{
		return 64.0f * 2;
	}
	else if (m == 2)
	{
		return 64.0f * 67.0f;
	}
	else if (m == 3)
	{
		return 64.0f * 70.0f;
	}
	else if (m == 4)
	{
		return 64.0f * 25.0f;
	}
	else if (m == 5)
	{
		return 64.0f;
	}
	else if (m == 6)
	{
		return 64.0f;
	}
	else if (m == 7)
	{
		return 64.0f;
	}

}
//HitBoxChanger�֐�
/*
�����@�P�@�@�@int m�@               :�}�b�v�؂�ւ��Ǘ��p�ϐ�
�����@�Q�@�@�@int map[MAP_X][MAP_Y  :�}�b�v���
�߂�l�@����
�}�b�v�؂�ւ����ɃM�~�b�N�̃q�b�g�{�b�N�X��ύX����֐�
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
					if (m_map[i][j] == 7)
					{
						m_map[i][j] = 1;

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick* objg = new CObjGimmick(j*64.0f, i*64.0f);
						Objs::InsertObj(objg, OBJ_GIMMICK, 11);

						CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
						gmk->SetX(i);
						gmk->SetY(j);


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
					if (m_map[i][j] == 7)
					{
						m_map[i][j] = 1;

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick2* objg2 = new CObjGimmick2(j *64.0f, i * 64.0f);
						Objs::InsertObj(objg2, OBJ_GIMMICK2, 11);

						CObjGimmick2* gmk2 = (CObjGimmick2*)Objs::GetObj(OBJ_GIMMICK2);
						gmk2->SetX(i);
						gmk2->SetY(j);


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
					if (m_map[i][j] == 7)
					{
						m_map[i][j] = 1;

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick3* objg3 = new CObjGimmick3(j*64.0f, i*64.0f);
						Objs::InsertObj(objg3, OBJ_GIMMICK3, 11);

						CObjGimmick3* gmk3 = (CObjGimmick3*)Objs::GetObj(OBJ_GIMMICK3);
						gmk3->SetX(i);
						gmk3->SetY(j);

						
					}
				}

			}
		}
		else if (m == 3)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick4* objg4 = new CObjGimmick4(j*64.0f , i*64.0f);
						Objs::InsertObj(objg4, OBJ_GIMMICK4, 11);

						CObjGimmick4* gmk4 = (CObjGimmick4*)Objs::GetObj(OBJ_GIMMICK4);
						gmk4->SetX(i);
						gmk4->SetY(j);

						m_map[i][j] = 1;
					}
				}

			}
		}
		else if (m == 4)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick5* objg5 = new CObjGimmick5(j*64.0f , i*64.0f);
						Objs::InsertObj(objg5, OBJ_GIMMICK5, 11);

						CObjGimmick5* gmk5 = (CObjGimmick5*)Objs::GetObj(OBJ_GIMMICK5);
						gmk5->SetX(i);
						gmk5->SetY(j);

						m_map[i][j] = 1;
					}
				}

			}
		}
		else if (m == 5)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick6* objg6 = new CObjGimmick6(j*64.0f, i*64.0f);
						Objs::InsertObj(objg6, OBJ_GIMMICK6, 11);

						CObjGimmick6* gmk6 = (CObjGimmick6*)Objs::GetObj(OBJ_GIMMICK6);
						gmk6->SetX(i);
						gmk6->SetY(j);

						m_map[i][j] = 1;
					}
				}

			}
		}
		else if (m == 6)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick7* objg7 = new CObjGimmick7(j*64.0f, i*64.0f);
						Objs::InsertObj(objg7, OBJ_GIMMICK7, 11);

						CObjGimmick7* gmk7 = (CObjGimmick7*)Objs::GetObj(OBJ_GIMMICK7);
						gmk7->SetX(i);
						gmk7->SetY(j);

						m_map[i][j] = 1;
					}
				}

			}
		}
		else if (m == 7)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//gimmick�I�u�W�F�N�g�쐬
						CObjGimmick8* objg8 = new CObjGimmick8(j*64.0f, i*64.0f);
						Objs::InsertObj(objg8, OBJ_GIMMICK8, 11);

						CObjGimmick8* gmk8 = (CObjGimmick8*)Objs::GetObj(OBJ_GIMMICK8);
						gmk8->SetX(i);
						gmk8->SetY(j);


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
					if (m_map[i][j] == 5)
					{
						m_map[i][j] = 1;

						//�X�e�[�W�P�̓G�I�u�W�F�N�g�쐬
						CObjEnemy* obje = new CObjEnemy(j*64.0f, i*64.0f);
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
					if (m_map[i][j] == 5)
					{
						m_map[i][j] = 1;

						//�X�e�[�W�Q�̓G�I�u�W�F�N�g�쐬
						CObjEnemy2* obje2 = new CObjEnemy2(j*64.0f , i*64.0f);
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
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�R�̓G�I�u�W�F�N�g�쐬
						CObjEnemy3* obje3 = new CObjEnemy3(j*64.0f, i*64.0f);
						Objs::InsertObj(obje3, OBJ_ENEMY3, 11);
					}
				}

			}
		}
		else if (m == 3)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�S�̓G�I�u�W�F�N�g�쐬
						CObjEnemy4* obje4 = new CObjEnemy4(j*64.0f, i*64.0f);
						Objs::InsertObj(obje4, OBJ_ENEMY4, 11);
					}
				}

			}
		}
		else if (m == 4)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�T�̓G�I�u�W�F�N�g�쐬
						CObjEnemy5* obje5 = new CObjEnemy5(j*64.0f, i*64.0f);
						Objs::InsertObj(obje5, OBJ_ENEMY5, 11);
					}
				}

			}
		}
		else if (m == 5)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�U�̓G�I�u�W�F�N�g�쐬
						CObjEnemy6* obje6 = new CObjEnemy6(j*64.0f, i*64.0f);
						Objs::InsertObj(obje6, OBJ_ENEMY6, 11);
					}
				}

			}
		}
		else if (m == 6)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�V�̓G�I�u�W�F�N�g�쐬
						CObjEnemy7* obje7 = new CObjEnemy7(j*64.0f, i*64.0f);
						Objs::InsertObj(obje7, OBJ_ENEMY7, 11);
					}
				}

			}
		}
		else if (m == 7)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 5)
					{

						m_map[i][j] = 1;

						//�X�e�[�W�W�̓G�I�u�W�F�N�g�쐬
						CObjEnemy* obje8 = new CObjEnemy(j*64.0f, i*64.0f);
						Objs::InsertObj(obje8, OBJ_ENEMY, 11);


					}
				}

			}
		}
	}

}


