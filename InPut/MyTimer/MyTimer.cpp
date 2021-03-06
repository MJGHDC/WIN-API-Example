// MyTimer.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MyTimer.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR sTime[128];
	static TCHAR sansu[128];
	static RECT rt = { 100,100,400,200 };

	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 1, 3000, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
	}
	break;
	case WM_TIMER:
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		if (wParam == 1)
		{
			int unsigned x, y, result;

			srand(st.wMilliseconds);

			do
			{
				x = rand() % 30;
				y = rand() % 30;

				result = x + y;

			} while (result > 30);

			wsprintf(sansu, TEXT("%d + %d = %d"), x, y, result);
			InvalidateRect(hWnd, &rt, TRUE);
		}
		else if (wParam == 2)
		{
			wsprintf(sTime, TEXT("지금 시간은 %d:%d:%d입니다."), st.wHour, st.wMinute, st.wSecond);
			InvalidateRect(hWnd, &rt, TRUE);
		}
	}
	break;
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
		KillTimer(hWnd, 2);
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
