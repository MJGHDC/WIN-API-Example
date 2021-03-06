// EditWnd.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "EditWnd.h"

#define ID_EDIT 100

HINSTANCE g_hInst;

HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR *Mes = TEXT("왼쪽 클릭:에디트 이동, 오른쪽 클릭:보임/숨김");
	switch (iMessage) {
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL, 10, nTop, 200, 25, hWnd, (HMENU)ID_EDIT, g_hInst, NULL);
		SetWindowText(hEdit, TEXT("에디트도 윈도우다"));
		return 0;
	case WM_LBUTTONDOWN:
		nTop += 10;
		MoveWindow(hEdit, 10, nTop, 200, 25, TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (bShow) {
			bShow = FALSE;
			ShowWindow(hEdit, SW_HIDE);
		}
		else {
			bShow = TRUE;
			ShowWindow(hEdit, SW_SHOW);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 200, 100, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
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

