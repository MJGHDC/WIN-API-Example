// BkMode.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "BkMode.h"

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont, OldFont;
	const TCHAR *str = TEXT("폰트 Test 1234");
	HBRUSH MyBrush, OldBrush;
	switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		
		Rectangle(hdc, 50, 50, 400, 200);
		SelectObject(hdc, OldBrush);

		hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 0));
		TextOut(hdc, 100, 100, str, lstrlen(str));
		
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 100, 150, str, lstrlen(str));

		SelectObject(hdc, OldFont);
		DeleteObject(MyBrush);
		DeleteObject(hFont);
		
		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	g_hInst = hInstance;
	wchar_t my_class_name[] = L"BkMode";
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

	HWND hWnd = CreateWindow(my_class_name, L"BkMode",
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

