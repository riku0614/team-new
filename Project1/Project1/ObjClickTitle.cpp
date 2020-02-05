//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjClickTitle.h"
#include "SceneMain.h"
#include "GameL/Audio.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClickTitle::Init()
{
	m_yj = 0.0f;
	m_f = true;
	save_data = 0;
	stage_data = 0;
}
//�A�N�V����
void CObjClickTitle::Action()
{

	if (Input::GetVKey('M'))
	{
		;
	}
	//Enter���������Ƃ��̏���
	if (m_yj == 0.0f && Input::GetVKey(VK_RETURN))
	{
		Scene::SetScene(new CScenePRO);//�v�����[�O��
	}
		//���y���̓ǂݍ���
		Audio::LoadAudio(9, L"9�^�C�g�����艹.wav", SOUND_TYPE::EFFECT);

	//�Q�[�����I�����鏈��
	if (m_yj == CLICK_TITLE_3 && Input::GetVKey(VK_RETURN))
	{
		Scene::SetScene(NULL);//�^�C�g����
		////���y�X�^�[�g
		//Audio::Start(9);

		//Scene::SetScene(new CSceneMain);
	}
	
	//'W'key�����������̖�󏈗�
	if (Input::GetVKey('W') == true)
	{ 
		//m_f��true�̏ꍇ...
		if (m_f == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(2, L"2�J�[�\��SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(2);

			//m_yj��0.0f(�����ʒu)�������ꍇ�̏���
			if (m_yj <= 0.0f)
			{
			m_yj = m_yj + CLICK_TITLE_CURSOR3;
			}
			//m_yj��0�ȏ�̏ꍇ
			if (m_yj > 0.0f)
			{
			m_yj -= CLICK_TITLE_CHOICE;//3�I���ł���悤�̂��邽�߁A+�̒l�̎O���̈�̐���������i-y�j�ɓ�����
			}

			m_f = false;//m_f��false�Ɂ�'W'�����������Ă��J�[�\���������Ȃ��悤�ɂ���
		}
	}

	//'S'key�����������̖�󏈗�
	else if (Input::GetVKey('S') == true)
	{
		//m_f��true�̏ꍇ...
		if (m_f == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(2, L"2�J�[�\��SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(2);

			//m_yj��100.0f(�ő�l�̈ʒu)�������ꍇ�̏���
			if (m_yj >= CLICK_TITLE_MAX)
			{
				m_yj = m_yj - CLICK_TITLE_CURSOR1;
			}
			//m_yj��100�ȉ��̏ꍇ
			if (m_yj <= CLICK_TITLE_UNDER100)
			{
				m_yj += CLICK_TITLE_CHOICE;//3�I���ł���悤�̂��邽�߁A-�̒l�̎O���̈�̐���������i+y�j�ɓ�����
			}

			m_f = false;//m_f��false�Ɂ�'W','S'�����������Ă��J�[�\���������Ȃ��悤�ɂ���
		}
	}
	//'W','S'����x����������
	else
	{
		m_f = true;//m_f��true��
	}
}

//�h���[
void CObjClickTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 607.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_right = 799.0f;
	dst.m_left = 0.0f;
	dst.m_bottom = dst.m_top + 599.0f;

	//�`��ݒ�
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = DRAW_SIZE;
	src.m_bottom = DRAW_SIZE;

	//�\���ʒu�ݒ�
	dst.m_top = 335.0f + m_yj;
	dst.m_right = 450.0f;
	dst.m_left = dst.m_right + DRAW_SIZE;
	dst.m_bottom = dst.m_top + DRAW_SIZE;

	//�`��ݒ�
	Draw::Draw(0, &src, &dst, c, 0.0f);



	//�N���b�N����ꏊ
	//�Q�[�����n�߂�ꏊ

	float cc[4] = { 1.0f,0.5f,0.5f,0.7f };
	Font::StrDraw(L"�ŏ��J��", 320, 350, 30, cc);
	Font::StrDraw(L"���L�J��", 320, 400, 30, cc);
	Font::StrDraw(L"�Q�[���I��", 300, 450, 30, cc);

}
