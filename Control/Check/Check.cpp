// Check.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Check.h"

#define EXIT			2

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND c1, c2, c3, c4;
	static BOOL bEllipse = FALSE;
		
	switch (uMsg) {
	case WM_CREATE:
		//c1 = CreateWindow(TEXT("button"), TEXT("Draw Ellipse?"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 20, 160, 25, hWnd, (HMENU)0, g_hInst, NULL);
		c1 = CreateWindow(TEXT("button"), TEXT("Draw Ellipse?"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 20, 160, 25, hWnd, (HMENU)0, g_hInst, NULL);
		c2 = CreateWindow(TEXT("button"), TEXT("Good bye Message?"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 50, 160, 25, hWnd, (HMENU)1, g_hInst, NULL);
		c3 = CreateWindow(TEXT("button"), TEXT("3State"), WS_CHILD | WS_VISIBLE | BS_3STATE, 20, 80, 160, 25, hWnd, (HMENU)2, g_hInst, NULL);
		c4 = CreateWindow(TEXT("button"), TEXT("Auto 3State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 20, 110, 160, 25, hWnd, (HMENU)3, g_hInst, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			/*if (SendMessage(c1, BM_GETCHECK,0,0) == BST_UNCHECKED)
			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = FALSE;
			}*/
			bEllipse = (BOOL)(SendMessage(c1, BM_GETCHECK, 0, 0) == BST_CHECKED);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
			}
			else
			{
				if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)
				{
					SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				else
				{
					SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
				}
			}
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (bEllipse == TRUE)
		{
			Ellipse(hdc, 200, 100, 400, 200);
		}
		else
		{
			Rectangle(hdc, 200, 100, 400, 200);
		}

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			MessageBox(hWnd, TEXT("Good bye"), TEXT("Check"), MB_OK);
		}
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	g_hInst = hInstance;
	wchar_t my_class_name[] = L"Control";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = g_hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"Control",
		WS_OVERLAPPEDWINDOW, 800, 300, 800, 800, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

