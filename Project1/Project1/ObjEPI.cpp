//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjEPI.h"
#include "SceneMain.h"
#include "GameL/Audio.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjEPI::Init()
{
	PR = 0;
	m_time = 0;
}

//アクション
void CObjEPI::Action()
{
	if (m_time < 761)
	{
		m_time++;
	}

	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_time = 760;
	}

	if (m_time == 760)
	{
		Scene::SetScene(new CSceneGameClear);
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
void CObjEPI::Draw()
{
	for (int i = 0; i < 14; i++)
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

			Draw::Draw(0, &src, &dst, f, 0.0f);
		}

		if (m_time > 20 && m_time <= 140)
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

		if (m_time > 140 && m_time <= 160)
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

		if (m_time > 160 && m_time <= 280)
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

		if (m_time > 280 && m_time <= 300)
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

		if (m_time > 300 && m_time <= 420)
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

			Draw::Draw(0, &src, &dst, f, 0.0f);
		}

		if (m_time > 440 && m_time <= 560)
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

		if (m_time > 560 && m_time <= 580)
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

		if (m_time > 580 && m_time <= 600)
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

		if (m_time > 600 && m_time <= 620)
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

		if (m_time > 620 && m_time <= 640)
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

		if (m_time > 640 && m_time <= 660)
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

		if (m_time > 660 && m_time <= 680)
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

		if (m_time > 680 && m_time <= 700)
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

		if (m_time > 700 && m_time <= 720)
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

		if (m_time > 720 && m_time <= 740)
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

		if (m_time > 740 && m_time <= 760)
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
	}

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//文字の表示
	Font::StrDraw(L"(ENTER_KEY)でスキップ", 560, 560, 20, c);


}