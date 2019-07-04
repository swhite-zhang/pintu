#pragma once

#include"framework.h"
#include"pintu.h"

#define MAX_LOADSTRING 100

class Pwindow
{
public:
	HINSTANCE hInst;                                // 当前实例
	WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
	WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
	WNDCLASSEXW wcex;

	static ATOM MyRegisterClass(HINSTANCE hInstance,Pwindow win);
	static BOOL InitInstance(HINSTANCE, int,Pwindow win);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM,Pwindow win);
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM,Pwindow win);

	Pwindow();
	~Pwindow();
};

