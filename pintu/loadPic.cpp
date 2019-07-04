#include "loadPic.h"

loadPic::loadPic(HWND hwnd, LPCWSTR PATH, int x, int y,int picx, int picy, int dcx, int dcy, int  cutwidth, int cutlength) :
	hdc(GetDC(hwnd)), picPath(PATH), width(x), length(y),hWnd(hwnd),PicX(picx),PicY(picy),DCX(dcx),DCY(dcy),cutWidth(cutwidth),cutLength(cutlength)
{
	mdc = CreateCompatibleDC(hdc);
	hbmp = (HBITMAP)LoadImage(NULL, picPath, IMAGE_BITMAP, width, length, LR_LOADFROMFILE);
	SelectObject(mdc, hbmp);
};

loadPic::~loadPic()
{
	ReleaseDC(hWnd, hdc);
}

void loadPic::loadIn(DWORD dword)
{

	BitBlt(hdc, DCX, DCY, cutWidth, cutLength, mdc, PicX, PicY, dword);
}
