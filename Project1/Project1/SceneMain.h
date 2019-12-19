#pragma once
//使用するヘッダー
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMain : public CScene
{
	public:
		CSceneMain();
		~CSceneMain();
		void InitScene();//ゲームメイン初期化メソッド
		void Scene();//ゲームメイン実行中メソッド
	
	private:
		int m_time;
};