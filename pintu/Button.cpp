#include "button.h"


button::button(HWND hwnd, HINSTANCE hinstance, DWORD dwstyle, LPCWSTR buname, int bux, int buy, int buWidth, int buHeight, HMENU hmenu) :
	hWnd(hwnd), hInstance(hinstance), dwStyle(dwstyle), Buname(buname), Bux(bux), Buy(buy), BuWidth(buWidth), BuHeight(buHeight), hMenu(hmenu)
{
	hSub = CreateWindow(_T("BUTTON"), Buname, dwStyle, Bux, Buy, BuWidth, BuHeight, hWnd, hMenu, hInstance, NULL);
}

button::~button()
{
}
