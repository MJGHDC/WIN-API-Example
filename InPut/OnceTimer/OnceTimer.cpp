// OnceTimer.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "OnceTimer.h"

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc = GetDC(hWnd);

	for (int i = 0; i < 1000; i++)
	{
		unsigned char r = (rand() % 256), g = (rand() % 256), b = (rand() % 256);
		SetPixel(hdc, rand() % 500, rand() % 400, RGB(r, g, b));
	}
	ReleaseDC(hWnd, hdc);
	return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR str[128];
	static TCHAR str2[128] = TEXT("올라갑니다.");
	static RECT rs = { 200, 0, 500, 400 };
	static unsigned y;

	switch (message)
	{
	case WM_CREATE:
	{
		y = 300;
		SetTimer(hWnd, 2, 500, NULL);
		return 0;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			KillTimer(hWnd, 1);
			lstrcpy(str, TEXT(""));
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		}
		else if (wParam == 2)
		{
			if (y == 20)
			{
				KillTimer(hWnd, 2);
				SetTimer(hWnd, 3, 2000, NULL);
			}

			y -= 20;
			InvalidateRect(hWnd, &rs, TRUE);
		}
		else if (wParam == 3)
		{
			KillTimer(hWnd, 3);
			SetTimer(hWnd, 2, 500, NULL);
			y = 300;
			InvalidateRect(hWnd, &rs, TRUE);
		}
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		lstrcpy(str, TEXT("왼쪽 버튼을 눌렀습니다."));
		InvalidateRect(hWnd, NULL, TRUE);
		SetTimer(hWnd, 1, 3000, NULL);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 20, 20, str, lstrlen(str));
		TextOut(hdc, 200, y, str2, lstrlen(str2));
		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
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

	HWND hWnd = CreateWindow(my_class_name, my_class_name, WS_OVERLAPPEDWINDOW, 800, 400, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
