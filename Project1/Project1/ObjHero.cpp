//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include "UtilityModule.h"
#include "GameL/Audio.h"
#include"ObjGameUI.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjHero::Init()
{
	m_px = 64.0f*11; //位置
	m_py = 64.0f*11;
	m_vx = 0.0f; //移動ベクトル
	m_vy = 0.0f;

	m_hero_life = 3;//主人公の体力用変数




	peperon_flag = false;
	use_Item_flag = false;
	
	Conflict_flag = false;

	//blockとの衝突確認用

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	mi_hit_up = false;
	mi_hit_down = false;
	mi_hit_left = false;
	mi_hit_right = false;

	m_hero_stop = false;

	enemy_flg = false;

	m_block_type = 0;



	m_ani_time = 4;
	m_time = 10;
	m_flg =false;

	m_ani_frame = 1;//静止フレームを初期にする

	m_speed_power = 1.0f;
	m_ani_max_time = 4;
	m_ani_move = 0;

	m_posture = 1.0f; //右向き0.0ｆ　左向き1.0ｆ
	m_stamina_limid = 90.0f;

	m_id = CHAR_HERO;
	k_id = 99;
	h_id = 99;
	b_id = 99;
	hit_flag_x = false;
	hit_flag_y = false;
	//当たり判定用hitboxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//アクション
void CObjHero::Action()
{
	//ゲームメインにフラグをセットする
	CObjMain* Main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (m_hero_stop == false)
	{

		//Zキー入力で速度アップ
		if (m_stamina_limid >= 10 && Input::GetVKey(VK_LSHIFT) == true ||
			m_stamina_limid >= 10 && Input::GetVKey(VK_RSHIFT) == true)
		{

			//ダッシュ時の速度
			m_speed_power = 0.9f;
			m_ani_max_time = 4;

			m_stamina_limid -= 0.5f;
		}
		else
		{
			//通常速度
			m_speed_power = 0.6f;
			m_ani_max_time = 4;

			if (m_stamina_limid < 90.0f)
			{
				m_stamina_limid += 0.5f;
			}

		}

		//キーの入力方向
		
		if (Input::GetVKey('A') == true&&Input::GetVKey('D')!=true)
		{
			m_vx -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('W') == true&&Input::GetVKey('S') != true)
		{
			m_vy -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('S') == true&&Input::GetVKey('W') != true)
		{
			m_vy += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('D') == true && Input::GetVKey('A') != true)
		{
			m_vx += m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
	}
	else if (m_hero_stop==true&&Input::GetVKey(VK_RETURN) == true)
	{

		Main->SetStoryFlag(false);
		Main->SetStoryFlag2(true);
		m_hero_stop = false;
	}

		//主人公のアイテムと当たったフラグを持ってくる
		CObjGameUI* UI = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);


		//1番目のアイテムをとる処理
		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag() == false && Main->GetMapItem() == true)
		{
			Main->SetKeyFlag(true);
			peperon_flag = true;
			k_id = ITEM_KEY;
			Main->SetDelete(true);
			
			//Main->GetMapItem() = false;
		}

		//2番目のアイテムをとる処理
		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true)
		{
			Main->SetHealFlag(true);
			peperon_flag_2 = true;
			h_id = ITEM_HEAL;
			Main->SetDelete(true);
			
			//Main->GetMapItem_2() = false;
		}

		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true)
		{
			Main->SetBarFlag(true);
			peperon_flag_3 = true;
			b_id = ITEM_BAR;
			Main->SetDelete(true);
			
			//Main->GetMapItem_2() = false;
		}


		//1番目のアイテムを使う処理
		if (Input::GetVKey('1') == true && UI->GetItemflag() == true)
		{
			use_Item_flag = true;
			UI->Settakeflag(false);
		}

		//2番目のアイテムを使う処理
		else if (Input::GetVKey('2') == true && UI->GetItemflag_2() == true)
		{
			if (m_hero_life <= 2)
			{
				use_Item_flag_2 = true;
				m_hero_life = 30;
				UI->Settakeflag_2(false);
			}
			else if (m_hero_life == 3)
			{
				;
			}

		}

		//3番目のアイテムを使う処理
		else if (Input::GetVKey('3') == true && UI->GetItemflag_3() == true)
		{
			use_Item_flag_3 = true;
			UI->Settakeflag_3(false);
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

		//摩擦
		m_vx += -(m_vx*0.098f);
		m_vy += -(m_vy*0.098f);

		//高速移動によるblock判定
		bool b;
		float pxx, pyy, r;
		CObjMain* pbb = (CObjMain*)Objs::GetObj(OBJ_MAIN);

		if (pbb->GetScrollX() > 0)
			pbb->SetScrollX(0);

		//移動方向にrayを飛ばす
		float vx;
		float vy;

		if (m_vx > 0)
			vx = 500 - pbb->GetScrollX();
		else
			vx = 0 - pbb->GetScrollX();


		//ray判定
		b = pbb->HeroBlockCrossPoint(m_px - pbb->GetScrollX() + 32, m_py - pbb->GetScrollY() + 32, vx, 0.0f, &pxx, &pyy, &r);

		if (b == true)
		{
			//交点取得
			px = pxx + pbb->GetScrollX();
			py = pyy - pbb->GetScrollY();

			float aa = (m_px)-px;//A（交点→主人公の位置）ベクトル
			float bb = (m_px + m_vx) - px;//B（交点→主人公の移動先位置）ベクトル


			//主人公の幅分オフセット
			if (vx > 0)
				px += -64;
			else
				px += 2;


			//AとBが逆を向いている（主人公が移動先の壁を越えている）
			if (aa*bb < 0)
			{
				//移動ベクトルを（交点→主人公の位置）ベクトルにする
				m_vx = px - m_px;
			}

		}
		else
		{
			px = 0.0f;
			py = 0.0f;
		}

	Main->BlockHit(&m_px, &m_py, true, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, &m_id, &k_id
	);

		//自身のhitboxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);

		//アイテムの当たり判定実行
	Main->ItemHit(&m_px, &m_py, true, true,
		&mi_hit_up, &mi_hit_down, &mi_hit_left, &mi_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;




	//hitboxの位置の変更
	hit->SetPos(m_px, m_py);

	//敵と当たったらフラグを持てる
	CObjGameUI*ui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);

	
	
	//主人公機オブジェクトと接触したら敵削除
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr&&m_flg==false||
		hit->CheckObjNameHit(OBJ_FASTENEMY) != nullptr&&m_flg == false|| 
		hit->CheckObjNameHit(OBJ_SPWANENEMY) != nullptr&&m_flg == false)
	{
		//音楽情報の読み込み
		Audio::LoadAudio(6, L"6ダメージ音.wav", SOUND_TYPE::EFFECT);

			//音楽スタート
			Audio::Start(6);

			m_hero_life -= 1;

			m_flg = true;
			

			m_time = 300;
			if (m_hero_life == 2)
			{
				Conflict_flag = true;
			}

			if (m_hero_life == 1)
			{
				Conflict_flag2 = true;
			}

			if (m_hero_life == 0)
			{

				Scene::SetScene(new CSceneGameOver);
			}

		}

	   

		if (m_flg == true && m_time > 0)
		{
			m_time--;
		}
		else if (m_time == 0)
		{
			m_flg = false;

		}
	
	
}

