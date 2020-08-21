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
#include "ObjTelop.h"
#include "SceneTelop.h"
#include "GameHead.h"

//コンストラクタ
CSceneTelop::CSceneTelop()
{

}

//デストラクタ
CSceneTelop::~CSceneTelop()
{

}

//ゲームメイン初期化メソッド
void CSceneTelop::InitScene()
{
	//音楽情報の読み込み
	//Audio::LoadAudio(8, L"8EDBGM.wav", SOUND_TYPE::EFFECT);

	//音楽スタート
	//Audio::Start(8);

	Draw::LoadImage(L"Telop.png", 0, TEX_SIZE_1024);

	//タイトルオブジェクト作成
	CObjTelop* objt = new CObjTelop();		//ゲームクリアオブジェクト作成
	Objs::InsertObj(objt, OBJ_TELOP, 10);	//ゲームクリアオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneTelop::Scene()
{

}