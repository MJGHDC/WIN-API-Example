// RopMode2.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "RopMode2.h"

#define CURVED_LINE		1
#define LINE			2
#define CIRCLE			3
#define RECTANGLE		4

int g_DrawOption;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int sx, sy, oldx, oldy;
	static BOOL bNowDraw = FALSE;

	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	else if (uMsg == WM_COMMAND)
	{
		int menu = LOWORD(wParam);
		if (menu == ID_CURVED_LINE_1)
		{
			g_DrawOption = CURVED_LINE;
		}
		else if (menu == ID_LINE_1)
		{
			g_DrawOption = LINE;
		}
		else if (menu == ID_CIRCLE_1)
		{
			g_DrawOption = CIRCLE;
		}
		else if (menu == ID_RECTANGLE_1)
		{
			g_DrawOption = RECTANGLE;
		}

	}

	else if (uMsg == WM_LBUTTONDOWN)
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
			if (g_DrawOption == LINE)
			{
				SetROP2(hdc, R2_NOT);
				MoveToEx(hdc, sx, sy, NULL);
				LineTo(hdc, oldx, oldy);
				oldx = LOWORD(lParam);
				oldy = HIWORD(lParam);
				MoveToEx(hdc, sx, sy, NULL);
				LineTo(hdc, oldx, oldy);
			}
			else if (g_DrawOption == CIRCLE)
			{
				SetROP2(hdc, R2_NOT);
				Ellipse(hdc, oldx, oldy, sx, sy);
				oldx = LOWORD(lParam);
				oldy = HIWORD(lParam);
				Ellipse(hdc, oldx, oldy, sx, sy);
			}
			else if (g_DrawOption == RECTANGLE)
			{
				SetROP2(hdc, R2_NOT);
				Rectangle(hdc, oldx, oldy, sx, sy);
				oldx = LOWORD(lParam);
				oldy = HIWORD(lParam);
				Rectangle(hdc, oldx, oldy, sx, sy);
			}
			else if (g_DrawOption == CURVED_LINE)
			{
				MoveToEx(hdc, sx, sy, NULL);
				sx = LOWORD(lParam);
				sy = HIWORD(lParam);
				LineTo(hdc, sx, sy);
			}

			ReleaseDC(hWnd, hdc);
		}
	}

	else if (uMsg == WM_LBUTTONUP)
	{
		bNowDraw = FALSE;
		HDC hdc = GetDC(hWnd);

		/*MoveToEx(hdc, sx, sy, NULL);
		LineTo(hdc, oldx, oldy);*/

		ReleaseDC(hWnd, hdc);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"RopMode2";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_ROPMODE2);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"RopMode2",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROPMODE2));

	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

