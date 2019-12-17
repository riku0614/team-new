#pragma once
//使用するヘッダー
#include "GameL/SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMenu : public CScene
{
   public:
	   CSceneMenu();
	   ~CSceneMenu();
	   void InitScene();//ゲームメイン初期化メソッド
	   void Scene();//ゲームメイン実行中メソッド
   private:

};