//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameClear::Init()
{
	m_time = 0;
}

//アクション
void CObjGameClear::Action()
{
	m_time++;	//時間によって画像を表示するための変数
}

//ドロー
void CObjGameClear::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//文字の表示
	//Font::StrDraw(L"～ゲームクリア～",240, 240, 40, c);

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

	//描画設定
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//ED1表示
	if (m_time > 60 && m_time < 300)
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

	//ED2表示
	if (m_time > 360 && m_time < 600)
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

	//ED3表示
	if (m_time > 660 && m_time < 900)
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

	//ED画像を表示した後、タイトル画面へ移行
	if (m_time > 930)
	{
		Scene::SetScene(new CSceneTitle);
	}

}