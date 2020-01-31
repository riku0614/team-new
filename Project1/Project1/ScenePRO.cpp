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
#include "ObjPRO.h"
#include "GameHead.h"

//�R���X�g���N�^
CScenePRO::CScenePRO()
{

}

//�f�X�g���N�^
CScenePRO::~CScenePRO()
{

}

//�Q�[�����C�����������\�b�h
void CScenePRO::InitScene()
{

	//�o�͂����镶���̃O���t�B�b�N�쐬
	//Font::SetStrTex(L"���q");
	//Font::SetStrTex(L"�`�J�C�G�`");
	//Font::SetStrTex(L"�ŏ�����");

	//�N���b�N�^�C�g���I�u�W�F�N�g�쐬
	CObjPRO* objpr = new CObjPRO();				//�v�����[�O�I�u�W�F�N�g�쐬
	Objs::InsertObj(objpr, OBJ_PRO, 10);		//�v�����[�O�I�u�W�F�N�g�o�^

	//�v�����[�O�摜
	Draw::LoadImageW(L"PR/�v�����[�O1(�t�F�[�h����).png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O3(�t�F�[�h����).png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O5(�t�F�[�h����).png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O7(�t�F�[�h����).png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O9(�t�F�[�h����).png", 4, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O11(�t�F�[�h����).png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O13(�t�F�[�h����).png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O15(�t�F�[�h����).png", 7, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O17(�t�F�[�h����).png", 8, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O19(�t�F�[�h����).png", 9, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O21(�t�F�[�h����).png", 10, TEX_SIZE_1024);
	Draw::LoadImageW(L"PR/�v�����[�O23(�t�F�[�h����).png", 11, TEX_SIZE_1024);
}

//�Q�[�����C�����s�����\�b�h
void CScenePRO::Scene()
{

}