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
#include "ObjTelop.h"
#include "SceneTelop.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTelop::CSceneTelop()
{

}

//�f�X�g���N�^
CSceneTelop::~CSceneTelop()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTelop::InitScene()
{
	//���y���̓ǂݍ���
	//Audio::LoadAudio(8, L"8EDBGM.wav", SOUND_TYPE::EFFECT);

	//���y�X�^�[�g
	//Audio::Start(8);

	Draw::LoadImage(L"Telop.png", 0, TEX_SIZE_1024);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTelop* objt = new CObjTelop();		//�Q�[���N���A�I�u�W�F�N�g�쐬
	Objs::InsertObj(objt, OBJ_TELOP, 10);	//�Q�[���N���A�I�u�W�F�N�g�o�^

}

//�Q�[�����C�����s�����\�b�h
void CSceneTelop::Scene()
{

}