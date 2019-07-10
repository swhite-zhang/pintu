#pragma once
#include "framework.h"
#include "jigsaw.h"

class loadPic
{
private:
	LPCWSTR picPath;
	int width;
	int length;
	HDC hdc, mdc;
	HWND hWnd;

public:
	HBITMAP hbmp;
	int PicX, PicY, cutWidth, cutLength;
	void loadIn(DWORD dword, int dcx, int dcy);

	static void trans(int xstart, int ystart, int xend, int yend, BITMAP bm, unsigned char* px);
	static void combin(int xstart, int ystart, int xend, int yend, unsigned char* px1, unsigned char* px2, BITMAP bm1, BITMAP bm2, HBITMAP& pic);


	loadPic(HWND hwnd, LPCWSTR PATH, int x, int y, int picx, int picy, int  cutWidth, int cutLength);

	~loadPic();
};

