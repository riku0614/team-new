#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

#define Status (1)

//オブジェクト：メイン
class CObjGameUI : public CObj
{
public:
	CObjGameUI() {};
	~CObjGameUI() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	bool GetItemflag() { return item_flag; }
	bool GetItemflag_2() { return item_flag_2; }
	bool GetItemflag_3() { return item_flag_3; }

	bool takeItemflag() { return take_flag; }
	bool takeItemflag_2() { return take_flag_2; }
	bool takeItemflag_3() { return take_flag_3; }

	void Settakeflag(bool i) { take_flag = i; }		//主人公に渡す、アイテムを持っているかどうかのフラグ（1番用）、中身いじります
	void Settakeflag_2(bool i) { take_flag_2 = i; } //2番用
	void Settakeflag_3(bool i) { take_flag_3 = i; } //3番用
	void SetID(int id) { b_id = id; }
	
private:

	bool item_flag;		//主人公にてアイテム1番を使用するためのトリガーフラグ
	bool item_flag_2;	//2番
	bool item_flag_3;	//3番

	bool take_flag;		//主人公がアイテム（1番）を持っているかを判断するためのフラグ
	bool take_flag_2;	//2番
	bool take_flag_3;	//3番


	int m_id;	//key用変数
	int h_id;	//Heal用変数
	int b_id;	//bar用変数
	float damage_effect_feed1;//ダメージエフェクトフェードアウト用変数１
	float damage_effect_feed2;//ダメージエフェクトフェードアウト用変数２
};