void CObjHero::Draw()
{
	int AniData[4] =
	{
		0,1,2,1,

	};
	//描画カラー情報　R=RED　G=Green　B=Blue　A=Alpha（透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//スタミナバーの描画
	if (m_stamina_limid > 0 && m_stamina_limid < 90.0)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 0.0f + m_py+64.0f;
		dst.m_left = 0.0f+ m_px;
		dst.m_right = m_stamina_limid + m_px;
		dst.m_bottom = 64.0f + m_py+64.0f;

		//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	
	//主人公のダッシュ時と通常時と静止時の描画
	if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('W') == true &&m_stamina_limid>0|| 
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('W') == true && m_stamina_limid > 0)
	{
		//切り取り位置設定
		src.m_top = 192.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 256.0f;

		
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('A') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('A') == true && m_stamina_limid > 0)
	{
		//切り取り位置設定
		src.m_top = 64.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 128.0f;
		
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0)
	{
		//切り取り位置設定
		src.m_top = 128.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 192.0f;

	
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 64.0f;
		


	}
	else if (Input::GetVKey('W') == true )
	{
		//切り取り位置設定
		src.m_top = 192.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 256.0f;

		


	}
	else if (Input::GetVKey('A') == true)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;

		

	

	}
	else if (Input::GetVKey('S') == true)
	{
		//切り取り位置設定
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 192.0f;

		


	}
	else if (Input::GetVKey('D') == true)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;

	}
	else
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;
	}


	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	Draw::Draw(11, &src, &dst, c, 0.0f);
}
