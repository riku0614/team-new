//使用するヘッダーファイル
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



//使用するネームスペース
using namespace GameL;

CObjMain::CObjMain(int map[ROOM_X][ROOM_Y])
{
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));
}





//イニシャライズ
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

	//教室マップデータ
	r[ROOM_1] = Save::ExternalDataOpen(L"教室６右サクラ.csv", &size);
	r[ROOM_2] = Save::ExternalDataOpen(L"教室２右サクラ.csv", &size);
	r[ROOM_3] = Save::ExternalDataOpen(L"教室３右サクラ.csv", &size);
	r[ROOM_4] = Save::ExternalDataOpen(L"教室４右サクラ.csv", &size);
	r[ROOM_5] = Save::ExternalDataOpen(L"教室５右サクラ.csv", &size);
	r[ROOM_6] = Save::ExternalDataOpen(L"教室１右サクラ.csv", &size);

	//廊下マップデータ
	p[FLOOR8] = Save::ExternalDataOpen(L"チーム開発マップ案8階.csv", &size);
	p[FLOOR7] = Save::ExternalDataOpen(L"チーム開発マップ案7階.csv", &size);
	p[FLOOR6] = Save::ExternalDataOpen(L"チーム開発マップ案6階.csv", &size);
	p[FLOOR5] = Save::ExternalDataOpen(L"チーム開発マップ案5階.csv", &size);
    p[FLOOR4] = Save::ExternalDataOpen(L"チーム開発マップ案4階.csv", &size);
	p[FLOOR3] = Save::ExternalDataOpen(L"チーム開発マップ案3階.csv", &size);
    p[FLOOR2] = Save::ExternalDataOpen(L"チーム開発マップ案2階.csv", &size);
	p[FLOOR1] = Save::ExternalDataOpen(L"チーム開発マップ案1階.csv", &size);
	p[FLOOR_NULL] = Save::ExternalDataOpen(L"チーム開発マップ案1階.csv", &size);

}

