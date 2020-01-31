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
	m_time = 0;
}

//�A�N�V����
void CObjPRO::Action()
{
	if (m_time < 601)
	{
		m_time++;
	}

	if (Input::GetVKey('P') == true)
	{
		m_time = 600;
	}

	if (m_time == 600)
	{
		Scene::SetScene(new CSceneMain);
	}

	/*if (PR < 2 && Input::GetVKey('P') == true)
	{
		PR++;
	}
	else if (PR >= 2 && Input::GetVKey('P') == true)
	{
		Scene::SetScene(new CSceneMain);
	}*/
}

//�h���[
//Font::StrDraw(L"�o�͂�����������", x�ʒu, y�ʒu, �����̑傫��, color�z��);
void CObjPRO::Draw()
{
	//�����̕\��
	//Font::StrDraw(L"���q", 320, 200, 60, c);
	//Font::StrDraw(L"�`�J�C�G�`", 317, 270, 25, c);
	//�v�����[�O�\��
	for (int i = 0; i < 50; i++)
	{
		if (m_time <= 20)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(0, &src, &dst, f, 0.0f);
		}

		if (m_time > 20 && m_time <= 40)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(1, &src, &dst, f, 0.0f);
		}
		if (m_time > 40 && m_time <= 60)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(2, &src, &dst, f, 0.0f);
		}

		if (m_time > 60 && m_time <= 80)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(3, &src, &dst, f, 0.0f);
		}

		if (m_time > 80 && m_time <= 100)
		{
			float f[4] = { 1.0f,1.0f,1.0f,1.0f };

			RECT_F src;
			RECT_F dst;

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 640.0f;
			src.m_bottom = 480.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_right = 800.0f;
			dst.m_left = 0.0f;
			dst.m_bottom = 600.0f;

			Draw::Draw(4, &src, &dst, f, 0.0f);
		}

	}
	

}