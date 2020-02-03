#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjEPI : public CObj
{
public:
	CObjEPI() {};
	~CObjEPI() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:

	int m_time;	//テロップ出現用
	int PR;		//プロローグ用変数
};