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
#include "ObjEPI.h"
#include "GameHead.h"

//コンストラクタ
CSceneEPI::CSceneEPI()
{

}

//デストラクタ
CSceneEPI::~CSceneEPI()
{

}

//ゲームメイン初期化メソッド
void CSceneEPI::InitScene()
{

	//出力させる文字のグラフィック作成
	Font::SetStrTex(L"(ENTER_KEY)でスキップ");
	//Font::SetStrTex(L"～カイエ～");
	//Font::SetStrTex(L"最初から");

	//音楽情報の読み込み
	Audio::LoadAudio(0, L"エピローグ音楽.wav", SOUND_TYPE::BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);

	//クリックタイトルオブジェクト作成
	CObjEPI* objep = new CObjEPI();				//プロローグオブジェクト作成
	Objs::InsertObj(objep, OBJ_EPI, 10);		//プロローグオブジェクト登録

	//プロローグ画像
	Draw::LoadImageW(L"EP/EP_BLACK.png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi1.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi2.png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi3.png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi4.png", 4, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi5.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi6.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi7.png", 7, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi8.png", 8, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi9.png", 9, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi10.png", 10, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi11.png", 11, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi12.png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"EP/epi13.png", 13, TEX_SIZE_1024);
}

//ゲームメイン実行中メソッド
void CSceneEPI::Scene()
{

}