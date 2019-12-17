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
	//音楽情報の読み込み
	Audio::LoadAudio(8, L"8EDBGM.wav", SOUND_TYPE::EFFECT);

	//音楽スタート
	Audio::Start(8);

	//オブジェクトを登録
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	Draw::LoadImageW(L"ED画面 背景用.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED画面1.png", 1, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED画面2.png", 2, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED画面3.png", 3, TEX_SIZE_1024);

	//タイトルオブジェクト作成
	CObjGameClear* objc = new CObjGameClear();		//ゲームクリアオブジェクト作成
	Objs::InsertObj(objc, OBJ_GAMECLEAR, 10);	//ゲームクリアオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneGameClear::Scene()
{
	
}