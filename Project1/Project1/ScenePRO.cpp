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
	Font::SetStrTex(L"怪穢");
	Font::SetStrTex(L"～カイエ～");
	Font::SetStrTex(L"最初から");

	//クリックタイトルオブジェクト作成
	CObjPRO* objpr = new CObjPRO();				//プロローグオブジェクト作成
	Objs::InsertObj(objpr, OBJ_PRO, 10);		//プロローグオブジェクト登録


}

//ゲームメイン実行中メソッド
void CScenePRO::Scene()
{

}