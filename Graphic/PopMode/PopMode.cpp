// PopMode.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PopMode.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int sx, sy, oldx, oldy;
	static BOOL bNowDraw = FALSE;

	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	else if(uMsg == WM_LBUTTONDOWN)
	{
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		oldx = sx;
		oldy = sy;
		bNowDraw = TRUE;
		return 0;
	}

	else if (uMsg == WM_MOUSEMOVE)
	{
		if (bNowDraw)
		{
			HDC hdc = GetDC(hWnd);
			
			SetROP2(hdc, R2_NOT);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);
			oldx = LOWORD(lParam);
			oldy = HIWORD(lParam);
			MoveToEx(hdc, sx, sy, NULL);
			LineTo(hdc, oldx, oldy);

			ReleaseDC(hWnd, hdc);
		}
	}

	else if (uMsg == WM_LBUTTONUP)
	{
		bNowDraw = FALSE;
		HDC hdc = GetDC(hWnd);

		MoveToEx(hdc, sx, sy, NULL);
		LineTo(hdc, oldx, oldy);

		ReleaseDC(hWnd, hdc);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"RopMode";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"RopMode",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

