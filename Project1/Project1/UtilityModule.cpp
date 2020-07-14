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
切り替え用の廊下マップをメイン廊下マップ変数にぶち込む関数
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
切り替え用の教室マップはランダムに選ばれる
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
ステージごとの主人公の初期位置（X軸）を返す変数
*/
float SpawnChangerX(int m)
{
	if (m == 1)           //7階
	{
		return BLOCK_SIZE_X;
	}
	else if (m == 2)      //1階
	{
		return BLOCK_SIZE_X *34.0f;
	}

}
//SpawnChangerY関数
/*
引数１　int m     :map切り替え用変数
戻り値　float
ステージごとの主人公の初期位置（Y軸）を返す変数
*/
float SpawnChangerY(int m)
{
	if (m == 1)           //7階
	{
		return BLOCK_SIZE_Y;
	}
	else if (m == 2)      //1階
	{
		return 0.0f;
	}

}
//HitBoxChanger関数
/*
引数　１　　　int m　               :マップ切り替え管理用変数
引数　２　　　int map[MAP_X][MAP_Y  :マップ情報
戻り値　無し
ギミックのヒットボックスをマップごとに変更する関数
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

						//gimmickオブジェクト作成
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

						//gimmick２オブジェクト作成
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

						//gimmick３オブジェクト作成
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
					if (m_map[i][j] == MAIN_ENEMY)
					{
						m_map[i][j] = FLOOR_0;

						//ステージ１の敵オブジェクト作成
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

						//ステージ２の敵オブジェクト作成
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

						//ステージ３の敵オブジェクト作成
						CObjEnemy3* obje3 = new CObjEnemy3(j*BLOCK_SIZE_Y, i*BLOCK_SIZE_X);
						Objs::InsertObj(obje3, OBJ_ENEMY3, 11);
					}
				}

			}
		}
	}

}


