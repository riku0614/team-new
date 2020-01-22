#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define WINDOW_MAX_X (800.0f)
#define WINDOW_MIN_X (-32.0f)
#define WINDOW_MAX_Y (600.0f)
#define WINDOW_MIN_Y (-32.0f)

#define MAP_MIN   (0)
#define MAP_ERROR (-1)
#define MAP_DRAW_SIZE (64.0f)

#define BUFFER_MAX         (8)
#define BUFFER_DELETE_DATA (999)
#define BUFFER_NO_DATA     (-1)

#define SEARCH_MAX         (4)
#define SEARCH_MAP_NEXT    (1)

#define KM_MAP_MAX         (9)
#define CONNECTION_DELETE  (1)

#define LINE_LOOP          (1)
#define LINE_STEP_UP       (1)
#define LINE_STEP_X_PLUS   (0)
#define LINE_STEP_Y_PULS   (0)

//オブジェクト：主人公
class CObjEnemy3 : public CObj
{
public:
	CObjEnemy3(float x, float y);
	~CObjEnemy3() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー

	float GetX() { return m_ex; }
	float GetY() { return m_ey; }

	void SetX(float x) { m_ex = x; }
	void SetY(float y) { m_ey = y; }

	float scrollY() { return escrolly; }
	float scrollX() { return escrollx; }

private:
	float m_ex;  //オブジェクトの位置X
	float m_ey;  //オブジェクトの位置Y
	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY
	float m_posture; //姿勢

	int m_map[MAP_X][MAP_Y];
	int m_flg;//追従移動の管理用フラグ

	int m_time;
	int zx;
	int zy;

	float escrolly;
	float escrollx;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	int m_id;
	int k_id;

	int m_ani_frame;
	int m_ani_time;
	int m_ani_max_time;
	float damage_time;//ダメージブースト用時間変数
	bool boost_flag;//ダメージブーストを一回しか発動させないためのフラグ

	float px, py;//交点
};
