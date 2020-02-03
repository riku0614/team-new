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
	Font::SetStrTex(L"(ENTER_KEY)でスキップ");
	//Font::SetStrTex(L"～カイエ～");
	//Font::SetStrTex(L"最初から");

	//音楽情報の読み込み
	Audio::LoadAudio(0, L"プロローグ音楽.wav", SOUND_TYPE::BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);

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
	Draw::LoadImageW(L"PR/プロローグ25(フェード入り).png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ27(フェード入り).png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ29(フェード入り).png", 14, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ31(フェード入り).png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ33(フェード入り).png", 16, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ35(フェード入り).png", 17, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ37(フェード入り).png", 18, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ39(フェード入り).png", 19, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ41(フェード入り).png", 20, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ43(フェード入り).png", 21, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ45(フェード入り).png", 22, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ47(フェード入り).png", 23, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/プロローグ49(フェード入り).png", 24, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/PR_BLACK.png", 25, TEX_SIZE_1024);
}

//ゲームメイン実行中メソッド
void CScenePRO::Scene()
{

}