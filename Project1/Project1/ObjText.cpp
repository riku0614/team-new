//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjText.h"
#include "SceneMain.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjText::Init()
{
	
}
//アクション
void CObjText::Action()
{
	//Enterを押したときの処理
	if (Input::GetVKey(VK_RETURN)==true)
	{
		
	}
}

//ドロー
void CObjText::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置設定
	dst.m_top = 64.0f;
	dst.m_right = 64.0f;
	dst.m_left =  64.0f;
	dst.m_bottom =  64.0f;

	//描画設定
	Draw::Draw(0, &src, &dst, c, 0.0f);



	Font::StrDraw(L"もしこれを見ているのなら、早くこの学校から逃げろ", 64, 64, 64, c);
}