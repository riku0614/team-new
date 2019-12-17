#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define Status (8)

//オブジェクト：主人公
class CObjHero : public CObj
{
public:
	CObjHero() {};
	~CObjHero() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー

	float GetX() { return m_px; }    //主人公の位置を渡す
	float GetY() { return m_py; }

	float GetVY() { return m_vy; }   //主人公のベクトルを渡す
	float GetVX() { return m_vx; }

	int GetLife() { return m_hero_life; }

	int GetBT() { return m_block_type; }//当たっているブロックの種類を渡す



	void SetUp(bool b) { m_hit_up = b; }      //上下左右のブロックの当たり判定のフラグ 
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

	void SetBT(int t) { m_block_type = t; }   //当たっているブロックの種類を設定する

	void SetX(float x) { m_px = x; }       //主人公の位置を設定
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }    //主人公のベクトルを設定
	void SetVX(float vx) { m_vx = vx; }

	void SetHeroStop(bool f) { m_hero_stop = f; }

	bool Getflag() { return peperon_flag;}
	void SetFlug(bool f) { peperon_flag = f; }
	bool Getflag_2() { return peperon_flag_2; }
	void SetFlug_2(bool f) { peperon_flag_2 = f; }
	bool Getflag_3() { return peperon_flag_3; }
	void SetFlug_3(bool f) { peperon_flag_3 = f; }

	bool SetItemflag() { return use_Item_flag; }
	bool SetItemflag_2() { return use_Item_flag_2; }
	bool SetItemflag_3() { return use_Item_flag_3; }

	bool action_flag() { return Conflict_flag; }
	bool action_flag2() { return Conflict_flag2; }

	int GetKeyID() { return m_id; }
	int GatHealID() { return h_id; }
	bool GetEnemyFlag() { return enemy_flg; }
	int GetBarID() { return b_id; }

	void SetHitFlagX(bool h) { hit_flag_x = h; }
	void SetHitFlagY(bool h) { hit_flag_y = h; }
private:
	float save[Status][2];

	int k_id;//アイテム（鍵）のID
	int h_id;//回復アイテムのID
	int b_id;//バールのID
	int m_id;//キャラクターID
	float m_px; //位置
	float m_py;
	float m_vx; //移動ベクトル
	float m_vy;
	float m_posture; //姿勢
	float m_stamina_limid;//スタミナの限界値

	int m_hero_life;//主人公の体力
	int m_ani_time;  //アニメーションフレーム動作間隔
	int m_ani_frame; //描画フレーム

	bool m_hero_stop;

	float m_speed_power;        //スピードパワー
	float m_ani_max_time;   //アニメーション動作間隔最大値

	int m_ani_move;//キャラクターの動き
	
    //blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//アイテムとの衝突確認用
	bool mi_hit_up;
	bool mi_hit_down;
	bool mi_hit_left;
	bool mi_hit_right;

	int m_time;//無敵時間
	bool m_flg;//無敵フラグ

	//踏んでいるブロックの種類確認用
	int m_block_type;

	bool peperon_flag; //アイテム1番消去フラグ用
	bool peperon_flag_2; //アイテム2番消去フラグ用
	bool peperon_flag_3; //アイテム3番消去フラグ用

	bool use_Item_flag; //アイテム1番使用フラグ
	bool use_Item_flag_2;//アイテム2番使用フラグ
	bool use_Item_flag_3;//アイテム3番使用フラグ

	bool Conflict_flag; //敵と当たったかを判断するフラグ
	bool Conflict_flag2; 

	float px, py;//交点

	bool stey_flg1;
	bool stey_flg2;
	bool stey_flg3;

	bool enemy_flg;

	bool hit_flag_x;

	bool hit_flag_y;
};