#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjTelop : public CObj
{
public:
	CObjTelop() {};
	~CObjTelop() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:

	int m_time;	//テロップ出現用
};