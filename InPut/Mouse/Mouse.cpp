// Mouse.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Mouse.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x, y;
	static BOOL bNowDraw = FALSE;
	int len;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		x = 0x0000FFFF & lParam;
		y = 0x0000FFFF & (lParam >> 16);

		bNowDraw = TRUE;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (bNowDraw == TRUE)
		{
			HDC hdc = GetDC(hWnd);
			MoveToEx(hdc, x, y, NULL);
			x = 0x0000FFFF & lParam;
			y = 0x0000FFFF & (lParam >> 16);
			LineTo(hdc, x, y);
			ReleaseDC(hWnd, hdc);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		bNowDraw = FALSE;
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		InvalidateRect(hWnd, NULL, TRUE);
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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	TCHAR my_class_name[] = TEXT("GraphOut");

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = my_class_name;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, my_class_name, WS_OVERLAPPEDWINDOW, 800, 400, 400, 350, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);


	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
