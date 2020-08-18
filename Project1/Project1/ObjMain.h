#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define GAME_CLEAR (3)
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (25)
#define ROOM_Y (25)
#define MAP_NUMBER (8)
#define BAR (26)
#define BLOCK_SIZE_X (64.0f)
#define BLOCK_SIZE_Y (64.0f)
#define ITEM_SIZE_X (32.0f)
#define ITEM_SIZE_Y (32.0f)
#define ROOM_NUMBER (7)
#define DRAW_SIZE (64.0f)
#define DRAW_FIX_SIZE (63.0f)
#define DRAW_DOOR_SIZE (50.0f)
#define CORRIDOR_SCROLL_RIGHT (80.0f)
#define CORRIDOR_SCROLL_LEFT (350.0f)
#define CORRIDOR_SCROLL_DOWN (300.0f)
#define CORRIDOR_SCROLL_UP (80.0f)
#define ROOM_SPAWN_X (20.0f)
#define ROOM_SPAWN_Y (4.0f)
#define ROOM_SPAWN_SCROLL_X (-15.0f)
#define ROOM_SPAWN_SCROLL_Y (-5.0f)



//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
	public:
		CObjMain(int map[ROOM_X][ROOM_Y]);
		~CObjMain() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[
		void SetScrollX(float s) { m_scroll_x = s; }//X�����̃X�N���[�����󂯓n���֐�
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y�����ւ̃X�N���[�����󂯓n���֐�
		float GetScrollY() { return m_scroll_y; }

		void SetDelete(bool b) { delete_flg = b; }//�A�C�e���̏����p

		bool RoomFlag() { return room_in; }//�������O����

		bool FirstFlag() { return first_stop; }

		//�t�H���g�\���t���O�؂�ւ��p
		bool GetStoryFlag() { return font_story_flg; }
		void SetStoryFlag(bool f) { font_story_flg = f; }
		void SetStoryFlag2(bool f) { font_story_flg2 = f; }
		void SetBarFlag(bool f) { font_bar_flg = f; }
		void SetHealFlag(bool f) { font_heal_flg = f; }
		void SetKeyFlag(bool f) { font_key_flg2 = f; }


		int RoomMapData() { return r_map[ROOM_X][ROOM_Y]; }//���݂̋����}�b�v�f�[�^

		int MapChangeData() { return map_chg; }//���݂̃X�e�[�W�f�[�^

		bool GetFlug() { return stop_flg; }//�}�b�v�؂�ւ���M�~�b�N��G�L�����A�A�C�e����z�u���鏈���p

		bool GetFlug2() { return stop_flg2; }//���̃M�~�b�N�p

		
		//�}�b�v��̃A�C�e���f�[�^���A�C�e���I�u�W�F�N�g�ɑ���p�̊֐�
		void SetMapItem(bool mi) { map_Item; }//��
		bool GetMapItem() { return map_Item; }
		void SetMapItem_2(bool mi) { map_Item_2; }//�񕜖�
		bool GetMapItem_2() { return map_Item_2; }
		void SetMapItem_3(bool mi) { map_Item_3; }//�o�[��
		bool GetMapItem_3() { return map_Item_3; }

		int m_map[MAP_X][MAP_Y];//�}�b�v���u���b�N���iX���V�T�AY=�V�T�j
		int r_map[ROOM_X][ROOM_Y];//�}�b�v���u���b�N���iX��25�AY=25�j


		//BlockHit�֐��̐錾
		void MapHit(
			float *x, float *y, bool scroll_on_x,bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt, int *c_id, int *k_id
		);

		//ItemHit�֐��̐錾
		void ItemHit(
			float *x, float *y, bool scroll_on_x, bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt
		);

		//��l���ƕǂ̌�������
		bool HeroBlockCrossPoint(
			float x, float y, float vx, float vy,
			float *out_px, float *out_py, float *out_len
		);
	private:
		
		float save_x[MAP_NUMBER][2];//�}�b�v���s��������p�̎�l���̈ʒu��o�^����z��
		float save_y[MAP_NUMBER][2];
		float save_scroll_x[MAP_NUMBER][2];//�}�b�v���s��������p�̃X�N���[������o�^����z��
		float save_scroll_y[MAP_NUMBER][2];

		int save_map[MAP_X][MAP_Y];//�����ɓ������ۂɌ��݂̘L���̃}�b�v����ۑ��������
		int save_room_map[ROOM_X][ROOM_Y][ROOM_NUMBER];//�����_���ɑI�΂ꂽ�}�b�v���𒆂ɓ���Ă�����萔���[�v�����炱�̕ϐ�����Ăяo��

		unsigned int rand_map;//�����_���Ƀ}�b�v���Ăԗp�̕ϐ�

		bool stop_flg;    //�}�b�v�؂�ւ���M�~�b�N��G�L�����A�A�C�e����z�u���鏈������x�����񂷗p�̃t���O
		bool stop_flg2;   //���̃M�~�b�N�؂�ւ��p
		bool first_stop;  //�L���}�b�v�f�[�^��ϐ��Ɉڂ���������x�����񂷗p�̃t���O
		bool room_in;     //�����}�b�v�ւ̐؂�ւ��̃t���O
		bool delete_flg;  //�A�C�e�������p�t���O
		bool pepepe;
		bool pepepe_2;
		bool room_chg_stop;//�����}�b�v�f�[�^��ϐ��֏����ʂ������̒�~�t���O
		

		float m_stamina_limid;//�X�^�~�i�̌��E�l

		//�e�L�X�g�\���p�֐�
		//���̎擾
		bool font_key_flg;
		bool font_key_flg2;
		//�e�L�X�g�u�b�N�p
		bool font_story_flg;
		bool font_story_flg2;
		//�o�[���擾
		bool font_bar_flg;
		//�񕜖�̎擾
		bool font_heal_flg;
		//�J�e�L�X�g�p
		bool font_open_flg;
		bool font_close_flg;
		bool font_open_flg2;
		//�����Ȃ��e�L�X�g�\���p
		bool font_nothing_flg;
		//�J���Ȃ��e�L�X�g�\���p
		bool keepout_font_flg;
		//�����Ă���A�C�e���I�u�W�F�N�g�̏�Ɏ擾�ł���L�[��\������p
		bool searchpoint_font_flg;

		int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
		int m_ani_frame; //�`��t���[��
		float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l


		bool open_flg;//����o�[���ŊJ���鏈���p�̃t���O
		bool nothing_flg;//�{�I�Ȃǂ���A�C�e����1�x��������ł��Ȃ������p�t���O
		bool switch_flg;

		int g_count1;
		int g_count2;
		unsigned int map_chg;     //�L���}�b�v�؂�ւ����Ǘ����邽�߂̕ϐ�
		unsigned int room_chg;    //���̋����}�b�v�p

		//�A�C�e���̓����蔻��ɓ��������Ƃ��ɂ��̏ꏊ�̗v�f�ԍ���ۑ�����ϐ�
		unsigned int ix;
		unsigned int iy;

		int size;        
		unsigned int m_time;      //�t�H���g��\������b��

		float spawn_pointX[MAP_NUMBER]; //map���̏����l���֐���������p�̕ϐ�
		float spawn_pointY[MAP_NUMBER];
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[MAP_NUMBER]; //���[�U�[�f�[�^�̃��C���}�b�v�f�[�^��ۑ����邽�߂̕ϐ�
		unique_ptr<wchar_t> r[MAP_NUMBER]; //���[�U�[�f�[�^�̋����}�b�v�f�[�^��ۑ����邽�߂̕ϐ�


		float m_scroll_x;   //���E�X�N���[���p
		float m_scroll_y;   //�㉺�X�N���[���p

		bool map_Item;//�}�b�v��̃A�C�e�����
		bool map_Item_2;//�}�b�v��̃A�C�e�����2!
		bool map_Item_3;//�}�b�v��̃A�C�e�����3!

		//����
		float Dot(float ax, float ay, float bx, float by);
		//�O��
		float Cross(float ax, float ay, float bx, float by);

		//���Ɛ��̌�������
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);

		
};