//アクション
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
	//ステージ強制移動コマンド
	if (Input::GetVKey(VK_SPACE) == true)
	{
		//廊下マップ→次の廊下マップ
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
		//教室マップ→廊下マップ
		else if (switch_flg == true && room_in == true)
		{
			room_in = false;
			stop_flg = true;

			switch_flg = false;
		}
	
	}
	//入力重複阻止フラグ
	else
	{
		switch_flg = true;
	}
	//教室マップを６回回したらセーブしたマップへのロードに切り替える
	if (room_chg >= ROOM_LIMIT)
	{
		room_chg = ROOM_1;
		room_chg_stop = true;
	}
	//８階のマップの処理
	if (map_chg == FLOOR8)
	{
		//廊下マップから教室マップへの切り替え処理
		if (room_chg >= ROOM_1 && room_in == true && stop_flg == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(4, L"4教室扉SE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(4);

			//主人公の初期位置を変更
			
			hero->SetX(ROOM_SPAWN_X*BLOCK_SIZE_X);
			hero->SetY(ROOM_SPAWN_Y*BLOCK_SIZE_Y);
			m_scroll_x = ROOM_SPAWN_SCROLL_X * BLOCK_SIZE_X;
			m_scroll_y = ROOM_SPAWN_SCROLL_Y * BLOCK_SIZE_Y;

			//新規にマップをロードする処理とセーブしたマップをロードする処理の切り替え
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
		//初期の教室から廊下へのマップ切り替え（１度しか回さない）
		if (room_in == false && stop_flg == true && first_stop == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);

			//マップ切り替え関数を呼び出す
			MapChanger(map_chg, m_map, p);

			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(0.0f);
			hero->SetY(BLOCK_SIZE_Y * 4);
			m_scroll_x = 0.0f;
			m_scroll_y = 0.0f;

			


			first_stop = false;
		}
		else if (room_in == false && stop_flg == true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);

			
		}

	}
	//７階以降のマップの処理
	if (map_chg >= FLOOR7)
	{
		if (map_chg >=1 && stop_flg == true&&first_stop==true)
		{
			//音楽情報の読み込み
			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);
			
			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//マップ切り替え関数を呼び出す
			MapChanger(map_chg, m_map, p);
			
			hero->SetFlug(false);
	
			//主人公の初期位置の値を関数で指定する
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
		//廊下マップからマップへの切り替え処理
		else if (room_chg >= 1 && room_in == true && stop_flg == true)
		{
			//音楽情報の読み込み
   			Audio::LoadAudio(5, L"5マップ切り替えSE.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(5);

			//主人公の初期位置を変更
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(ROOM_SPAWN_X*BLOCK_SIZE_X);
			hero->SetY(ROOM_SPAWN_Y*BLOCK_SIZE_Y);
			m_scroll_x = ROOM_SPAWN_SCROLL_X * BLOCK_SIZE_X;
			m_scroll_y = ROOM_SPAWN_SCROLL_Y * BLOCK_SIZE_Y;
			//新規にマップをロードする処理とセーブしたマップをロードする処理の切り替え
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

	//後方スクロールライン
	if (hx < SCROLL_RIGHT)
	{
		hero->SetX(SCROLL_RIGHT);
		m_scroll_x -= hero->GetVX();
	}
	//前方スクロールライン
	if (hx > SCROLL_LEFT)
	{
		hero->SetX(SCROLL_LEFT);
		m_scroll_x -= hero->GetVX();
	}
	//上方スクロールライン
	if (hy < SCROLL_UP)
	{
		hero->SetY(SCROLL_UP);
		m_scroll_y -= hero->GetVY();
	}

	//下方スクロールライン
	if (hy > SCROLL_DOWN)
	{
		hero->SetY(SCROLL_DOWN);
		m_scroll_y -= hero->GetVY();


	}

	//ギミックのヒットボックスをマップごとに変更する処理
	if (stop_flg == true)
	{
		stop_flg2 = false;

		HitBoxChanger(map_chg, m_map, room_in, room_chg, r_map);
		EnemySpawnChanger(map_chg, m_map, room_in);

		


	}

	//敵が出現するフラグ（ヒットボックス）生成処理：縦ライン
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

					//生成ポイントを床に変更
					m_map[i][j] = FLOOR_0;
				}
			}
		}
	}
	
	//敵が出現するフラグ（ヒットボックス）生成処理：横ライン
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
					//生成ポイントを床に変更
					m_map[i][j] = FLOOR_0;
				}
			}
		}
	}
	//アイテム「鍵」の生成処理：教室用
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
	//アイテム「鍵」の生成処理：廊下用
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_KEY)
				{

					//アイテムオブジェクト作成
					CObjItem * objir = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objir, OBJ_ITEM, 16);




				}
			}

		}
	}
	//アイテム「薬」の表示処理：廊下用
	if (room_in == false && stop_flg == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_HEAL)
				{

					//アイテムオブジェクト作成
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}




	//アイテム「薬」の表示処理：教室用
	if (stop_flg == true && room_in == true)
	{

		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_HEAL)
				{

					//アイテムオブジェクト作成
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}
	//アイテム「バールのようなもの」の表示処理：廊下用
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_BAR)
				{

					//アイテムオブジェクト作成
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}
	}
	//アイテム「バールのようなもの」の表示処理：教室用
	if (room_in == true && stop_flg == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_BAR)
				{

					//アイテムオブジェクト作成
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}

	}
	//鍵を取得した際に敵を生成する処理
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
	
	



/*内積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}

/*外積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1-(x<=0)-(x<0)

/*線と線の交差判定関数
  引数　float 1, 2  a1_x,a1y            :軸ベクトルAの始点
  引数　float 3, 4  a2x,a2y             :軸ベクトルAの終点
  引数　float 5, 6  b1x,b1y             :軸ベクトルAの始点
  引数　float 7, 8  b2x,b2y             :軸ベクトルAの始点
  引数　float 9, 10  out_px,out_py      :軸ベクトルAの始点
  戻り値　bool  :true=交点有り　false=交点無し
  内容：引数のA・Bベクトルの交点を見つけ、out_pxとout_pyの返す*/
bool CObjMain::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//エラーコード
	*out_px = -99999.0f; *out_py = -99999.0f;

	//Aベクトル作成(a2←a1)
	float ax = a2x - a1x;  float ay = a2y - a1y;

	//Bベクトル作成(b2←b1)
	float bx = b2x - b1x;  float by = b2y - b1y;

	//Cベクトル作成(b1←a1)
	float cx = b1x - a1x;  float cy = b1y - a1y;

	//Dベクトル作成(b2←a1)
	float dx = b2x - a1x;  float dy = b2y - a1y;
	//A X Cの射影とA X Bの射影を求める
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);
	//符号が同じ方向になっているかどうかチェック
	if (SGN(t1) == SGN(t2))
		return false;
	//射影の絶対値化
	t1 = abs(t1);  t2 = abs(t2);

	//交点を求める
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//APベクトル（ｐ←a1）
	float apx = px - a1x;  float apy = py - a1y;

	//BPベクトル（p←a2)
	float bpx = px - a2x;  float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//符号チェック
	if (SGN(w1) == SGN(w2))
		return false; //交点が外

	//交点を返す
	*out_px = px; *out_py = py;

	return true;

}

