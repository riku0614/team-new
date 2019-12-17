#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：タイトル
class CObjTitle : public CObj
{
	public:
		CObjTitle() {};
		~CObjTitle() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー
	private:
		float m_mou_x;	//マウスの位置X
		float m_mou_y;	//マウスの位置Y
		bool m_mou_r;	//マウスクリック確認"R"
		bool m_mou_l;	//マウスクリック確認"L"
};