#include "Pwindow.h"

Pwindow::Pwindow()
{
	
}

Pwindow::~Pwindow()
{

}

ATOM Pwindow::MyRegisterClass(HINSTANCE hInstance , Pwindow win)
{
	win.wcex.style = CS_HREDRAW | CS_VREDRAW;
	win.wcex.lpfnWndProc = (WNDPROC)Pwindow::WndProc;
	win.wcex.cbClsExtra = 0;
	win.wcex.cbWndExtra = 0;
	win.wcex.hInstance = hInstance;
	win.wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PINTU));
	win.wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	win.wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	win.wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PINTU);
	win.wcex.lpszClassName = win.szWindowClass;
	win.wcex.hIconSm = LoadIcon(win.wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&win.wcex);
}

BOOL Pwindow::InitInstance(HINSTANCE hInstance, int nCmdShow,Pwindow win)
{
	win.hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(win.szWindowClass, win.szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK Pwindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,Pwindow win)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(win.hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)Pwindow::About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Pwindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam,Pwindow win)
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
