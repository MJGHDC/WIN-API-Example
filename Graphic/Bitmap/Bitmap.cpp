// Bitmap.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Bitmap.h"

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitmap, OldBitmap;

	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	else if (uMsg == WM_PAINT)
	{	
		hdc = BeginPaint(hWnd,&ps);
		MemDC = CreateCompatibleDC(hdc);
		MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

		BitBlt(hdc, 0, 0, 123, 160, MemDC, 0, 0, SRCCOPY);
		StretchBlt(hdc, 150, 0, 369, 480, MemDC, 0, 0, 123, 160, SRCCOPY);
		
		SelectObject(MemDC, OldBitmap);

		DeleteObject(MyBitmap);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);

		return 0;
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	g_hInst = hInstance;
	wchar_t my_class_name[] = L"Bitmap";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = g_hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"Bitmap",
		WS_OVERLAPPEDWINDOW, 100, 90, 800, 550, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

