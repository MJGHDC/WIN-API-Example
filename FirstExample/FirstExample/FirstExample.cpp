// FirstExample.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "FirstExample.h"

#define SIZE 25
#define D_SIZE (SIZE*2)

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	
	
	if (uMsg == WM_RBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		HDC h_screen_dc = GetDC(NULL);

		BitBlt(h_dc, 10, 10, 500, 300, h_screen_dc, 0, 0, SRCCOPY);
		

		/*HBITMAP h_bitmap = (HBITMAP)GetCurrentObject(h_dc, OBJ_BITMAP);
		BITMAP bmp_info;

		GetObject(h_bitmap, sizeof(BITMAP), &bmp_info);
		int pattern_size = bmp_info.bmWidthBytes * bmp_info.bmHeight * bmp_info.bmBitsPixel / 8;
		char *p_data = new char[pattern_size];
		GetBitmapBits(h_bitmap, pattern_size, p_data);

		for (int i = 0; i < bmp_info.bmWidthBytes * bmp_info.bmHeight; i++)
		{
			*(p_data + i) = 0xFF0000FF;
		}

		SetBitmapBits(h_bitmap, pattern_size, p_data);

		delete[] p_data;*/
		ReleaseDC(hWnd, h_dc);
		ReleaseDC(NULL, h_screen_dc);

	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		HDC h_dc = GetDC(hWnd);
		//DebugBreak();
		int x = (lParam) & 0x0000FFFF;
		int y = (lParam >> 16) & 0x0000FFFF;

		if((MK_CONTROL | MK_SHIFT | MK_LBUTTON) == wParam ) Ellipse(h_dc, x - D_SIZE, y - D_SIZE, x + D_SIZE, y + D_SIZE);
		else if(MK_CONTROL & wParam) Ellipse(h_dc, x - SIZE, y - SIZE, x + SIZE, y + SIZE);
		else Rectangle(h_dc, x - SIZE, y - SIZE, x + SIZE, y + SIZE);

		ReleaseDC(hWnd, h_dc);

		MessageBeep(0);
		return 0;

	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;

		HDC h_dc = BeginPaint(hWnd, &ps);

		//기존 윈도우 화면 복구 어떻게 하는지 모름
		Rectangle(h_dc, 30 - SIZE, 30 - SIZE, 30 + SIZE, 30 + SIZE);

		EndPaint(hWnd, &ps);

		return 0;
	}
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);

	

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"FirstExample";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClass(&wc);

	HWND hWnd = CreateWindowW(my_class_name, L"FirstExampleWindow", WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		100, 90, 400, 350, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		/*PostQuitMessage(0);*/
	}

    return msg.wParam;
}
