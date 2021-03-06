// TextOut.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TextOut.h"

void MyTextOut(HDC hdc, int x, int y, LPCTSTR Text);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	switch (message)
	{
	case WM_PAINT:
	{	
		HDC hdc;
		PAINTSTRUCT ps;
		TCHAR str[128];
		int Score = 85;

		hdc = BeginPaint(hWnd, &ps);

		
		wsprintf(str, TEXT("현재 점수는 %d점입니다."), Score);
		MyTextOut(hdc, 100, 60, str);
		SetTextAlign(hdc, TA_UPDATECP);
		MyTextOut(hdc, 100, 60, TEXT("what the fuck!!!"));
		MyTextOut(hdc, 100, 80, TEXT("fuck!!!"));
		MyTextOut(hdc, 100, 100, TEXT("you!!!"));

		EndPaint(hWnd, &ps);
		return 0;
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

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("TextOut");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(TEXT("TextOut"), TEXT("TextOut"), WS_OVERLAPPEDWINDOW,
		200, 300, 400, 300, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

void MyTextOut(HDC hdc, int x, int y, LPCTSTR Text)
{
	TextOut(hdc, x, y, Text, lstrlen(Text));
}