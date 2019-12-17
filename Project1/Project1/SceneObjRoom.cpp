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
#include "ObjGameClear.h"
#include "SceneGameClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameClear::CSceneGameClear()
{

}

//デストラクタ
CSceneGameClear::~CSceneGameClear()
{

}

//ゲームメイン初期化メソッド
void CSceneGameClear::InitScene()
{
	//オブジェクトを登録
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	//タイトルオブジェクト作成
	CObjGameClear* objc = new CObjGameClear();		//ゲームクリアオブジェクト作成
	Objs::InsertObj(objc, OBJ_GAMECLEAR, 10);	//ゲームクリアオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneGameClear::Scene()
{

}