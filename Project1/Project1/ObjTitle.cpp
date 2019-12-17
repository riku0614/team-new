//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"
#include "SceneMain.h"
#include "GameL/Audio.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{

	//Mouseの位置取得用変数初期化
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	//Mouseのクリック確認初期化
	m_mou_r = false;
	m_mou_l = false;
}

//アクション
void CObjTitle::Action()
{
	//マウスの位置を取得
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();

	//マウスのボタンの状態
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//マウスの位置とクリックする場所で当たり判定
	if (m_mou_x > 230 && m_mou_x < 450 && m_mou_y>400 && m_mou_y < 430)
	{
		//マウスが押されたらメインに移行
		if (m_mou_r == true || m_mou_l == true)
		{
			Scene::SetScene(new CSceneMain);
		}
	}
}

//ドロー
//Font::StrDraw(L"出力したい文字列", x位置, y位置, 文字の大きさ, color配列);
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//仮マウス位置表示
	wchar_t str[256];
	swprintf_s(str, L"X=%f,Y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 20, c);

	//文字の表示
	Font::StrDraw(L"怪穢", 320, 200, 60, c);
	Font::StrDraw(L"～カイエ～", 317, 270, 25, c);

	
}