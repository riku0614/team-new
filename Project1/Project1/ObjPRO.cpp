//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjPRO.h"
#include "SceneMain.h"
#include "GameL/Audio.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjPRO::Init()
{
	PR = 0;
	m_time = 0;
}

//アクション
void CObjPRO::Action()
{
	if (m_time < 691)
	{
		m_time++;
	}

	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_time = 690;
	}

	if (m_time == 690)
	{
		Scene::SetScene(new CSceneMain);
	}

	/*if (PR < 2 && Input::GetVKey('P') == true)
	{
		PR++;
	}
	else if (PR >= 2 && Input::GetVKey('P') == true)
	{
		Scene::SetScene(new CSceneMain);
	}*/
}

//ドロー
//Font::StrDraw(L"出力したい文字列", x位置, y位置, 文字の大きさ, color配列);
void CObjPRO::Draw()
{
	//Font::StrDraw(L"〜カイエ〜", 317, 270, 25, c);
	//プロローグ表示
	for (int i = 0; i < 50; i++)
	{
		if (m_time <= 20)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(25, &src, &dst, f, 0.0f);
		}

		if (m_time > 20 && m_time <= 40)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(0, &src, &dst, f, 0.0f);
		}
		if (m_time > 40 && m_time <= 60)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(1, &src, &dst, f, 0.0f);
		}

		if (m_time > 60 && m_time <= 80)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(2, &src, &dst, f, 0.0f);
		}

		if (m_time > 80 && m_time <= 130)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(3, &src, &dst, f, 0.0f);
		}

		if (m_time > 130 && m_time <= 150)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(4, &src, &dst, f, 0.0f);
		}

		if (m_time > 150 && m_time <= 170)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(5, &src, &dst, f, 0.0f);
		}

		if (m_time > 170 && m_time <= 190)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(6, &src, &dst, f, 0.0f);
		}

		if (m_time > 190 && m_time <= 210)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(7, &src, &dst, f, 0.0f);
		}

		if (m_time > 210 && m_time <= 230)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(8, &src, &dst, f, 0.0f);
		}

		if (m_time > 230 && m_time <= 250)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(25, &src, &dst, f, 0.0f);
		}

		if (m_time > 250 && m_time <= 270)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(9, &src, &dst, f, 0.0f);
		}

		if (m_time > 270 && m_time <= 290)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(10, &src, &dst, f, 0.0f);
		}

		if (m_time > 290 && m_time <= 310)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(11, &src, &dst, f, 0.0f);
		}

		if (m_time > 310 && m_time <= 360)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(12, &src, &dst, f, 0.0f);
		}

		if (m_time > 360 && m_time <= 380)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(13, &src, &dst, f, 0.0f);
		}

		if (m_time > 380 && m_time <= 400)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(14, &src, &dst, f, 0.0f);
		}

		if (m_time > 400 && m_time <= 420)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(15, &src, &dst, f, 0.0f);
		}

		if (m_time > 420 && m_time <= 440)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(16, &src, &dst, f, 0.0f);
		}

		if (m_time > 440 && m_time <= 460)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(25, &src, &dst, f, 0.0f);
		}

		if (m_time > 460 && m_time <= 480)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(17, &src, &dst, f, 0.0f);
		}

		if (m_time > 480 && m_time <= 500)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(18, &src, &dst, f, 0.0f);
		}

		if (m_time > 500 && m_time <= 520)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(19, &src, &dst, f, 0.0f);
		}

		if (m_time > 520 && m_time <= 540)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(20, &src, &dst, f, 0.0f);
		}

		if (m_time > 540 && m_time <= 590)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(21, &src, &dst, f, 0.0f);
		}

		if (m_time > 590 && m_time <= 610)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(22, &src, &dst, f, 0.0f);
		}

		if (m_time > 610 && m_time <= 630)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(23, &src, &dst, f, 0.0f);
		}

		if (m_time > 630 && m_time <= 650)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(24, &src, &dst, f, 0.0f);
		}

		if (m_time > 650 && m_time <= 670)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//表示位置設定
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(25, &src, &dst, f, 0.0f);
		}
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//文字の表示
	Font::StrDraw(L"(ENTER_KEY)でスキップ", 560, 560, 20, c);
	

}