#include "GameHead.h"
#include "UtilityModule.h"
#include "GameL/UserData.h"   
#include <ctime>      
#include <cstdlib>     

//---UnitVec関数
/*引数１ float* vx  ; ベクトルのX成分のポインタ
　引数２ float* vy  ; ベクトルのY成分のポインタ
  戻り値　bool　　　; true=計算成功　false=計算失敗
  内容
  引数ベクトルを正規化しその値をvx,vyに変更します。*/
bool UnitVec(float* vx, float* vy)
{
	//ベクトルの長さを決める（三平方の定理）
    float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);//rをルートを求める


	//長さが０かどうか調べる
	if (r == 0.0f)
	{
		//０なら計算失敗
		return false;
	}
	else
	{
		//正規化を行う
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);

	}

	return true;
}
//GetAtan2Angle関数
/*引数１　float w   :幅
　引数２　float h   :高さ
  戻り値　float     :角度（０°～360°）
  内容
  高さと幅から直角三角形があると仮定しその角度を求める*/
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180°～0°を180°～360°に変換
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}


//MapChange関数
/*
引数１　int m     :map切り替え用変数
引数２　int m_map :切り替えるマップデータをぶち込むメインマップ変数
戻り値　無し
切り替え用のマップをメインマップ変数にぶち込む関数
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
//RoomMapChange関数
/*
引数１　int m     :map切り替え用変数
引数２　int m_map :切り替えるマップデータをぶち込むメインマップ変数
戻り値　無し
切り替え用の教室マップをメイン教室マップ変数にぶち込む関数
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
//SpawnChangerX関数
/*
引数１　int m     :map切り替え用変数
戻り値　float
ステージごとの主人公の初期位置を返す変数
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
//SpawnChangerY関数
/*
引数１　int m     :map切り替え用変数
戻り値　float
ステージごとの主人公の初期位置を返す変数
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
//HitBoxChanger関数
/*
引数　１　　　int m　               :マップ切り替え管理用変数
引数　２　　　int map[MAP_X][MAP_Y  :マップ情報
戻り値　無し
マップ切り替え時にギミックのヒットボックスを変更する関数
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

						//gimmickオブジェクト作成
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

//EnemySpawnChanger関数
/*引数１　　int m　　　　　　　　　　　　：現在のステージ情報
　引数２    int m_map[MAP_X][MAP_Y]　　　:マップ情報
  引数３    bool room_in　　　　　　　　：教室内外判定
  戻り値　　無し
  ステージごとの敵出現用関数
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

						//ステージ１の敵オブジェクト作成
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

						//ステージ２の敵オブジェクト作成
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

						//ステージ３の敵オブジェクト作成
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

						//ステージ４の敵オブジェクト作成
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

						//ステージ５の敵オブジェクト作成
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

						//ステージ６の敵オブジェクト作成
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

						//ステージ７の敵オブジェクト作成
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

						//ステージ８の敵オブジェクト作成
						CObjEnemy* obje8 = new CObjEnemy(j*64.0f, i*64.0f);
						Objs::InsertObj(obje8, OBJ_ENEMY, 11);


					}
				}

			}
		}
	}

}


