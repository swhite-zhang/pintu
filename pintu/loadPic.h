#pragma once
#include "framework.h"
#include "pintu.h"

class loadPic
{	
private:
	LPCWSTR picPath;
	int width;
	int length;
	int PicX, PicY, DCX, DCY, cutWidth, cutLength;
	HDC hdc, mdc;
	HWND hWnd;
	HBITMAP hbmp;
public:
	void loadIn(DWORD dword);
	loadPic(HWND hwnd, LPCWSTR PATH, int x, int y,int picx, int picy, int dcx, int dcy, int  cutWidth, int cutLength) ;
	~loadPic();
};

