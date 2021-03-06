// TransObject.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TransObject.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		for (int i = 0; i < 250; i += 5)
		{
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, 600, i);
		}

		HBRUSH MyBrush = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH OldBruch = (HBRUSH)SelectObject(hdc, MyBrush);
		HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

		Ellipse(hdc, 20, 20, 150, 150);

		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc, 220, 20, 350, 150);

		SelectObject(hdc, MyBrush);
		SelectObject(hdc, GetStockObject(NULL_PEN));
		Ellipse(hdc, 420, 20, 550, 150);

		DeleteObject(SelectObject(hdc, OldBruch));
		DeleteObject(SelectObject(hdc, OldPen));


		ReleaseDC(hWnd, hdc);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"TransObject";
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

	HWND hWnd = CreateWindow(my_class_name, L"TransObject",
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

