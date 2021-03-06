// RandGrp.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "RandGrp.h"

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
	static TCHAR sTime[128];
	static TCHAR sansu[128];
	static RECT rt = { 100,100,400,200 };

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 50, TimerProc);
		return 0;
	}
	case WM_TIMER:
	{
		
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		Ellipse(hdc, LOWORD(lParam) - 10, HIWORD(lParam) - 10, LOWORD(lParam) + 10, HIWORD(lParam) + 10);
		ReleaseDC(hWnd, hdc);
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, sansu, lstrlen(sansu));
		TextOut(hdc, 100, 120, sTime, lstrlen(sTime));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
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
