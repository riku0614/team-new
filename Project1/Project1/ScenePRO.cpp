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
	Font::SetStrTex(L"���q");
	Font::SetStrTex(L"�`�J�C�G�`");
	Font::SetStrTex(L"�ŏ�����");

	//�N���b�N�^�C�g���I�u�W�F�N�g�쐬
	CObjPRO* objpr = new CObjPRO();				//�v�����[�O�I�u�W�F�N�g�쐬
	Objs::InsertObj(objpr, OBJ_PRO, 10);		//�v�����[�O�I�u�W�F�N�g�o�^


}

//�Q�[�����C�����s�����\�b�h
void CScenePRO::Scene()
{

}