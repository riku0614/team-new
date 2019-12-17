#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjClickTitle : public CObj
{
public:
	CObjClickTitle() {};
	~CObjClickTitle() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_yj;	//矢印移動変数
	bool m_f;	//矢印制御用
};