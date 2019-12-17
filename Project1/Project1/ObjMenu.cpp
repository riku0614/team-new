//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjMenu.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	m_enter_flag = false;
}

//アクション
void CObjMenu::Action()
{
	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_enter_flag == false)
		{
			Scene::SetScene(new CSceneTitle);
		}
		m_enter_flag = true;
	}

	else
	{
		m_enter_flag = false;
	}

	if (Input::GetVKey('E') == true)
	{
		Scene::SetScene(new CSceneMain);
	}



}

//ドロー
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"spaceキーでタイトルへ戻る", 200, 250, 32, c);
}