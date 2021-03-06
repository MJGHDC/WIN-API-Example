// ComboBox.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "ComboBox.h"

#define ID_COMBOBOX 100

HINSTANCE g_hInst;
const TCHAR *Items[] = { TEXT("Apple"),TEXT("Orange"),TEXT("Melon"),TEXT("Grape"),TEXT("Strawberry") };
HWND hCombo;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE |
			CBS_DROPDOWN, 10, 10, 100, 200, hWnd, (HMENU)ID_COMBOBOX, g_hInst, NULL);
		for (i = 0; i<5; i++) {
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COMBOBOX:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
		}
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

