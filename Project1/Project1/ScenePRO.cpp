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
#include "SceneMain.h"
#include "ObjPRO.h"
#include "GameHead.h"

//コンストラクタ
CScenePRO::CScenePRO()
{

}

//デストラクタ
CScenePRO::~CScenePRO()
{

}

//ゲームメイン初期化メソッド
void CScenePRO::InitScene()
{

	//出力させる文字のグラフィック作成
	//Font::SetStrTex(L"怪穢");
	//Font::SetStrTex(L"～カイエ～");
	//Font::SetStrTex(L"最初から");

	//クリックタイトルオブジェクト作成
	CObjPRO* objpr = new CObjPRO();				//プロローグオブジェクト作成
	Objs::InsertObj(objpr, OBJ_PRO, 10);		//プロローグオブジェクト登録

	//プロローグ画像
	Draw::LoadImageW(L"PR/プロローグ1(フェード入り).png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ3(フェード入り).png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ5(フェード入り).png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ7(フェード入り).png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ9(フェード入り).png", 4, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ11(フェード入り).png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ13(フェード入り).png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ15(フェード入り).png", 7, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ17(フェード入り).png", 8, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ19(フェード入り).png", 9, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ21(フェード入り).png", 10, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ23(フェード入り).png", 11, TEX_SIZE_1024);
}

//ゲームメイン実行中メソッド
void CScenePRO::Scene()
{

}