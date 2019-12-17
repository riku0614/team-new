#pragma once
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <mmsystem.h>
namespace GameL
{
	//ウィンドウ作成
	typedef class LSetWindow
	{
		public:
			static void NewWindow(int w,int h,wchar_t* name,HINSTANCE hInstance);
			static void DeleteWindow();
			static HWND GethWnd()	{return m_hWnd;}
		private:
			static HWND m_hWnd;			//ウィンドウハンドル
			static int  m_width;
			static int  m_height;
	}Window;

};