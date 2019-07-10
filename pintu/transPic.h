#pragma once

#include "jigsaw.h"
#include "framework.h"

class transPic
{
private:
	unsigned char* px1, * px2;
	HDC hdc, mdc;
	BITMAP bm1, bm2;
	int xstart, ystart;

public:
	void handlePic(int showW, int showY, float fdegree);
	void showTrans(HBITMAP pic1, HBITMAP pic2);
	void tranself(HBITMAP pic);
	transPic(int xstart, int ystart, HBITMAP pic1, HBITMAP pic2, HDC Hdc, HDC Mdc);
	~transPic();
};

