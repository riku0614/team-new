#pragma once
//使用するヘッダー
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneGameClear : public CScene
{
public:
	CSceneGameClear();
	~CSceneGameClear();
	void InitScene();//ゲームメイン初期化メソッド
	void Scene();//ゲームメイン実行中メソッド

	bool Ending1() { return ED; }
private:
	int m_time;	//テロップ出現用（試作）
	bool ED;	//ED1出現用
};