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
}

//アクション
void CObjPRO::Action()
{
	if (PR < 2 && Input::GetVKey('P') == true)
	{
		PR++;
	}
	else if (PR >= 2 && Input::GetVKey('P') == true)
	{
		Scene::SetScene(new CSceneMain);
	}
}

//ドロー
//Font::StrDraw(L"出力したい文字列", x位置, y位置, 文字の大きさ, color配列);
void CObjPRO::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//文字の表示
	Font::StrDraw(L"怪穢", 320, 200, 60, c);
	Font::StrDraw(L"～カイエ～", 317, 270, 25, c);

}