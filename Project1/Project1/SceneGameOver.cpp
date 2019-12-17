//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "ObjGameOver.h"
#include "SceneGameOver.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//ゲームメイン初期化メソッド
void CSceneGameOver::InitScene()
{
	//オブジェクトを登録
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	Draw::LoadImageW(L"無題.png", 0, TEX_SIZE_512);

	//タイトルオブジェクト作成
	CObjGameOver* objg = new CObjGameOver();		//ゲームオーバーオブジェクト作成
	Objs::InsertObj(objg, OBJ_GAMEOVER, 10);	//ゲームオーバーオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneGameOver::Scene()
{

}