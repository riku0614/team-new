//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "ObjEPI.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneEPI::CSceneEPI()
{

}

//�f�X�g���N�^
CSceneEPI::~CSceneEPI()
{

}

//�Q�[�����C�����������\�b�h
void CSceneEPI::InitScene()
{

	//�o�͂����镶���̃O���t�B�b�N�쐬
	Font::SetStrTex(L"(ENTER_KEY)�ŃX�L�b�v");
	//Font::SetStrTex(L"�`�J�C�G�`");
	//Font::SetStrTex(L"�ŏ�����");

	//���y���̓ǂݍ���
	Audio::LoadAudio(0, L"�G�s���[�O���y.wav", SOUND_TYPE::BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(0);

	//�N���b�N�^�C�g���I�u�W�F�N�g�쐬
	CObjEPI* objep = new CObjEPI();				//�v�����[�O�I�u�W�F�N�g�쐬
	Objs::InsertObj(objep, OBJ_EPI, 10);		//�v�����[�O�I�u�W�F�N�g�o�^

	//�v�����[�O�摜
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

//�Q�[�����C�����s�����\�b�h
void CSceneEPI::Scene()
{

}