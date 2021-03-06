// Radio.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Radio.h"

enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 };

HINSTANCE g_hInst;
HWND r1, r2, r3, r4, r5, r6;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	switch (uMsg) {
	case WM_CREATE:
		//c1 = CreateWindow(TEXT("button"), TEXT("Draw Ellipse?"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 20, 160, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Graph"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 5, 120, 110, hWnd, (HMENU)1, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Rectangle"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Ellipse"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 50, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Line"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 80, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("Black"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 20, 100, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 50, 100, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL);
		r6 = CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 80, 100, 30, hWnd, (HMENU)ID_R6, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_R1, ID_R2, ID_R1);
		CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_R1:
			Graph = 0;
			break;
		case ID_R2:
			Graph = 1;
			break;
		case ID_R3:
			Graph = 2;
			break;
		case ID_R4:
			Color = RGB(0, 0, 0);
			break;
		case ID_R5:
			Color = RGB(255, 0, 0);
			break;
		case ID_R6:
			Color = RGB(0, 0, 255);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MyBrush = CreateSolidBrush(Color);
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		MyPen = CreatePen(PS_SOLID, 0, Color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		switch (Graph)
		{
		case 0:
			Rectangle(hdc, 10, 200, 200, 300);
			break;
		case 1:
			Ellipse(hdc, 10, 200, 200, 300);
			break;
		case 2:
			MoveToEx(hdc, 10, 200, NULL);
			LineTo(hdc, 200, 300);
			break;
		}

		SelectObject(hdc, OldBrush);
		SelectObject(hdc, OldPen);

		DeleteObject(MyBrush);
		DeleteObject(MyPen);
		
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
	wchar_t my_class_name[] = L"Control";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
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

