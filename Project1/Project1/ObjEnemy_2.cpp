//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy_2.h"
#include "SceneMain.h"
#include "UtilityModule.h"


//使用するネームスペース
using namespace GameL;

CObjEnemy2::CObjEnemy2(float x, float y)
{
	m_ex = x;
	m_ey = y;
}
//イニシャライズ
void CObjEnemy2::Init()
{

	m_vx = 0.0f;
	m_vy = 0.0f;


	m_flg = 0;

	m_id = CHAR_ENEMY;
	k_id = 1;
	m_time = 0;
	damage_time = 0.0f;

	boost_flag = false;



	//blockとの衝突確認用

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ex, m_ey, BLOCK_SIZE_X, BLOCK_SIZE_Y, ELEMENT_ENEMY, OBJ_ENEMY, 1);

	m_ani_frame = 0;

	m_ani_time = M_ANI_TIME;

	m_ani_max_time = M_ANI_MAX_TIME;
}

//アクション
void CObjEnemy2::Action()
{

	//マップ情報の取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));
	if (main->MapChangeData() != 1)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	else if (main->RoomFlag() == false && main->GetFlug() == true)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_ex, m_ey, BLOCK_SIZE_X, BLOCK_SIZE_Y, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	}
	else if (main->GetFlug() == true && main->FirstFlag() == true)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_ex, m_ey, BLOCK_SIZE_X, BLOCK_SIZE_Y, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	}

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	float scrollx = main->GetScrollX();
	float scrolly = main->GetScrollY();
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));

	//画面内に入ると主人公を追従する
	if (m_ex<(WINDOW_MAX_X + -(scrollx)) && m_ex>(WINDOW_MIN_X + -(scrollx)) &&
		m_ey<(WINDOW_MAX_Y + -(scrolly)) && m_ey>(WINDOW_MIN_Y + -(scrolly)))
	{
		m_vx = (hx + -(scrollx)-m_ex);
		m_vy = (hy + -(scrolly)-m_ey);

		m_ani_time++;
	}
	//画面外に数秒いると主人公の近くにワープする
	else
	{
		m_time++;
		gx = (hx + -(scrollx)+(BLOCK_SIZE_X * 3)) / BLOCK_SIZE_X;
		gy = (hy + -(scrolly)+(BLOCK_SIZE_Y * 3)) / BLOCK_SIZE_Y;


		if (m_time > 300 && m_map[gy][gx] == 1 && hero->GetKeyID() == ITEM_KEY)
		{
			m_time = 0;

			m_ex = gx * 64.0f;
			m_ey = gy * 64.0f;
			m_ani_time++;
		}
	}
	


	//アニメーションのリセット
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//アニメーションフレームのリセット
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}
	//移動ベクトルの正規化
	UnitVec(&m_vy, &m_vx);

	m_ex += m_vx * ENEMY_VECTOR_X;
	m_ey += m_vy * ENEMY_VECTOR_Y;



	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//Mapの当たり判定実行
	
	main->MapHit(&m_ex, &m_ey, false, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d, &m_id, &k_id);


	

	//自身のhitboxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	if (hit != nullptr)
	{
		//hitboxの位置の変更
		hit->SetPos(m_ex + main->GetScrollX(), m_ey + main->GetScrollY());
	}

	if (main->RoomFlag() == true)
	{
		Hits::DeleteHitBox(this);
	}

}

//ドロー
void CObjEnemy2::Draw()
{
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (main->RoomFlag() == false)
	{
		//アニメーションデータ
		int AniData[4] =
		{
			0,1,1,0,

		};
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src; //描画元切り取り位置
		RECT_F dst; //描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * ENEMY_SIZE;
		src.m_right = ENEMY_SIZE + AniData[m_ani_frame] * ENEMY_SIZE;
		src.m_bottom = ENEMY_SIZE;


		//表示位置の設定
		dst.m_top = 0.0f + m_ey + main->GetScrollY();
		dst.m_left = (ENEMY_DISPLAY) + m_ex + main->GetScrollX();
		dst.m_right = (ENEMY_DISPLAY - ENEMY_DISPLAY) + m_ex + main->GetScrollX();
		dst.m_bottom = ENEMY_DISPLAY + m_ey + main->GetScrollY();

		//3番目に登録したグラフィックをsrc.dst.cの情報を元に描画
		Draw::Draw(49, &src, &dst, c, 0.0f);
	}
}





