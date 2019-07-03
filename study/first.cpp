// first.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "first.h"
#include <math.h>
#include <vector>
#define MAX_LOADSTRING 100
#define pi 3.1415926535

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HBITMAP hbmp,bg,girl;//位图对象
HDC mdc;//创建内存DC
HPEN hPen[7];
HPEN hPenP;
HBRUSH hBru[7];
HBRUSH hBruP;
POINT poly1[5], poly2[5], poly3[5];

const int xstart(50), ystart(50);//常数定义，半透明贴图的起始坐标
int sPen[7] = { PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME };//指定7种系统提供的画笔数组
int sBru[6] = { HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_BDIAGONAL };//指定6种系统所提供的阴影画刷数组
void myPaintL(HDC hdc);//画线
void myPaintW(HDC hdc, LPARAM lParam);//输出文字
void myPaintP(HDC hdc);//画多边形
void myPaintI(HDC hdc);//插入图片
void myPaintT(HDC hdc);//半透明处理

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。
	 
	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FIRST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);//调用MyRegisterClass()函数，向系统注册窗口类别，输入参数“hInstance”是目前程序运行个体的对象代码。
	// 执行应用程序初始化:

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}//掉用InitInstance函数，进行初始化操作。

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIRST));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))//获取程序消息
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);//转换为伪码及字符
			DispatchMessage(&msg);//将控制权交给系统，再有系统决定负责处理消息的程序
		}
	}//程序通过此消息循环来获取消息，并进行必要的键盘消息转换，而后将控制权交给操作系统，由操作系统决定该由哪个程序的消息处理函数处理消息。

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;//窗口类的风格，CS前缀，C表示class，S表示style，这里使用了水平和垂直风格
	wcex.lpfnWndProc = WndProc;//消息处理函数
	wcex.cbClsExtra = 0;//附加参数，通常情况下为0
	wcex.cbWndExtra = 0;//附加参数，通常情况下为0
	wcex.hInstance = hInstance;//窗口句柄，这里将WinMain中的hInstance句柄赋值就可
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRST));//窗口图标，LoadIcon()是加载图标，这里是加载一个系统资源图标，LoadIcon()的原型是HICON LoadIcon(HINSTANE,LPCSTR);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//加载鼠标
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//窗口画刷，这里是白色
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FIRST);//窗口菜单名称
	wcex.lpszClassName = szWindowClass;//窗口类别名称 
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
	HDC hdc;
	HWND hWnd = CreateWindowW(szWindowClass, _T("PinTu"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	//调用CreateWindow()函数建立一个窗口对象(窗口类名，窗口标题，窗口风格，窗口左上角x坐标，窗口左上角y坐标，窗口宽度，窗口高度，父窗口句柄，菜单句柄，窗口句柄改值会传递给窗口WM_CREATE消息的一个参数)
	if (!hWnd)
	{
		return FALSE;
	}
	SetCursorPos(456, 234);
	//MoveWindow(hWnd, 10, 10, 600, 450, true);//设定窗口显示的位置及窗口大小
	ShowWindow(hWnd, nCmdShow);//设定窗口显示时的状态，将窗口绘制于显示设备上
	UpdateWindow(hWnd);//发送一些初始消息，更新GDI
	//设定窗口的显示位置及窗口大小，然后绘制在显示设备上
	
	
	//画线和矩形
	for (int i = 0; i < 7; i++)
	{//循环建立各种画笔与画刷
		hPen[i] = CreatePen(sPen[i], 1, RGB(255, 0, 0));//建立画笔，rgb为颜色结构
		if (i == 6)
			hBru[i] = CreateSolidBrush(RGB(0, 255, 0));//建立阴影画刷
		else
			hBru[i] = CreateHatchBrush(sBru[i], RGB(0, 255, 0));
	}

	hdc = GetDC(hWnd);//取得窗口DC
	myPaintL(hdc);
	ReleaseDC(hWnd, hdc);//释放占用的DC


	//画多边形
	for (int i = 0; i < 5; i++)
	{//初始化顶点数组poly123
		poly1[i].x = 100 + 100 * sin( i * 72 * pi / 180 );
		poly1[i].y = 100 + 100 * cos(i * 72 * pi / 180);

		poly2[i].x = poly1[i].x + 300;
		poly2[i].y = poly1[i].y;

		poly3[i].x = poly1[i].x + 100;
		poly3[i].y = poly1[i].y + 200;
	}

	//建立画笔与画刷
	hPenP = CreatePen(PS_SOLID,5,RGB(255,0,0));
	hBruP = CreateHatchBrush(HS_BDIAGONAL, RGB(0, 355, 0));

	hdc = GetDC(hWnd);//取得窗口DC
	myPaintP(hdc);
	ReleaseDC(hWnd, hdc);//释放占用的DC


	//插入图片
	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);

	hbmp = (HBITMAP)LoadImage(NULL,_T( "bg.bmp"), IMAGE_BITMAP, 600,600, LR_LOADFROMFILE);//加载文件名为“bg.bmp”的位图到“hbmp”
	SelectObject(mdc, hbmp);//将hbmp存到mdc中
	myPaintI(hdc);

	ReleaseDC(hWnd, hdc);


	//半透明处理
	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);

	BITMAP bm1, bm2;//存储bg和girl的信息
	
	unsigned char* px1, * px2;//指向存储位图色彩值的数组
	//处理背景图
	bg = (HBITMAP)LoadImage(NULL, _T("background.bmp"), IMAGE_BITMAP, 524, 350, LR_LOADFROMFILE);
	GetObject(bg, sizeof(BITMAP), &bm1);//加载背景图并取的背景图信息，存于bm1中

	if (bm1.bmBitsPixel != 32 && bm1.bmBitsPixel != 24)
	{
		MessageBox(NULL, _T("此程序只能在32bit或24bit显示模式中运行"), _T("警告"), 0);
		return false;
	}

	px1 = new /*unsigned long int*/BYTE[bm1.bmHeight * bm1.bmWidthBytes];
	GetBitmapBits(bg, bm1.bmHeight * bm1.bmWidthBytes, px1);//建立暂存数组将取得的背景图象素色彩值存入px1中

	//处理前景图
	girl = (HBITMAP)LoadImage(NULL, _T("lzy.bmp"), IMAGE_BITMAP, 228, 250, LR_LOADFROMFILE);
	GetObject(girl, sizeof(BITMAP), &bm2);
	px2 = new /*unsigned long int*/BYTE[bm2.bmHeight * bm2.bmWidthBytes];
	GetBitmapBits(girl, bm2.bmHeight * bm2.bmWidthBytes, px2);//对前景图做同样操作

	int xend, yend;
	int x, y, i;//循环变量
	long int rgb_b;
	int PxBytes = (bm1.bmBitsPixel / 8);//计算目前显示系统中每一个像素多占用得Byte数（每一个Byte在暂存数组中即为一个元素），有助于后面求出像素各原色值存储得元素索引值

	xend = xstart + 228;//求出要显示半透明得区域得右下角点的坐标
	yend = ystart + 250;

	for (y = ystart; y < yend; y++)
	{
		for (x = xstart; x < xend; x++)
		{
			rgb_b = y * bm1.bmWidthBytes + x * PxBytes;//计算出半透明贴图区域内每个像素第一个颜色值（蓝色）所在的元素索引
			px1[rgb_b] = px1[rgb_b] * 0.7;
			px1[rgb_b + 1] = px1[rgb_b + 1] * 0.7;
			px1[rgb_b + 2] = px1[rgb_b + 2] * 0.7;
		}
	}

	for (y = 0; y < bm2.bmHeight; y++)
	{
		for (x = 0; x < bm2.bmWidth; x++)
		{
			rgb_b = y * bm2.bmWidthBytes + x * PxBytes;
			i = (ystart + y) * bm1.bmWidthBytes + (xstart + x) * PxBytes;

			px2[rgb_b] = px2[rgb_b] * 0.3 +px1[i];
			px2[rgb_b + 1] = px2[rgb_b + 1] * 0.3 +px1[i];
			px2[rgb_b + 2] = px2[rgb_b + 2] * 0.3 +px1[i];
		}
	}

	SetBitmapBits(girl, bm2.bmHeight* bm2.bmWidthBytes, px2);

	myPaintT(hdc);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		TCHAR szFilename[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);
		GetModuleFileName(hInstance, szFilename, MAX_PATH);
		MessageBoxW(hWnd, _T("傻逼"),_T("新窗口") , MB_OK | MB_ICONEXCLAMATION);
	}
	break;
	case WM_COMMAND://处理应用程序菜单消息
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT://窗口重绘消息
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		
		//myPaintI(hdc);


		EndPaint(hWnd, &ps);
		
	}
	break;
	case WM_MOUSEMOVE:
	{
		HDC hdc = GetDC(hWnd);
		myPaintW(hdc,lParam);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_DESTROY://窗口结束消息

		for (int i = 0; i < 7; i++)
		{
			DeleteObject(hPen[i]);//删除画笔
			DeleteObject(hBru[i]);//删除画刷
		}

		PostQuitMessage(0);//发送窗口结束消息给系统，通知系统结束目前程序的运行
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		//调用预设的系统函数来处理程序本身不处理的消息
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void myPaintL(HDC hdc)//自定义绘图函数
{
	int i, x1, x2, y;
	for (i = 0; i < 7; i++)
	{
		y = (i + 1) * 30;

		SelectObject(hdc, hPen[i]);//选用画笔
		MoveToEx(hdc, 30, y, NULL);//移到线条起点
		LineTo(hdc, 100, y);//画线
	}

	x1 = 120;
	x2 = 180;

	for (i = 0; i < 7; i++)
	{
		SelectObject(hdc, hBru[i]);//选用画笔
		Rectangle(hdc, x1, 30, x2, y);//画封闭矩形
		x1 += 70; 
		x2 += 70;
	}
}

void myPaintW(HDC hdc, LPARAM lParam)
{
	int x, y;
	WCHAR str[20] = _T(" ") ;//声明空字符串，用来存储要输出到屏幕上的文字
	x = LOWORD(lParam);//获取鼠标x坐标值
	y = HIWORD(lParam);//获取鼠标y坐标值

	SetTextColor(hdc, RGB(255, 0, 0));//设定输出到屏幕上的文字输出的颜色

	//格式化所要显示的字符串，并调用TextOut()函数将其输出再窗口上
	TextOut(hdc, 10, 10, _T("mouse position"), strlen("mouse position"));
	wsprintfW(str, _T("x position:%d"), x);
	TextOut(hdc, 30, 30, str, lstrlenW(str));
	wsprintfW(str, _T("y position:%d"), y);
	TextOut(hdc, 30, 50, str, lstrlenW(str));
}

void myPaintP(HDC hdc)
{
	SelectObject(hdc, hPenP);//自定义画笔
	SelectObject(hdc, hBruP);//自定义画刷
	//用顶点数组poly123绘图
	PolylineTo(hdc, poly1, 5);
	Polyline(hdc, poly2, 5);
	Polygon(hdc, poly3, 5);
}

void myPaintI(HDC hdc)
{
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);//贴图
}

void myPaintT(HDC hdc)
{
	SelectObject(mdc, bg);
	BitBlt(hdc, 600, 0, 524, 350, mdc, 0, 0, SRCCOPY);

	SelectObject(mdc, girl);
	BitBlt(hdc, 600+xstart, ystart, 228, 250, mdc, 0, 0, SRCCOPY);
}
