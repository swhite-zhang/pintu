#include "loadPic.h"

loadPic::loadPic(HWND hwnd, LPCWSTR PATH, int x, int y, int picx, int picy, int  cutwidth, int cutlength) :
	hdc(GetDC(hwnd)), picPath(PATH), width(x), length(y), hWnd(hwnd), PicX(picx), PicY(picy), cutWidth(cutwidth), cutLength(cutlength)
{
	mdc = CreateCompatibleDC(hdc);
	hbmp = (HBITMAP)LoadImage(NULL, picPath, IMAGE_BITMAP, width, length, LR_LOADFROMFILE);
	SelectObject(mdc, hbmp);
};

loadPic::~loadPic()
{
	ReleaseDC(hWnd, hdc);
}

void loadPic::loadIn(DWORD dword, int dcx, int dcy)
{

	BitBlt(hdc, dcx, dcy, cutWidth, cutLength, mdc, PicX, PicY, dword);
}

void loadPic::trans(int xstart, int ystart, int xend, int yend, BITMAP bm, unsigned char* px)
{
	int x, y;
	long int rgb_b;
	int PxBytes = bm.bmBitsPixel / 8;
	px = new BYTE[bm.bmHeight * bm.bmWidthBytes];
	for (y = ystart; y < yend; y++)
	{
		for (x = xstart; x < xend; x++)
		{
			rgb_b = y * bm.bmWidthBytes + x * PxBytes;//计算出半透明贴图区域内每个像素第一个颜色值（蓝色）所在的元素索引
			px[rgb_b] = px[rgb_b] * 0.9;
			px[rgb_b + 1] = px[rgb_b + 1] * 0.9;
			px[rgb_b + 2] = px[rgb_b + 2] * 0.9;
		}
	}
}

void loadPic::combin(int xstart, int ystart, int xend, int yend, unsigned char* px1, unsigned char* px2, BITMAP bm1, BITMAP bm2, HBITMAP& pic)
{
	int i;
	int x, y;
	long int rgb_b;
	int PxBytes = bm1.bmBitsPixel / 8;

	for (y = 0; y < (yend - ystart); y++)
	{
		for (x = 0; x < (xend - xstart); x++)
		{
			rgb_b = y * bm1.bmWidthBytes + x * PxBytes;//计算出半透明贴图区域内每个像素第一个颜色值（蓝色）所在的元素索引
			i = (ystart + y) * bm1.bmWidthBytes + (xstart + x) * PxBytes;

			px2[rgb_b] = px1[i];
			px2[rgb_b + 1] = px1[i + 1];
			px2[rgb_b + 2] = px1[i + 2];
		}
	}
	SetBitmapBits(pic, bm2.bmHeight * bm2.bmWidthBytes, px2);
}
