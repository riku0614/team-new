//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjFastEnemy.h"
#include "SceneMain.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

CObjFastEnemy::CObjFastEnemy(float x, float y)
{
	m_ex = x;
	m_ey = y;
}
//イニシャライズ
void CObjFastEnemy::Init()
{

	m_vx = 0.0f;
	m_vy = 0.0f;


	m_flg = 0;

	m_id = CHAR_ENEMY;
	k_id = 99;


	//blockとの衝突確認用

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	m_ani_frame = 0;//描画フレーム

	m_ani_time = 4;//アニメーションフレーム動作間隔

	m_ani_max_time = 4;//アニメーション動作間隔最大値
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_FASTENEMY, 1);


}

//アクション
void CObjFastEnemy::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//マップ情報の取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float scrollx = main->GetScrollX();
	float scrolly = main->GetScrollY();

	if (m_ex<(WINDOW_MAX_X - scrollx) && m_ex>(WINDOW_MIN_X - scrollx) &&
		m_ey<(WINDOW_MAX_Y - scrolly) && m_ey>(WINDOW_MIN_Y - scrolly))
	{
		m_vx = (hx + (-scrollx) - m_ex);
		m_vy = (hy + (-scrolly) - m_ey);
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

	m_ex += m_vx * 6.5f;
	m_ey += m_vy * 6.5f;
	m_ani_time++;

	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//ブロックの当たり判定実行
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

	if (hit->CheckObjNameHit(OBJ_HERO))
	{
		//ダメージブースト処理！！
		//主人公が敵とどの角度で当たっているかどうかの判定
		HIT_DATA** hit_data;

		hit_data = hit->SearchObjNameHit(OBJ_HERO);

		//hit_data[0]->rに当たった相手との角度がある。
		float r = hit_data[0]->r;

		//右に当たった場合
		if ((r < 45 && r >= 0) || r > 315)
		{
			hero->SetVX(+20.0f);
		}
		//左に当たった場合
		if (r > 135 && r < 225)
		{
			hero->SetVX(-20.0f);
		}

		//下に当たった場合
		if (r > 45 && r < 135)
		{
			hero->SetVY(-20.0f);
		}

		//上に当たった場合
		if (r > 225 && r < 315)
		{
			hero->SetVY(+20.0f);
		}
	}

}

//ドロー
void CObjFastEnemy::Draw()
{
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (main->RoomFlag() == false)
	{
		//アニメーションデータ
		int AniData[4] =
		{
			0,1,1,0,

		};
		float c[4] = { 1.0f,0.0f,0.0f,1.0f };

		RECT_F src; //描画元切り取り位置
		RECT_F dst; //描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 512.0f;
		src.m_right = 512.0 + AniData[m_ani_frame] * 512.0f;
		src.m_bottom = 512.0f;


		//表示位置の設定
		dst.m_top = 0.0f + m_ey + main->GetScrollY();
		dst.m_left = (128.0) + m_ex + main->GetScrollX();
		dst.m_right = (128 - 128.0f) + m_ex + main->GetScrollX();
		dst.m_bottom = 128.0f + m_ey + main->GetScrollY();

		//3番目に登録したグラフィックをsrc.dst.cの情報を元に描画
		Draw::Draw(57, &src, &dst, c, 0.0f);
	}

}