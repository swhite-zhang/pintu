#include "transPic.h"

transPic::transPic(int Xstart, int Ystart, HBITMAP pic1, HBITMAP pic2, HDC Hdc, HDC Mdc) :hdc(Hdc), mdc(Mdc), xstart(Xstart), ystart(Ystart)
{
	GetObject(pic1, sizeof(BITMAP), &bm1);
	px1 = new BYTE[bm1.bmHeight * bm1.bmWidthBytes];
	GetBitmapBits(pic1, bm1.bmHeight * bm1.bmWidthBytes, px1);
	GetObject(pic2, sizeof(BITMAP), &bm2);
	px2 = new BYTE[bm2.bmHeight * bm2.bmWidthBytes];
	GetBitmapBits(pic2, bm2.bmHeight * bm2.bmWidthBytes, px1);
}

transPic::~transPic()
{

}

void transPic::handlePic(int showW, int showL, float fdegree)
{
	int x, y;
	int xend, yend;
	long int rgb_b;
	int PxBytes = (bm1.bmBitsPixel / 8);
	int i;

	xend = xstart + showW;
	yend = ystart + showL;

	for (y = ystart; y < yend; y++)
	{
		for (x = xstart; x < xend; x++)
		{
			rgb_b = y * bm1.bmWidthBytes + x * PxBytes;//计算出半透明贴图区域内每个像素第一个颜色值（蓝色）所在的元素索引
			px1[rgb_b] = px1[rgb_b] * (1 - fdegree);
			px1[rgb_b + 1] = px1[rgb_b + 1] * (1 - fdegree);
			px1[rgb_b + 2] = px1[rgb_b + 2] * (1 - fdegree);
		}
	}


	for (y = 0; y < bm2.bmHeight; y++)
	{
		for (x = 0; x < bm2.bmWidth; x++)
		{
			rgb_b = y * bm2.bmWidthBytes + x * PxBytes;
			i = (ystart + y) * bm1.bmWidthBytes + (xstart + x) * PxBytes;

			px2[rgb_b] = px2[rgb_b] * fdegree + px1[i];
			px2[rgb_b + 1] = px2[rgb_b + 1] * fdegree + px1[i + 1];
			px2[rgb_b + 2] = px2[rgb_b + 2] * fdegree + px1[i + 2];
		}
	}
}

void transPic::showTrans(HBITMAP pic1, HBITMAP pic2)
{
	SetBitmapBits(pic2, bm2.bmHeight * bm2.bmWidthBytes, px2);

	SelectObject(mdc, pic1);
	BitBlt(hdc, 0, 0, 400, 400, mdc, 0, 0, SRCCOPY);

	SelectObject(mdc, pic2);
	BitBlt(hdc, 0 + xstart, ystart, 100, 100, mdc, 0, 0, SRCCOPY);
}
