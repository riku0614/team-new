#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：メイン
class CObjheal : public CObj
{
public:
	CObjheal(float x,float y);
	~CObjheal() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	//void SetFlag(bool b) { stop_flg = b; }

private:
	int m_map[MAP_X][MAP_Y];//マップ情報
	int ix;	//アイテムのX位置保管用
	int iy; //アイテムのY位置保管用
	float m_scroll_x;   //左右スクロール用
	float m_scroll_y;   //上下スクロール用

	int r_map[ROOM_X][ROOM_Y];
	float m_px;  //オブジェクトの位置X
	float m_py;  //オブジェクトの位置Y
	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY

		//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stop_flg;
	//bool hit_flg;
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_time;  //アニメーションフレーム動作間隔
	int m_ani_frame; //描画フレーム
};

