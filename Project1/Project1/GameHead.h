#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_TITLE,
	OBJ_CLICK_TITLE,
	OBJ_PRO,
	OBJ_EPI,
	OBJ_HERO,
	OBJ_ENEMY,
	OBJ_ENEMY2,
	OBJ_ENEMY3,
	OBJ_ENEMY4,
	OBJ_ENEMY5,
	OBJ_ENEMY6,
	OBJ_ENEMY7,
	OBJ_ENEMY8,
	OBJ_FASTENEMY,
	OBJ_SPWANENEMY,
	OBJ_MAIN,
	OBJ_GAMEOVER,
	OBJ_GAMECLEAR,
	OBJ_GAME_UI,
	OBJ_ITEM,
	OBJ_MENU,
	OBJ_JUNCTION,
	OBJ_ROOM,
	OBJ_GIMMICK,
	OBJ_GIMMICK2,
	OBJ_GIMMICK3,
	OBJ_GIMMICK4,
	OBJ_GIMMICK5,
	OBJ_GIMMICK6,
	OBJ_GIMMICK7,
	OBJ_GIMMICK8,
	OBJ_ROOM_GIMMICK,
	OBJ_HEAL,
	OBJ_BAR,
	OBJ_TEXT,

	//OBJ_CHAR,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_FASTENEMY,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
enum ITEM_ID
{
	ITEM_KEY,
	CHAR_HERO,
	CHAR_ENEMY,
	ITEM_HEAL,
	ITEM_BAR,
	CHAR_FASTENEMY,
	ITEM_NULL = 99,
};

enum MAP_ID
{
	MAP_NULL_0,
	MAP_KEY = 4,
	MAP_HEAL = 21,
	MAP_BAR = 26,
	FLOOR_0 = 1,
	FLOOR_1 = 4,
	FLOOR_2 = 5,
	FLOOR_3 = 7,
	FLOOR_4 = 13,
	FLOOR_5 = 21,
	FLOOR_6 = 25,
	FLOOR_7 = 26,
	FLOOR_8 = 8,
	FLOOR_10 = 31,
	FLOOR_11 = 36,
	FLOOR_12 = 37,
	FLOOR_13 = 38,
	FLOOR_14 = 39,
	DESK = 2,
	CHAIR = 3,
	BOOK_SHELF = 19,
	STAIRS = 3,
	WALL_UP = 9,
	WALL_RIGHT = 10,
	WALL_LEFT = 11,
	WALL_DOWN = 12,
	DOOR_UP=15,
	DOOR_DOWN=16,
	DOOR_LEFT = 17,
	DOOR_RIGHT = 18,
	WALL_ANGLE1 = 27,
	WALL_ANGLE2 = 28,
	WALL_ANGLE3 = 29,
	WALL_ANGLE4 = 30,
	WALL_ANGLE5 = 31,
	WALL_ANGLE6 = 32,
	WALL_ANGLE7 = 33,
	WALL_ANGLE8 = 34,
	WALL_ANGLE9 = 50,
	HOLE = 36,
	BOOK = 31,
	TEACHING_1 = 36,
	TEACHING_2 = 37,
	TEACHING_3 = 38,
	TEACHING_4 = 39,
	SPAWN_ENEMY_Y = 34,
	SPAWN_ENEMY_X = 35,
	FAST_ENEMY = 25,
	MAIN_ENEMY = 5,
	GIMMICK = 7,
	MAP_NULL=99,

};

enum STAGE_NUMBER
{
	FLOOR8,
	FLOOR7,
	FLOOR6,
	FLOOR5,
	FLOOR4,
	FLOOR3,
	FLOOR2,
	FLOOR1,
	GAME_CLEAR,
	FLOOR_NULL=8,
};

enum ROOM_NUMBER
{
	ROOM_0,
	ROOM_1,
	ROOM_2,
	ROOM_3,
	ROOM_4,
	ROOM_5,
	ROOM_6,
	ROOM_LIMIT,
};
//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjTitle.h"
#include "ObjHero.h"
#include "ObjClickTitle.h"
#include "ObjMain.h"
#include "ObjPRO.h"
#include "ObjEPI.h"

#include "ObjEnemy.h"
#include "ObjEnemy_2.h"
#include "ObjEnemy_3.h"


#include "ObjGameUI.h"
#include "ObjGameOver.h"
#include "ObjGameClear.h"
#include "ObjGameUI.h"
#include "ObjItem.h"
#include "ObjMenu.h"
#include "ObjText.h"


#include "ObjGimmick.h"
#include "ObjGimmick2.h"
#include "ObjGimmick3.h"


#include "objheal.h"
#include "ObjFastEnemy.h"
#include "ObjSpawnEnemy.h"
#include "Objbar.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "SceneGameUI.h"
#include "SceneMenu.h"
#include "ScenePRO.h"
#include "SceneEPI.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START  CSceneTitle
//-----------------------------------------------