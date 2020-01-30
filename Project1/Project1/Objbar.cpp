//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "Objbar.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"
#include "GameL/Audio.h"


//使用するネームスペース
using namespace GameL;

CObjbar::CObjbar(float x, float y)
{
	ix = x;
	iy = y;
}


//イニシャライズ
void CObjbar::Init()
{
	//変数初期化


	//m_px = 0.0f;
	//m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;

	//hit_flg = true;



	//当たり判定用hitboxを作成
	Hits::SetHitBox(this, ix, iy, 32, 32, ELEMENT_BLACK, OBJ_BAR, 1);


	//m_scroll_x = -2850.0f;
	//m_scroll_y = -64.0f;

	stop_flg = false;

	m_ani_max_time = 25;

	m_ani_frame = 0;

	m_ani_time = 0;


}

//アクション
void CObjbar::Action()
{
	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	//マップのデータをコピーして、アイテムを表示させる
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));
	memcpy(r_map, main->r_map, sizeof(int)*(ROOM_X * ROOM_Y));

	//主人公のアイテムと当たったフラグを持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(ix + main->GetScrollX(), iy + main->GetScrollY());

	//アイテムに当たって、なおかつ'E'を押したときにアイテムが消える処理
	if (hero->Getflag_3() == true)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	m_ani_time++;

	//アニメーションのリセット
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//アニメーションフレームのリセット
	if (m_ani_frame == 5)
	{
		m_ani_frame = 0;
	}


}

//ドロー
void CObjbar::Draw()
{
	int AniData[5] =
	{
		4,3,2,1,0,
	};

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//描画切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64.0f;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
	src.m_bottom = 64.0f;

	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	if (main->RoomFlag() == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == BAR )
				{
					if (main->GetStoryFlag() == true)
					{
						;
					}
					else
					{
						//表示位置の設定
						dst.m_top = i * 64.0f + hy;
						dst.m_left = j * 64.0f + hx;
						dst.m_right = dst.m_left + 32.0f;
						dst.m_bottom = dst.m_top + 32.0f;
					}
					Draw::Draw(54, &src, &dst, c, 0.0f);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == BAR&&main->GetStoryFlag()==false)
				{
					//表示位置の設定
					dst.m_top = i * 64.0f + hy;
					dst.m_left = j * 64.0f + hx;
					dst.m_right = dst.m_left + 32.0f;
					dst.m_bottom = dst.m_top + 32.0f;

					Draw::Draw(54, &src, &dst, c, 0.0f);
				}
			}
		}
	}
}