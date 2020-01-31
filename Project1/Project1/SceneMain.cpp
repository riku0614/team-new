#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjMain.h"
#include "ObjItem.h"


//使用するネームスペース
using namespace GameL;


//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//時間
	m_time=0;

	
	//音楽情報の読み込み
	Audio::LoadAudio(1, L"1廊下BGM.wav", SOUND_TYPE::BACK_MUSIC);

	//音楽スタート
	Audio::Start(1);

	unique_ptr<wchar_t> p;
	int size;
	
	p = Save::ExternalDataOpen(L"教室1サクラ.csv", &size);

	int map[ROOM_X][ROOM_Y];
	int count = 1;

	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

			
		
			
		}
	}


	Draw::LoadImage(L"床.png", 1, TEX_SIZE_512);
	Draw::LoadImage(L"スタミナゲージ.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"壁.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"窓.png", 4, TEX_SIZE_512);
	Draw::LoadImage(L"敵(仮2).png", 5, TEX_SIZE_512);
	Draw::LoadImage(L"アイテム欄(仮).png", 6, TEX_SIZE_512);
	Draw::LoadImage(L"kaidan2.png", 7, TEX_SIZE_512);
	Draw::LoadImage(L"アイテム(仮).png", 8, TEX_SIZE_512);
	Draw::LoadImage(L"鍵.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"扉.png", 10, TEX_SIZE_512);

	Draw::LoadImage(L"主人公まとめ.png", 11, TEX_SIZE_512);

	Draw::LoadImage(L"手形1.png", 15, TEX_SIZE_512);
	Draw::LoadImage(L"呪い.png", 16, TEX_SIZE_512);
	Draw::LoadImage(L"画面.png", 17, TEX_SIZE_1024);
	Draw::LoadImage(L"壁（横）.png", 18, TEX_SIZE_512);
	Draw::LoadImage(L"壁（横）２.png", 19, TEX_SIZE_512);
	Draw::LoadImage(L"壁２.png", 20, TEX_SIZE_512);                     //20
	Draw::LoadImage(L"薬.png", 21, TEX_SIZE_512);
	Draw::LoadImage(L"ダメージエフェクト1.png", 22, TEX_SIZE_1024);
	Draw::LoadImage(L"ダメージエフェクト2.png", 23, TEX_SIZE_1024);
	Draw::LoadImage(L"床穴.png", 24, TEX_SIZE_512);
	Draw::LoadImage(L"扉1.png", 25, TEX_SIZE_512);
	Draw::LoadImage(L"扉（下）1.png", 26, TEX_SIZE_512);
	Draw::LoadImage(L"扉（右）1.png", 27, TEX_SIZE_512);
	Draw::LoadImage(L"扉（左）1.png", 28, TEX_SIZE_512);
	Draw::LoadImage(L"本棚.png", 29, TEX_SIZE_512);
	Draw::LoadImage(L"机まとめ.png", 30, TEX_SIZE_1024);                             //30
	Draw::LoadImage(L"椅子まとめ.png", 31, TEX_SIZE_1024);
	Draw::LoadImage(L"敵黄色(仮).png", 32, TEX_SIZE_512);
	Draw::LoadImage(L"ドット絵　本.png", 33, TEX_SIZE_512);
	Draw::LoadImage(L"壁左上.png", 34, TEX_SIZE_512);
	Draw::LoadImage(L"壁右上.png", 35, TEX_SIZE_512);
	Draw::LoadImage(L"壁右下.png", 36, TEX_SIZE_512);
	Draw::LoadImage(L"壁左下.png", 37, TEX_SIZE_512);
	Draw::LoadImage(L"敵赤色(仮).png", 38, TEX_SIZE_512);
	Draw::LoadImage(L"床青.png", 39, TEX_SIZE_512);
	Draw::LoadImage(L"壁角２右下.png", 38, TEX_SIZE_512);
	Draw::LoadImage(L"壁角２左下.png", 39, TEX_SIZE_512);
	Draw::LoadImage(L"壁角２左上.png", 40, TEX_SIZE_512);                       //40
	Draw::LoadImage(L"壁角２右上.png", 41, TEX_SIZE_512);
	Draw::LoadImage(L"敵赤色(仮).png", 42, TEX_SIZE_512);
	Draw::LoadImage(L"床青.png", 43, TEX_SIZE_512);
	Draw::LoadImage(L"バールのようなもの.png", 44, TEX_SIZE_1024);
	Draw::LoadImage(L"教卓.png", 45, TEX_SIZE_512);
	Draw::LoadImage(L"black.png", 46, TEX_SIZE_1024);
	Draw::LoadImage(L"ダメージエフェクト1.png", 47, TEX_SIZE_1024);
	Draw::LoadImage(L"ダメージエフェクト2.png", 48, TEX_SIZE_1024);
	Draw::LoadImage(L"敵結合.png", 49, TEX_SIZE_1024);
	Draw::LoadImage(L"教卓右下.png", 50, TEX_SIZE_1024);
	Draw::LoadImage(L"教卓右上.png", 51, TEX_SIZE_1024);
	Draw::LoadImage(L"教卓左上.png", 52, TEX_SIZE_1024);
	Draw::LoadImage(L"教卓左下.png", 53, TEX_SIZE_1024);

	Draw::LoadImage(L"バールアイテムエフェクトまとめ.png", 54, TEX_SIZE_1024);
	Draw::LoadImage(L"回復アイテムエフェクトまとめ.png", 55, TEX_SIZE_1024);
	Draw::LoadImage(L"鍵アイテムエフェクトまとめ.png", 56, TEX_SIZE_1024);

	//出力させる文字のグラフィック作成
	Font::SetStrTex(L"鍵を入手した...");

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//UIオブジェクト作成
	CObjGameUI* objui = new CObjGameUI();
	Objs::InsertObj(objui, OBJ_GAME_UI, 12);
	
	
	//ブロックオブジェクト作成
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 8);

	////アイテムオブジェクト作成
	//CObjItem* obji = new CObjItem(map);
	//Objs::InsertObj(obji, OBJ_ITEM, 13);

	
	
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}