/*主人公と壁の交差判定関数
　引数1,2 float  x,y          :主人公の位置
  引数3,4 float  vx,vy        :主人公の移動ベクトル
  引数5,6 float* out_px,out_y :Blockとの交点
  引数7   float* out          :一から交点までの距離
  主人公の位置＋移動ベクトルと各ブロックの変で好転の判定を行い
  最も近い交点の位置と距離を返す*/
bool CObjMain::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float *out_len
)

{
	
	bool pb = false;      //交点確認用
	float len = 99999.0f; //交点との距離
	//ブロックの辺ベクトル
	float edge[4][4] =
	{
		{ 0, 0,64, 0},
		{64, 0,64,64},
		{64,64, 0,64},
		{ 0,64, 0, 0},
	};

	//m_mapの全要素にアクセス
	//廊下用
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
				{
					//ブロックの４辺から交点を探す
					for (int k = 0; k < 4; k++)
					{
						//交点を探す
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//交点チェック
						if (b == true)
						{
							//交点との距離を求める
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//見つけた交点の中で最も距離が短いものを探す
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
	//教室用
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{
					//ブロックの４辺から交点を探す
					for (int k = 0; k < 4; k++)
					{
						//交点を探す
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],&px, &py);

						//交点チェック
						if (b == true)
						{
							//交点との距離を求める
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//見つけた交点の中で最も距離が短いものを探す
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
/*BlockHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  引数１２　int *c_id            :判定時に当たっているキャラクターのID
  引数１２　int *k_id            :判定時に当たっているキャラクターのアイテム（鍵）のID
  基本処理　判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４～１０に返す。（廊下マップ用と教室マップ用の二種類）
  
  応用処理　教室の扉（上下左右）に接触しかつEキーを押した際に廊下マップから教室マップ教室マップから廊下マップに切り替える
  また特殊な扉（アイテムを使わないと開かない扉）に接触しかつ主人公がアイテム（錆びたバールのようなもの）を持っているかどうか判別し、
  持っていれば開いた演出が出て通常の扉と同様に出ることができる。

  階段（上下左右）接触しかつ主人公がカギを待っているか判別し持っていれば次の階層へ進むことができる。
  持っていなければ、処理をスルーする。

  アイテムや本、本棚の衝突判定を取り、調べる及び取得できるフラグを立てる

  */

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt, int *c_id, int *k_id
)
{
	

	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるブロックの種類の初期化
	*bt = 0;

	//関数内で使うオブジェクトアドレス一覧
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	CObjItem* item = (CObjItem*)Objs::GetObj(OBJ_ITEM);
	CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
	CObjGameUI* UI = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
	CObjClickTitle* Title = (CObjClickTitle*)Objs::GetObj(OBJ_CLICK_TITLE);
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//m=mapの全要素にアクセス
	//廊下用
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
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;



					//スクロールの影響
     				float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;

					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) <= bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) &&( *y + (-scroll_y) < by + BLOCK_SIZE_Y))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if(r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 88.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r >= 0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								*vx = -(*vx)*0.1f;//-VX*反発係数
								//階段
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
								//扉
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
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - BLOCK_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
								*vy = 0.0f;//-VX*反発係数
								
								//階段
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
							    //扉
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
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								*vx = -(*vx)*0.1f;//-VX*反発係数
								//階段
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
								//扉
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
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y =by + BLOCK_SIZE_Y + (scroll_y);//ブロックの位置-主人公の
								//反発係数
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								//階段
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
							    //扉
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
	//教室用
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{


				if (r_map[i][j] <= MAP_NULL && r_map[i][j] > FLOOR_0 && r_map[i][j] != GIMMICK && r_map[i][j] != FLOOR_7 && r_map[i][j] != CHAIR)
				{
					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) < bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) <= by + BLOCK_SIZE_Y))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 87.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r > 0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								*vx = -(*vx)*0.1f;//-VX*反発係数
								
								//本を開く処理本を開く処理
								if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(12, L"12謎の手記SE.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(12);

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//通常の扉
								else if (r_map[i][j] == DOOR_LEFT && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{

									if (room_in == true && room_chg >= ROOM_1)
									{
										room_in = false;
										stop_flg = true;

										searchpoint_font_flg = true;
										//主人公が扉に当たった瞬間に保存していた位置とスクロール情報を代入する。
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
									//バールを使わないと開かない扉
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
							//上
							*down = true;//主人公から見て、下の部分が衝突している
							*y = by - BLOCK_SIZE_X + (scroll_y);//ブロックの位置-主人公の幅
							*vy = 0.0f;	//反発係数

							
							//本を開く処理
							if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
							{
								searchpoint_font_flg = true;

								//音楽情報の読み込み
								Audio::LoadAudio(12, L"12謎の手記SE.wav", SOUND_TYPE::EFFECT);

								//音楽スタート
								Audio::Start(12);

								CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
								font_story_flg = true;
								hero->SetHeroStop(true);
							}
							//通常の扉
							else if (r_map[i][j] == DOOR_DOWN && *c_id == CHAR_HERO && Input::GetVKey('E'))
							{
								if (room_in == true && room_chg >= ROOM_1)
								{
									searchpoint_font_flg = true;

									room_in = false;
									stop_flg = true;

									//主人公が扉に当たった瞬間に保存していた位置とスクロール情報を代入する。
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
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅]
								*vx = -(*vx)*0.1f;//-VX*反発係数
								
								//本を開く処理
								if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(12, L"12謎の手記SE.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(12);

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//通常の時
								else if (r_map[i][j] == DOOR_RIGHT && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{
									if (room_in == true && open_flg==true)
									{
										

										room_in = false;
										stop_flg = true;

										//主人公が扉に当たった瞬間に保存していた位置とスクロール情報を代入する。
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
											//音楽情報の読み込み
											Audio::LoadAudio(11, L"11ドア破壊音.wav", SOUND_TYPE::EFFECT);

											//音楽スタート
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
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + BLOCK_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
							    if (*vy < 0)
								{
									*vy = 0.0f;
								}

								//本棚から鍵を取る処理
								if (r_map[i][j] == BOOK_SHELF && Input::GetVKey('E') == true&&nothing_flg==false)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
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
								//本を開く処理
								else if (r_map[i][j] == BOOK && Input::GetVKey('E') == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(12, L"12謎の手記SE.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(12);

									searchpoint_font_flg = true;

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}

								//通常の時
								else if (r_map[i][j] == DOOR_UP && *c_id == CHAR_HERO && Input::GetVKey('E'))
								{
									if (room_in == true)
									{
										searchpoint_font_flg = true;
										room_in = false;
										stop_flg = true;

										//主人公が扉に当たった瞬間に保存していた位置とスクロール情報を代入する。
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
							//扉やアイテムなどの調べることができるものに当たった際に主人公の頭上にフォントを表示する
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

/*ItemHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとアイテム64*32限定で、当たり判定と上下左右判定を行う
  その結果は引数４～１０に返す（廊下マップと教室マップ）*/

void CObjMain::ItemHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	

	//踏んでいるブロックの種類の初期化
	*bt = 0;
	
	if (room_in == false)
	{
		//m=mapの全要素にアクセス
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == MAP_KEY || m_map[i][j] == MAP_HEAL || m_map[i][j] == MAP_BAR)
				{



					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + BLOCK_SIZE_X >= bx) && (*x + (-scroll_x) <= bx + ITEM_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y >= by) && (*y + (-scroll_y) <= by + ITEM_SIZE_Y))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//lenがある一定の長さのより短い場合判定に入る
						if (len < 87.0f)
						{
							//角度で左右を判定
							if ((r < 45 && r>=0) || r > 315)
							{
								//右
								*right = true;//主人公から見て、左の部分が衝突している
								*x = bx + ITEM_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								*vx = -(*vx)*0.1f;//-VX*反発係数
								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{

									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;
									

									delete_flg = false;
								}

								
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - BLOCK_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{

									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								*vx= -(*vx)*0.1f;//-VX*反発係数
								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{

									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								
							}
							if (r > 225 && r < 315)
							{
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + ITEM_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								//アイテムを取得した際にアイテムを消す処理
								if (delete_flg == true)
								{

									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									m_map[iy][ix] = FLOOR_0;

									

									delete_flg = false;
								}
								

							}
							//鍵
							if (m_map[i][j] == MAP_KEY)
							{
								searchpoint_font_flg = true;
								map_Item = true;
							}
							else
							{
								map_Item = false;
							}
							//薬
							if (m_map[i][j] == MAP_HEAL)
							{
								searchpoint_font_flg = true;
								map_Item_2 = true;
							}
							else
							{
								map_Item_2 = false;
							}
							//バール
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
	//教室用
	if(room_in==true)
	{
		//m=mapの全要素にアクセス
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == MAP_KEY || r_map[i][j] == MAP_HEAL || r_map[i][j] == MAP_BAR)
				{



					//要素番号を座標に変更
					float bx = j * BLOCK_SIZE_X;
					float by = i * BLOCK_SIZE_Y;

				//スクロールの影響
				float scroll_x = scroll_on_x ? m_scroll_x : 0;
				float scroll_y = scroll_on_y ? m_scroll_y : 0;
				//主人公とブロックの当たり判定
				if ((*x + (-scroll_x) + BLOCK_SIZE_X > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
				{
					//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//長さを求める
						float len = sqrt(rvx*rvx + rvy * rvy);


						//角度を求める
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);


					 //lenがある一定の長さのより短い場合判定に入る
					 if (len < 88.0f)
					 {  
					 	 //角度で左右を判定
						 if ((r < 45 && r >= 0) || r > 315)
						 {
							 //右
							 *right = true;//主人公から見て、左の部分が衝突している
							 *x = bx + ITEM_SIZE_X + (scroll_x);//ブロックの位置-主人公の
							 ix = bx / BLOCK_SIZE_X;
							 iy = by / BLOCK_SIZE_Y;

							 if (delete_flg == true)
							 {
								 //音楽情報の読み込み
								 Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

								 //音楽スタート
								 Audio::Start(10);

								 r_map[iy][ix] = FLOOR_0;



								 delete_flg = false;
							 }
						 }

							
						if (r > 45 && r < 135)
						{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - BLOCK_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								if (delete_flg == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}

								*vy = 0.0f;
						}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - BLOCK_SIZE_X + (scroll_x);//ブロックの位置-主人公の幅
								ix = bx / BLOCK_SIZE_X;
								iy = by / BLOCK_SIZE_Y;

								if (delete_flg == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}
							}
							
						
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公から見て、上の部分が衝突している
							*y = by + ITEM_SIZE_Y + (scroll_y);//ブロックの位置-主人公の幅
							ix = bx / BLOCK_SIZE_X;
							iy = by / BLOCK_SIZE_X;

								if (delete_flg == true)
								{
									//音楽情報の読み込み
									Audio::LoadAudio(10, L"10アイテム入手.wav", SOUND_TYPE::EFFECT);

									//音楽スタート
									Audio::Start(10);

									r_map[iy][ix] = FLOOR_0;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


						}
						//鍵
						if (r_map[i][j] == MAP_KEY)
						{
							searchpoint_font_flg = true;
							map_Item = true;
						}
						else
						{
							map_Item = false;
						}
						//薬
						if (r_map[i][j] == MAP_HEAL)
						{
							searchpoint_font_flg = true;
							map_Item_2 = true;
						}
						else
						{
							map_Item_2 = false;
						}
						//バールのようなもの
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


	


//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//主人公オブジェクトのアドレス
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > MAP_NULL_0)
				{


					//表示位置の設定
					dst.m_top = i * DRAW_SIZE + m_scroll_y;
					dst.m_left = j * DRAW_SIZE + m_scroll_x;
					dst.m_right = dst.m_left + DRAW_SIZE;
					dst.m_bottom = dst.m_top + DRAW_SIZE;


					//床テクスチャ
					if (m_map[i][j] == FLOOR_0 || m_map[i][j] == FLOOR_1 || m_map[i][j] == FLOOR_2 || m_map[i][j] == FLOOR_3 || m_map[i][j] == FLOOR_4 || m_map[i][j] == FLOOR_5 || m_map[i][j] == FLOOR_6 || m_map[i][j] == FLOOR_7)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}

					
					//階段テクスチャ
					if (m_map[i][j] == STAIRS)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					//壁テクスチャ４つ
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
					}//壁テクスチャ４つ↑

					//扉テクスチャ４つ
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
					}//扉テクスチャ４つ↑
					 //壁角4つ
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
					}//角壁4つ↑

					 //壁角２・4つ
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
					//角壁２・5つ↑
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


					//表示位置の設定
					dst.m_top = i * DRAW_SIZE + m_scroll_y;
					dst.m_left = j * DRAW_SIZE + m_scroll_x;
					dst.m_right = dst.m_left + DRAW_SIZE;
					dst.m_bottom = dst.m_top + DRAW_SIZE;


					//床テクスチャ
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
					//机まとめ
					if (r_map[i][j] == DESK)
					{
						src.m_top = 100.0f;
						src.m_left = 350.0f;
						src.m_right = src.m_left + 200.0f;
						src.m_bottom = src.m_top + 200.0f;

						Draw::Draw(30, &src, &dst, c, 0.0f);
					}
					//椅子まとめ
					if (r_map[i][j] == CHAIR)
					{
						src.m_top = 50.0f;
						src.m_left = 320.0f;
						src.m_right = src.m_left + 180.0f;
						src.m_bottom = src.m_top + 180.0f;

						Draw::Draw(31, &src, &dst, c, 0.0f);
					}
					
					//壁テクスチャ4つ
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
					}//壁テクスチャ４つ↑

					//扉テクスチャ4つ
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
					}//扉４つ↑

					 //壁角4つ
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
					}//角壁4つ↑2


					//本棚
					if (r_map[i][j] == BOOK_SHELF)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(29, &src, &dst, c, 0.0f);
					}
					//本
					if (r_map[i][j] == BOOK)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					
					//教卓
					if (r_map[i][j] == TEACHING_1)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(50, &src, &dst, c, 0.0f);
					}
					//教卓
					if (r_map[i][j] == TEACHING_2)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(51, &src, &dst, c, 0.0f);
					}
					//教卓
					if (r_map[i][j] == TEACHING_3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + DRAW_SIZE;
						src.m_bottom = src.m_top + DRAW_SIZE;

						Draw::Draw(52, &src, &dst, c, 0.0f);
					}
					//教卓
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
	//サーチポイントフォント
	if (searchpoint_font_flg == true)
	{
		Font::StrDraw(L"E", hero->GetX()+25.0f, hero->GetY()-20.0f, 23, c);

	}


	//バールのようなもの持ってない状態で特殊なドアを調べると出るフォント
	if (font_close_flg == true && m_time <= 100)
	{

		Font::StrDraw(L"開かない... 何か道具が必要だ", 270.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_close_flg == true && m_time > 100)
	{
		font_close_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}
	//バールのようなもの持っている状態で特殊なドアを調べると出るフォント
	else if (font_open_flg == true && m_time <= 90)
	{

		Font::StrDraw(L"錆びたバールのようなものを使った,", 200.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_open_flg == true && m_time > 90)
	{
		font_open_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}
	//一度本棚で鍵を取得した際のちに本棚を調べると出るフォント
	else if (font_nothing_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"もう何もない...", 340.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_nothing_flg == true && m_time > 150)
	{
		font_nothing_flg = false;

		m_time = 0;
	}
	//本棚から鍵を入手した際のテキストの表示と一定時間たったらテキストを消す処理
	else if (font_key_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"鍵を入手した...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_key_flg == true && m_time > 150)
	{
		font_key_flg = false;

		m_time = 0;
	}

	//上のアイテム（鍵）バージョン
	else if (font_key_flg2 == true && m_time <= 150)
	{


		Font::StrDraw(L"鍵を入手した...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_key_flg2 == true && m_time > 150)
	{
		font_key_flg2 = false;

		m_time = 0;
	}
	//あかない扉を調べた時のフォント表示
	else if (keepout_font_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"扉は固く閉ざされている...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (keepout_font_flg == true && m_time > 150)
	{
		keepout_font_flg = false;

		m_time = 0;
	}
	//上のアイテム（錆びたバールのようなもの）バージョン
	else if (font_bar_flg == true && m_time <= 150)
	{
		Font::StrDraw(L"錆びたバールのようなものを入手した...", 230.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_bar_flg == true && m_time > 150)
	{
		font_bar_flg = false;

		m_time = 0;
	}

	//上のアイテム（薬）バージョン
	else if (font_heal_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"薬を入手した...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_heal_flg == true && m_time > 150)
	{
		font_heal_flg = false;

		m_time = 0;
	}

	//あらすじを読んだ際の後のセリフ
	else if (font_story_flg2 == true && m_time <= 200)
	{
		Font::StrDraw(L"早くここを脱出しなければ！", 270.0f, 530.0f, 25, c);
		m_time++;
	}
	else if (font_story_flg2 == true && m_time <= 400)
	{
		Font::StrDraw(L"まずはここの扉を開ける道具を探そう", 250.0f, 530.0f, 25, c);
		m_time++;
	}
	else if (font_story_flg2 == true && m_time > 400)
	{
		font_story_flg2 = false;

		m_time = 0;
	}
}
	