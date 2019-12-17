//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameOver.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameOver::Init()
{
	GO_time = 0;
	Title_flag = false;
}

//アクション
void CObjGameOver::Action()
{
	GO_time++;//タイムの経過によってタイトルに移行するため、後置インクリメントで値を増やしていく

	//タイムの経過とは別に、'Z'キーを押した場合にタイトルに移行するようにする
	if (Input::GetVKey('Z') == true)
	{
		Title_flag = true;	//タイトルに移行するためのフラグをオンに
	}

	if (Title_flag == true)
	{
		Scene::SetScene(new CSceneTitle);
	}
	else if (GO_time > 300)
	{
		Scene::SetScene(new CSceneTitle);
	}
}

//ドロー
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;
	RECT_F dst;

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	//表示位置設定
	dst.m_top = 0.0f;
	dst.m_right = 800.0f;
	dst.m_left = 0.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

}