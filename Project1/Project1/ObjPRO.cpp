//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjPRO.h"
#include "SceneMain.h"
#include "GameL/Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjPRO::Init()
{
	PR = 0;
}

//�A�N�V����
void CObjPRO::Action()
{
	if (PR < 2 && Input::GetVKey('P') == true)
	{
		PR++;
	}
	else if (PR >= 2 && Input::GetVKey('P') == true)
	{
		Scene::SetScene(new CSceneMain);
	}
}

//�h���[
//Font::StrDraw(L"�o�͂�����������", x�ʒu, y�ʒu, �����̑傫��, color�z��);
void CObjPRO::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�����̕\��
	Font::StrDraw(L"���q", 320, 200, 60, c);
	Font::StrDraw(L"�`�J�C�G�`", 317, 270, 25, c);

}