// Graphic.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Graphic.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd,&ps);
		HPEN MyPen = CreatePen(PS_SOLID, 40, RGB(0, 0, 255));
		HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);
		HBRUSH MyBrush = (HBRUSH)CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
		HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

		Rectangle(hdc, 50, 50, 300, 200);

		DeleteObject(SelectObject(hdc, OldBrush));
		DeleteObject(SelectObject(hdc, OldPen));

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"First";
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

	HWND hWnd = CreateWindow(my_class_name, L"First",
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

