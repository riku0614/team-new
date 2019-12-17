//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "ObjMenu.h"
#include "SceneMenu.h"
#include "GameHead.h"

//コンストラクタ
CSceneMenu::CSceneMenu()
{

}

//デストラクタ
CSceneMenu::~CSceneMenu()
{

}

//ゲームメイン初期化メソッド
void CSceneMenu::InitScene()
{
	

	//メニューオブジェクト作成
	CObjMenu* objmenu = new CObjMenu();		//ゲームオーバーオブジェクト作成
	Objs::InsertObj(objmenu, OBJ_MENU, 10);	//ゲームオーバーオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneMenu::Scene()
{

}